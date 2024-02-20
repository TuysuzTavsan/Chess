#pragma once

#include <ecs/ecsTypes.h>
#include <vector>
#include <ecs/System.h>
#include <memory>

class SystemManager
{
public:

	SystemManager() = default;
	~SystemManager() = default;

	void AddSystem(std::unique_ptr<System>&& system)
	{
		systems.emplace_back(std::move(system));
	}

	void Update(const float& dt)
	{
		for (auto& system : systems)
		{
			(system.get())->Operate(dt);
		}
	}

private:

	std::vector<std::unique_ptr<System>> systems;

};