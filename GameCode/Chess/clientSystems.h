#pragma once
#include <ecs/SystemManager.h>

#include <Chess/renderSystem.h>
#include <Chess/guiSystem.h>

#define ADD_SYSTEM(x) systemManager.AddSystem(std::unique_ptr<System>(reinterpret_cast<System*>(new x)))

void SetClientSystems(SystemManager& systemManager)
{
	ADD_SYSTEM(RenderSystem);
	ADD_SYSTEM(GUISystem);
}
