#pragma once
#include <ecs/ECSManager.h>
#include <components/sprite.h>

#define REGISTER(x) ecsManager->RegisterComponent<x>();

void RegisterClientComponents(ECSManager* ecsManager)
{
	REGISTER(Sprite);
}