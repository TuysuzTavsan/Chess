#pragma once
#include <ecs/ECSManager.h>
#include <components/sprite.h>
#include <components/button.h>

#define REGISTER(x) ecsManager->RegisterComponent<x>();

void RegisterClientComponents(ECSManager* ecsManager)
{
	REGISTER(Sprite);
	REGISTER(Button);
}