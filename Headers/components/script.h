#ifndef SCRIPT_COMPONENT
#define SCRIPT_COMPONENT

#include <functional>
#include <scriptable.h>

struct Script
{
	Scriptable* scriptable = nullptr;

	Script(Scriptable* iscript)
	{
		scriptable = iscript;
		funcInstantiate = [this]() -> void { scriptable->Instantiate(); };
		funcUpdate = [this](const float& dt) -> void { scriptable->Update(dt); };
		funcOnFree = [this]() -> void {scriptable->OnFree(); };

	}

	std::function<void()> funcInstantiate;
	std::function<void(const float&)> funcUpdate;
	std::function<void()> funcOnFree;

};

#endif // !SCRIPT_COMPONENT
