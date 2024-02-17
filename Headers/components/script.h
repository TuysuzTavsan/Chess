#ifndef SCRIPT_COMPONENT
#define SCRIPT_COMPONENT

#include <functional>
#include <scriptable.h>
#include <memory>

struct Script
{
	std::unique_ptr<Scriptable> scriptable;
	std::function<void()> funcInstantiate;
	std::function<void(const float&)> funcUpdate;
	std::function<void()> funcOnFree;


	Script(Scriptable* _scriptable)
		:
		scriptable(_scriptable)
	{
		funcInstantiate = [this]() -> void { scriptable->Instantiate(); };
		funcUpdate = [this](const float& dt) -> void { scriptable->Update(dt); };
		funcOnFree = [this]() -> void {scriptable->OnFree(); };

	}

	~Script() {}

	Script(const Script&) = delete;

	Script(Script&& other) noexcept
		:
		scriptable(std::move(other.scriptable))
	{
		funcInstantiate = [this]() -> void { scriptable->Instantiate(); };
		funcUpdate = [this](const float& dt) -> void { scriptable->Update(dt); };
		funcOnFree = [this]() -> void {scriptable->OnFree(); };
	}

	Script& operator=(Script&& other) noexcept
	{
		scriptable = std::move(other.scriptable);

		funcInstantiate = [this]() -> void { scriptable->Instantiate(); };
		funcUpdate = [this](const float& dt) -> void { scriptable->Update(dt); };
		funcOnFree = [this]() -> void {scriptable->OnFree(); };

		return *this;
	}

	Script& operator=(const Script& other) = delete;



};

#endif // !SCRIPT_COMPONENT
