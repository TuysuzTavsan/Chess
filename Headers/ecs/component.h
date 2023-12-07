#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
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
	uint16_t ID = 0;

	//List of defined components.
	std::map<std::string, ComponentID> ComponentList;

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
		ComponentList.insert({ str,id });
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
