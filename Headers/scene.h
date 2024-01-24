#ifndef SCENE_H
#define SCENE_H

#include <components/script.h>
#include <ecs/ECSManager.h>
#include <observer.h>

#define NEW_SCENE(x) Scene* x = new Scene
#define ADD_SCRIPT(scene, script) scene->AddScript(new Script(new script))
#define RETURN_SCENE(x) return x

struct Scene
{
	std::list<Script*> scripts;
	Signal<void> endScene;

public:

	~Scene()
	{
		for (auto& script : scripts)
		{
			delete script;
		}
	}

/* 	void operator=(const Scene& other)
	{
		this->scripts = other.scripts;
	} */

	void AddScript(Script* script)
	{
		scripts.push_back(script);
	}

	void Instantiate()
	{
		std::cout << "Instantiating scriptable entities!\n";
		for (auto& scriptComponent : scripts)
		{
			scriptComponent->scriptable->instance = ECSManager::getManager()->CreateEntity();
			scriptComponent->scriptable->free.Connect(
				[this](Entity t) -> void {FreeScript(t);}
			);
			scriptComponent->scriptable->endScene.Connect(
				[this]() -> void {endScene.Emmit();}
			);
		}
		std::cout << "Instantiating scriptable entities done!\n";
	}

	void FreeScript(Entity ent)
	{
		ECSManager::getManager()->FreeEntity(ent);

	}

	void ScriptOnInit()
	{
		for (auto& scriptComponent : scripts)
		{
			scriptComponent->funcInstantiate();
		}
	}
	void ScriptOnUpdate(const float& dt)
	{
		for (auto& scriptComponent : scripts)
		{
			scriptComponent->funcUpdate(dt);
		}
	}
	void ScriptOnFree()
	{
		for (auto& scriptComponent : scripts)
		{
			scriptComponent->funcOnFree();
		}
	}

	void FreeAll()
	{
		std::cout << "Cleaning scriptable entities!\n";
		for (auto& scriptComponent : scripts)
		{
			ECSManager::getManager()->FreeEntity(scriptComponent->scriptable->instance);
			scriptComponent->scriptable->instance = 0;
		}
		std::cout << "Cleaning done!\n";
	}
};


struct SceneManager
{
	std::vector<Scene*> scenes;
	uint16_t active = 0;
	bool isReady = false;
	bool shouldEnd = false;
	bool shouldUpdate = true;

public:

	~SceneManager()
	{
		for (auto& scene : scenes)
		{
			delete scene;
		}
	}

	void operator=(const SceneManager& other)
	{
		this->scenes = other.scenes;
	}

	//TODO do we need scene pointer for this to work?
	//TODO do we support multiple scenes?
	void AddScene(Scene* scene)
	{
		scenes.push_back(scene);
		scene->endScene.Connect(
			[this](){ End();}
		);
	}

	void ReadyScenes()
	{
		for (auto& pScene : scenes)
		{
			pScene->Instantiate();
		}
	}

	void Play(const float& dt)
	{
		//No need to assert now.
		//TODO but maybe we need if we redisgne this class.
		//assert(active < scenes.size() && "Playing null scene!");

		if(!shouldUpdate)
		{
			return;
		}
		if (!isReady)
		{
			scenes[active]->ScriptOnInit();
			isReady = true;
		}
		if (!shouldEnd)
		{
			scenes[active]->ScriptOnUpdate(dt);
		}

		
		
	}

	void End()
	{
		scenes[active]->ScriptOnFree();
		scenes[active]->FreeAll();
		shouldEnd = true;
		isReady = false;


		// Scene just ended and we need to prepare new scene if there is one.
		//check if there is any scene waiting
		active++;
		if(scenes.size() > active)
		{
			return;
		}
		else
		{
			std::cout << "No scene to play!\n";
			shouldUpdate = false;
		}
		
	}


};



#endif // !SCENE_H

