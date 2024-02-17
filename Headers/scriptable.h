#pragma once
#include <ecs/ecsTypes.h>
#include <signal.h>


//Interface for a script
class Scriptable
{
public:
	Entity instance = 0;
	Signal<void, Entity> free;
	Signal<void> endScene;

	Scriptable() {}

	Scriptable(const Scriptable& othr) = delete;

	Scriptable(Scriptable&& other) noexcept
		:
		instance(std::move(other.instance)),
		free(std::move(other.free)),
		endScene(std::move(other.endScene))
	{

	}

	Scriptable& operator=(Scriptable&& other) noexcept
	{
		instance = std::move(other.instance);
		free = std::move(other.free);
		endScene = std::move(other.endScene);

		return *this;
	}

	Scriptable& operator=(const Scriptable& other) = delete;

	virtual ~Scriptable() = default;

	virtual void Instantiate() = 0;
	virtual void Update(const float& dt) = 0;
	virtual void OnFree() = 0;

};
