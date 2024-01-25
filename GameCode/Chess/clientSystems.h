#pragma once
#include <ecs/SystemManager.h>

#include <Chess/renderSystem.h>

#define ADD_SYSTEM(x) systemManager->AddSystem(new x)

void SetClientSystems(SystemManager* systemManager)
{
	ADD_SYSTEM(RenderSystem);
}
