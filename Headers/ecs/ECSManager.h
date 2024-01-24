#pragma once

#include <ecs/ecsTypes.h>
#include <ecs/EntityManager.h>
#include <ecs/ComponentPool.h>
#include <ecs/ComponentManager.h>

//Singleton ECSManager class that manages all ECS system.
class ECSManager 
{
public:
	
	static ECSManager* getManager();
	ECSManager(const ECSManager& othr) = delete;

	~ECSManager();

	Entity CreateEntity();

	void FreeEntity(Entity entity);
	
	template<typename T>
	void InsertComponent(Entity entity, T compData)
	{
		assert(entityManager.HasEntity(entity) && "Entity does not exist!");
		componentManager.AddComponent<T>(entity, compData);
		entityManager.SetSignature(entity, componentManager.GetComponentID<T>(), true);
	}

	template<typename T>
	void RegisterComponent()
	{
		componentManager.RegisterComponent<T>();
	}

	template<typename T>
	T& GetComponentData(Entity entity)
	{
		return componentManager.GetComponentData<T>(entity);
	}

	template<typename T>
	std::vector<T>& GetPoolData()
	{
		assert(componentManager.IsComponentDefined<T>() && "Component is not registered!");
		ComponentPool<T>* cpool = componentManager.GetPool<T>();
		return cpool->pool;
	}

private:

	ECSManager();
	static ECSManager* Instance;

	EntityManager entityManager;
	ComponentManager componentManager;



};