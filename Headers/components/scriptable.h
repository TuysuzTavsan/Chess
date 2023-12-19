#pragma once
#include <ecs/ecs.h>


//Interface for a script
class Scriptable
{
public:
	ECS::Entity instance = 0;

	virtual ~Scriptable() = default;

	virtual void Instantiate() = 0;
	virtual void Update(const float& dt) = 0;
	virtual void OnFree() = 0;
};
