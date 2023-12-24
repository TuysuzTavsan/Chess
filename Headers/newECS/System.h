#pragma once
#include <newECS/necsTypes.h>
#include <newECS/ComponentPool.h>


class System
{
public:

	System() {}
	~System() {}

	virtual void Operate() = 0;

};