#pragma once

#include <newECS/necsTypes.h>
#include <map>
#include <vector>

#include <assert.h>
#include <iostream>
#include <newECS/ComponentPool.h>

class ComponentManager
{
public:

	ComponentManager();
	~ComponentManager();

	//Check if the component is already defined via RegisterComponent.
	template<typename T>
	bool IsComponentDefined()
	{
		return (ComponentList.find(std::string(type_name<T>())) == ComponentList.end());
	}

	//Register a component.
	template<typename T>
	void RegisterComponent()
	{
		std::string str(type_name<T>());
		assert(ID + 1 < MAX_COMPONENT && "Too much components!");
		assert(IsComponentDefined<T>() && "Component already registered!");
		ComponentID id = ++ID;;
		ComponentPool<T>* pool = new ComponentPool<T>();
		ComponentPoolReacher.insert({ id, static_cast<IComponentPool*>(pool) });
		ComponentList.insert({ str,id });
	}

	template<typename T>
	void FreeComponent(Entity entity)
	{

		ComponentPool<T>* x = GetPool<T>();
		x->EraseComponent(entity);
	}

	template<typename T>
	void AddComponent(Entity entity, T compData)
	{
		ComponentPool<T>* pool = GetPool<T>();
		pool->AddComponent(entity, compData);
	}

	//Get a specified componentPool by a pointer.
	template<typename T>
	ComponentPool<T>* GetPool()
	{
		ComponentID id = GetComponentID<T>();
		assert(ComponentPoolReacher.find(id) != ComponentPoolReacher.end() && "Can not find Pool!");

		return static_cast<ComponentPool<T>*>(ComponentPoolReacher.find(id)->second);
	}

	template<typename T>
	T& GetComponentData(Entity entity)
	{
		ComponentPool<T>* pool = GetPool<T>();
		return pool->GetComponent(entity);
	}

	//Get pool by componentID
	IComponentPool* GetPoolbyID(ComponentID id);
	
	//Get an entity's ComponentID by type name.
	template<typename T>
	ComponentID GetComponentID()
	{
		std::string_view type = type_name<T>();
		assert(ComponentList.find(std::string(type)) != ComponentList.end() && "Component not registered!");

		return ComponentList.find(std::string(type))->second;
	}

	//Get component name by ComponentID.
	// TODO: Find a better way to implement.
	std::string_view GetComponentName(ComponentID id);
	
	//Get all registered components. This func will return a vector<string_view>.
	// TODO: Find a better way to implement?
	std::vector<std::string_view> GetAllComponentsName();
	
	//Function to print entity's specified component. Usefull for debugging.
	void PrintComponent(std::string_view type);


private:

	//Counter to give ID to component types.
	uint16_t ID = 0;

	//List of defined components.
	std::map<std::string, ComponentID> ComponentList;
	std::map<ComponentID, IComponentPool*> ComponentPoolReacher;

};