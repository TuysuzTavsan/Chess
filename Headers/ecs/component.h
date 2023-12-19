#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
#include <sstream>
#include <assert.h>
#include <map>
#include <vector>
#include <string_view>
#include <ecs/type_name.h>
#include <ecs/ecsTypes.h>

namespace _Component
{  
	using namespace ECS;

	//Counter to give ID to component types.
	inline uint16_t ID = 0;

	//List of defined components.
	inline std::map<std::string, ComponentID> ComponentList;
	inline std::map<ComponentID, IComponentPool*> ComponentPoolReacher;



	//Check if the component is already defined via RegisterComponent.
	template<typename T>
	bool IsComponentDefined()
	{
		return (ComponentList.find(std::string(type_name<T>())) == ComponentList.end());
	}

	//Register a component.
	template<typename T>
	void RegisterComponent(IComponentPool* componentPool)
	{
		std::string str(type_name<T>());
		assert(ID + 1 < MAX_COMPONENT && "Too much components!");
		assert(IsComponentDefined<T>() && "Component already registered!");
		ComponentID id = ++ID;;
		ComponentPoolReacher.insert({ id, componentPool });
		ComponentList.insert({ str,id });
	}

	void FreeComponent(const Entity& entity, const ComponentID& id)
	{
		assert(ComponentPoolReacher.find(id) != ComponentPoolReacher.end() && "Can not find componentPool to Free!");

		auto x = (ComponentPoolReacher.find(id)->second);
		x->EraseComponent(entity);
	}

	//Get a specified componentPool by a pointer.
	IComponentPool* GetPool(ComponentID id)
	{
		assert(ComponentPoolReacher.find(id) != ComponentPoolReacher.end() && "Can not find Pool!");
		return ComponentPoolReacher.find(id)->second;
	}

	//Get component name by ComponentID.
	// TODO: Find a better way to implement.
	std::string_view GetComponentName(ComponentID id)
	{

		for (auto& pair : ComponentList)
		{
			if (pair.second == id)
			{
				return pair.first;
			}
		}


		return "null";
	}

	//Get an entity's ComponentID by type name.
	ComponentID GetComponentID(std::string_view type)
	{
		assert(ComponentList.find(std::string(type)) != ComponentList.end() && "Component not registered!");

		return ComponentList.find(std::string(type))->second;
	}

	//Get all registered components. This func will return a vector<string_view>.
	// TODO: Find a better way to implement?
	std::vector<std::string_view> GetAllComponentsName()
	{
		std::vector<std::string_view> vector;
		for (auto& pair : ComponentList)
		{
			vector.push_back(pair.first);
		}

		return vector;
	}

	//Function to print entity's specified component. Usefull for debugging.
	void PrintComponent(std::string_view type)
	{
		auto pair = ComponentList.find(type.data());
		std::cout << "ID: " << pair->second << "\tName: " << pair->first << "\n";
	}


}// namespace Component





#endif // !COMPONENT_H
