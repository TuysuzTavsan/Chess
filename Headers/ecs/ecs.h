#ifndef ECS_H
#define ECS_H

#include <ecs/ecsTypes.h>
#include <ecs/entity.h>
#include <ecs/component.h>
#include <ecs/componentPool.h>
#include <ecs/system.h>

namespace ECS
{
	//Register a component.
	template<typename T>
	auto RegisterComponent = _Component::RegisterComponent<T>;
	
	//ComponentPool is a data holder struct for a component.
	template<typename T>
	using ComponentPool = _Component::ComponentPool<T>;

	//Create entity with empty signature.
	auto CreateEntity = _Entity::CreateEntity;


	//Add a component to specified entity's signature by type.
	template<typename T>
	void SignEntity(const Entity& entity)
	{
		assert(_Component::ComponentList.find(std::string(type_name<T>()))
			!= _Component::ComponentList.end()
			&& "Using component which is not registered yet!");

		ComponentID compID = _Component::GetComponentID(type_name<T>());
		Signature& sign = _Entity::GetSignature(entity);
		sign.set(compID, true);

	}

	//Returns vector<string_view> component list for an entity.
	//Debug helper function.
	std::vector<std::string_view> GetComponentList(const Entity& entity)
	{
		std::vector<std::string_view> vector;

		Signature sign = _Entity::GetSignature(entity);

		for (auto& pair : _Component::ComponentList)
		{
			if (sign.test(pair.second))
			{
				vector.push_back(std::string_view(pair.first));
			}
		}

		return vector;
	}

	//Debug helper function.
	void PrintAllComponent(const Entity& entity)
	{
		auto list = GetComponentList(entity);

		for (auto& name : list)
		{
			std::cout << "\n\t" << name.data() << "\n";
		}
	}

} // namespace ECS


#endif // !ECS_H
