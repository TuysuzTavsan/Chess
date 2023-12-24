#pragma once

#include <ecs/ecsTypes.h>
#include <vector>
#include <ecs/System.h>

class SystemManager
{
public:

	SystemManager() = default;
	~SystemManager() = default;

	void AddSystem(System* system)
	{
		systems.push_back(system);
	}

	void Update(const float& dt)
	{
		for (auto system : systems)
		{
			system->Operate(dt);
		}
	}

private:

	std::vector<System*> systems;

};