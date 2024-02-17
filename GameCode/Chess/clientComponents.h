#pragma once
#include <ecs/ECSM.h>
#include <components/sprite.h>
#include <components/button.h>

#define REGISTER(x) ECSM::RegisterComponent<x>();

void RegisterClientComponents()
{
	REGISTER(Sprite);
	REGISTER(Button);
}