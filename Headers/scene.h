#pragma once

#include <components/script.h>
#include <ecs/ECSM.h>
#include <signal.h>
#include <vector>

/*
Entry point scene will always be at index 0.
Scenes will have names to support changing between scenes from scripts.
*/

class SceneManager;

struct Scene
{
	friend SceneManager;

	//Scene names must be unique.
	Scene(std::string name)
		:
		name(name)
	{}

	~Scene() = default;

	Scene(const Scene&) = delete;
	
	Scene(Scene&& other) noexcept
		:
		scripts(std::move(other.scripts)),
		name(std::move(other.name))
	{

	}

	Scene& operator=(const Scene& other) = delete;

	Scene& operator=(Scene&& other) noexcept
	{
		scripts = std::move(other.scripts);
		name = std::move(other.name);
	}

	//Add a script from scriptable interface.
	void AddScript(Scriptable* scriptable)
	{
		scripts.emplace_back(Script(scriptable));
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

	//Instantiate entities that will hold scripts.
	void Prepare()
	{
		for (auto& script : scripts)
		{
			script.scriptable->instance = ECSM::CreateEntity();

			script.scriptable->free.Connect(
				[this](Entity t) -> void {FreeScript(t);}	);
		}
	}

	//Free all content that a scene has.
	void Free()
	{
		for (auto& script : scripts)
		{
			ECSM::FreeEntity(script.scriptable->instance);
			script.scriptable->instance = 0;
		}
	}

protected:

	std::vector<Script> scripts;
	std::string name;

	//Delete script.
	void FreeScript(Entity ent)
	{
		ECSM::FreeEntity(ent);

	}
};

