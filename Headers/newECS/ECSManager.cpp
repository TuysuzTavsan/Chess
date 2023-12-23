#include <newECS/ECSManager.h>

ECSManager::ECSManager()
{

}

ECSManager::~ECSManager()
{

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

//template<typename T>
//void ECSManager::InsertComponent(Entity entity, T compData)
//{
//	componentManager.AddComponent<T>(entity, compData);
//	entityManager.SetSignature(entity, componentManager.GetComponentID<T>(), true);
//}
//
//template<typename T>
//void ECSManager::RegisterComponent()
//{
//	componentManager.RegisterComponent<T>();
//}
//
//template<typename T>
//T& ECSManager::GetComponentData(Entity entity)
//{
//	return componentManager.GetComponentData<T>(entity);
//}