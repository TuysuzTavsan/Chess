#ifndef SCENE_H
#define SCENE_H

#include <ecs/ecs.h>
#include <components/script.h>

struct Scene
{
	std::vector<Script*> scripts;

public:

	~Scene()
	{
		for (auto& script : scripts)
		{
			delete script;
		}
	}

	void operator=(const Scene& other)
	{
		this->scripts = other.scripts;
	}

	void AddScript(Script* script)
	{
		scripts.push_back(script);
	}

	void Instantiate()
	{
		std::cout << "Instantiating scriptable entities!\n";
		for (auto& scriptComponent : scripts)
		{
			scriptComponent->scriptable->instance = ECS::CreateEntity();
		}
		std::cout << "Instantiating scriptable entities done!\n";
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

	void Free()
	{
		std::cout << "Cleaning scriptable entities!\n";
		for (auto& scriptComponent : scripts)
		{
			ECS::FreeEntity(scriptComponent->scriptable->instance);
			scriptComponent->scriptable->instance = NULL;
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

	void AddScene(Scene* scene)
	{
		scenes.push_back(scene);
	}

	void ReadyScenes()
	{
		for (auto& pScene : scenes)
		{
			pScene->Instantiate();
		}
	}

	void Play()
	{
		assert(active < scenes.size() && "Playing null scene!");
		if (!isReady)
		{
			scenes[active]->ScriptOnInit();
			isReady = true;
		}
		if (!shouldEnd)
		{
			scenes[active]->ScriptOnUpdate(13.0);
		}
		
		
	}

	void End()
	{
		scenes[active]->ScriptOnFree();
		scenes[active]->Free();
		isReady = false;
	}


};



#endif // !SCENE_H

