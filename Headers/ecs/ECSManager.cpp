#include <ecs/ECSManager.h>

ECSManager* ECSManager::Instance = nullptr;

ECSManager::ECSManager()
{

}

ECSManager::~ECSManager()
{

}

ECSManager* ECSManager::getManager()
{
	if (Instance == nullptr)
	{
		Instance = new ECSManager;
	}

	return Instance;
}

Entity ECSManager::CreateEntity()
{
	return entityManager.CreateEntity();
}

void ECSManager::FreeEntity(Entity entity)
{
	Signature sign = entityManager.GetSignature(entity);

	for (ComponentID i = 0; i < MAX_COMPONENT; i++)
	{
		if (sign.test(i))
		{
			//Entity has component.
			IComponentPool* pool = componentManager.GetPoolbyID(sign[i]);
			pool->EraseComponent(entity);
			entityManager.SetSignature(entity, i, false);
		}
	}


	entityManager.FreeEntity(entity);
}