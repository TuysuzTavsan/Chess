#pragma once

#include <vector>
#include <ecs/ecs.h>
#include <iostream>
#include <components/script.h>


class ScriptSystem
{
public:
	std::vector<Script> entities;


	void PushBack(Script scriptcomponent)
	{
		entities.push_back(scriptcomponent);
	}

	void Instantiate()
	{
		std::cout << "Instantiating scriptable entities!\n";
		for (auto& scriptComponent : entities)
		{
			scriptComponent.scriptable->instance = ECS::CreateEntity();
		}
		std::cout << "Instantiating scriptable entities done!\n";
	}

	void ScriptOnInit()
	{
		for (auto& scriptComponent : entities)
		{
			scriptComponent.funcInstantiate();
		}
	}
	void ScriptOnUpdate(const float& dt)
	{
		for (auto& scriptComponent : entities)
		{
			scriptComponent.funcUpdate(dt);
		}
	}
	void ScriptOnFree()
	{
		for (auto& scriptComponent : entities)
		{
			scriptComponent.funcFree();
		}
	}

	void Free()
	{
		std::cout << "Cleaning scriptable entities!\n";
		for (auto& scriptComponent : entities)
		{
			ECS::FreeEntity(scriptComponent.scriptable->instance);
			scriptComponent.scriptable->instance = NULL;
		}
		std::cout << "Cleaning done!\n";
	}
};