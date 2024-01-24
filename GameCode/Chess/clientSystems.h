#pragma once
#include <ecs/SystemManager.h>

#include <Chess/spriteSystem.h>

#define ADD_SYSTEM(x) systemManager->AddSystem(new x)

void SetClientSystems(SystemManager* systemManager)
{
	ADD_SYSTEM(SpriteSystem);
}
