#ifndef SCRIPT_COMPONENT
#define SCRIPT_COMPONENT

#include <functional>
#include <vector>

/*
* Goal: Have a script component that will provide a interface for
* update
* instantiate
* free 
* methods.
*/

//Interface for a script
class Scriptable
{
public:
	ECS::Entity instance = 0;

	virtual ~Scriptable() = default;

	virtual void Instantiate() = 0;
	virtual void Update(const float& dt) = 0;
	virtual void Free() = 0;
};

struct ScriptComponent
{
	Scriptable* scriptable;
	void Scriptify(Scriptable& iscript)
	{
		scriptable = &iscript;
		funcInstantiate = [&iscript]() -> void { iscript.Instantiate(); };
		funcUpdate = [&iscript](const float& dt) -> void { iscript.Update(dt); };
		funcFree = [&iscript]() -> void {iscript.Free(); };
	}

	std::function<void()> funcInstantiate;
	std::function<void(const float&)> funcUpdate;
	std::function<void()> funcFree;
};

class ScriptSystem
{
public:
	std::vector<ScriptComponent> entities;


	void PushBack(ScriptComponent scriptcomponent)
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

////Will hold scripted entitys in a place and then run their scripts.
//class ScriptSystem
//{
//
//};

#endif // !SCRIPT_COMPONENT
