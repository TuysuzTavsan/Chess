#pragma once

#include <ecs/ecsTypes.h>
#include <ecs/EntityManager.h>
#include <ecs/ComponentPool.h>
#include <ecs/ComponentManager.h>

//Singleton ECSManager class that manages all ECS system.
class ECSM 
{
public:

	ECSM() = delete;

	static Entity CreateEntity();

	static void FreeEntity(Entity entity);
	
	template<typename T>
	static void InsertComponent(Entity entity, T compData)
	{
		assert(entityManager.HasEntity(entity) && "Entity does not exist!");
		componentManager.AddComponent<T>(entity, compData);
		entityManager.SetSignature(entity, componentManager.GetComponentID<T>(), true);
	}

	template<typename T>
	static void RegisterComponent()
	{
		componentManager.RegisterComponent<T>();
	}

	template<typename T>
	static T& GetComponentData(Entity entity)
	{
		return componentManager.GetComponentData<T>(entity);
	}

	template<typename T>
	static std::vector<T>& GetPoolData()
	{
		assert(componentManager.IsComponentDefined<T>() && "Component is not registered!");
		ComponentPool<T>* cpool = componentManager.GetPool<T>();
		return cpool->pool;
	}

private:

	static EntityManager entityManager;
	static ComponentManager componentManager;


};