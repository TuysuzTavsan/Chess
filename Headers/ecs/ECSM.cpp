#include <ecs/ECSM.h>

EntityManager ECSM::entityManager;
ComponentManager ECSM::componentManager;

Entity ECSM::CreateEntity()
{
	return entityManager.CreateEntity();
}

void ECSM::FreeEntity(Entity entity)
{
	Signature sign = entityManager.GetSignature(entity);

	for (ComponentID i = 0; i < MAX_COMPONENT; i++)
	{
		if (sign.test(i))
		{
			//Entity has component.
			IComponentPool* pool = componentManager.GetPoolbyID(i);
			pool->EraseComponent(entity);
			entityManager.SetSignature(entity, i, false);
		}
	}


	entityManager.FreeEntity(entity);
}