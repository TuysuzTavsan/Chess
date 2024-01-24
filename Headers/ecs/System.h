#pragma once
#include <ecs/ecsTypes.h>
#include <ecs/ComponentPool.h>


class System
{
public:

	System() {}
	virtual ~System() = default;

	virtual void Operate(const float& dt) = 0;

};