#pragma once

#include <newECS/necsTypes.h>
#include <newECS/EntityManager.h>
#include <newECS/ComponentPool.h>
#include <newECS/ComponentManager.h>



class ECSManager
{
public:

	ECSManager();
	~ECSManager();

	Entity CreateEntity();

	void FreeEntity(Entity entity);
	
	template<typename T>
	void InsertComponent(Entity entity, T compData)
	{
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

	void Update();

private:

	EntityManager entityManager;
	ComponentManager componentManager;



};