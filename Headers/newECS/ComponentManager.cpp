#include <newECS/ComponentManager.h>
#include <newECS/type_name.h>
#include <assert.h>
#include <iostream>
#include <newECS/ComponentPool.h>

ComponentManager::ComponentManager()
{

}

ComponentManager::~ComponentManager()
{
	for (auto& pair : ComponentPoolReacher)
	{
		delete pair.second;
	}
}

////Check if the component is already defined via RegisterComponent.
//template<typename T>
//bool ComponentManager::IsComponentDefined()
//{
//	return (ComponentList.find(std::string(type_name<T>())) == ComponentList.end());
//}
//
////Register a component.
//template<typename T>
//void ComponentManager::RegisterComponent()
//{
//	std::string str(type_name<T>());
//	assert(ID + 1 < MAX_COMPONENT && "Too much components!");
//	assert(IsComponentDefined<T>() && "Component already registered!");
//	ComponentID id = ++ID;;
//	ComponentPool<T>* pool = new ComponentPool<T>();
//	ComponentPoolReacher.insert({ id, static_cast<IComponentPool*>(pool) });
//	ComponentList.insert({ str,id });
//}
//
//template<typename T>
//void ComponentManager::FreeComponent(Entity entity)
//{
//
//	ComponentPool<T>* x = GetPool<T>();
//	x->EraseComponent(entity);
//}
//
//template<typename T>
//void ComponentManager::AddComponent(Entity entity, T compData)
//{
//	ComponentPool<T>* pool = GetPool<T>();
//	pool->AddComponent(entity, compData);
//}
//
////Get a specified componentPool by a pointer.
//template<typename T>
//ComponentPool<T>* ComponentManager::GetPool()
//{
//	ComponentID id = GetComponentID<T>();
//	assert(ComponentPoolReacher.find(id) != ComponentPoolReacher.end() && "Can not find Pool!");
//
//	return static_cast<ComponentPool<T>>(ComponentPoolReacher.find(id)->second);
//}
//
//template<typename T>
//T& ComponentManager::GetComponentData(Entity entity)
//{
//	ComponentPool<T>* pool = GetPool<T>();
//	return pool->GetComponent(entity);
//}

//Get pool by ID.
IComponentPool* ComponentManager::GetPoolbyID(ComponentID id)
{
	assert(ComponentPoolReacher.find(id) != ComponentPoolReacher.end() && "Can not find pool by ID!");

	return ComponentPoolReacher.find(id)->second;
}

//Get component name by ComponentID.
// TODO: Find a better way to implement.
std::string_view ComponentManager::GetComponentName(ComponentID id)
{

	for (auto& pair : ComponentList)
	{
		if (pair.second == id)
		{
			return pair.first;
		}
	}


	return "null"; //?
}

////Get an entity's ComponentID by type name.
//template<typename T>
//ComponentID ComponentManager::GetComponentID()
//{
//	std::string_view type = type_name<T>();
//	assert(ComponentList.find(type) != ComponentList.end() && "Component not registered!");
//
//	return ComponentList.find(type)->second;
//}

//Get all registered components. This func will return a vector<string_view>.
// TODO: Find a better way to implement?
std::vector<std::string_view> ComponentManager::GetAllComponentsName()
{
	std::vector<std::string_view> vector;
	for (auto& pair : ComponentList)
	{
		vector.push_back(pair.first);
	}

	return vector;
}

//Function to print entity's specified component. Usefull for debugging.
void ComponentManager::PrintComponent(std::string_view type)
{
	auto pair = ComponentList.find(type.data());
	std::cout << "ID: " << pair->second << "\tName: " << pair->first << "\n";
}