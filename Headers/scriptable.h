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

	virtual ~Scriptable() = default;

	virtual void Instantiate() = 0;
	virtual void Update(const float& dt) = 0;
	virtual void OnFree() = 0;

};
