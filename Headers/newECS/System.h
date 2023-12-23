#pragma once
#include <newECS/necsTypes.h>
#include <newECS/ComponentPool.h>

template<typename T>
class System
{
public:

	System() {}
	~System() {}


	void InsertComponent(Entity entity, T component)
	{
		componentPool->AddComponent(entity, component);
	}

	virtual void Operate() = 0;


private:
	ComponentPool<T>* componentPool = nullptr;


};