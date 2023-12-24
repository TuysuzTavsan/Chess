#pragma once
#include <ecs/System.h>
#include <ecs/ECSManager.h>

class RenderSystem : public System
{
public:
	void Operate(const float& dt) override
	{
		ECSManager* manager = ECSManager::getManager();
	}
};