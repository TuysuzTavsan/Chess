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