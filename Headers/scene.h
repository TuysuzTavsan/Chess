#ifndef SCENE_H
#define SCENE_H

#include <components/script.h>
#include <ecs/ECSManager.h>
#include <signal.h>
#include <memory>
#include <list>


struct Scene
{
	std::vector<Script> scripts;
	Signal<void> endScene;

public:

	Scene() {}

	~Scene() = default;

	Scene(const Scene&) = delete;
	
	Scene(Scene&& other)
		:
		scripts(std::move(other.scripts)),
		endScene(std::move(other.endScene))
	{

	}

	Scene& operator=(const Scene& other) = delete;

	Scene& operator=(Scene&& other) noexcept
	{
		scripts = std::move(other.scripts);
		endScene = std::move(other.endScene);
	}

	void AddScript(Scriptable* scriptable)
	{
		scripts.emplace_back(Script(scriptable));
	}

	void Instantiate()
	{
		for (auto& script : scripts)
		{
			script.scriptable->instance = ECSManager::getManager()->CreateEntity();

			script.scriptable->free.Connect(
				[this](Entity t) -> void {FreeScript(t);}	);

			script.scriptable->endScene.Connect(
				[this]() -> void {endScene.Emmit();}	);
		}
	}

	void FreeScript(Entity ent)
	{
		ECSManager::getManager()->FreeEntity(ent);

	}

	void ScriptOnInit()
	{
		for (auto& script : scripts)
		{
			script.funcInstantiate();
		}
	}

	void ScriptOnUpdate(const float& dt)
	{
		for (auto& script : scripts)
		{
			script.funcUpdate(dt);
		}
	}
	void ScriptOnFree()
	{
		for (auto& script : scripts)
		{
			script.funcOnFree();
		}
	}

	void FreeAll()
	{
		for (auto& script : scripts)
		{
			ECSManager::getManager()->FreeEntity(script.scriptable->instance);
			script.scriptable->instance = 0;
		}
	}
};


struct SceneManager
{
	std::vector<Scene> scenes;
	uint16_t active = 0;
	bool isReady = false;
	bool shouldEnd = false;
	bool shouldUpdate = true;

public:

	//TODO do we need scene pointer for this to work?
	//TODO do we support multiple scenes?
	void AddScene(Scene& scene)
	{
		scene.endScene.Connect(
			[this]() { End(); }
		);
		scenes.emplace_back(std::move(scene));

	}

	void ReadyScenes()
	{
		for (auto& scene : scenes)
		{
			scene.Instantiate();
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
		else if(!isReady)
		{
			scenes[active].ScriptOnInit();
			isReady = true;
			return;
		}
		else
		{
			scenes[active].ScriptOnUpdate(dt);
		}
		

		
		
	}

	void End()
	{
		scenes[active].ScriptOnFree();
		scenes[active].FreeAll();
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

