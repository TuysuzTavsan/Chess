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
	auto RegisterComponent = 
	
	//ComponentPool is a data holder struct for a component.
	template<typename T>
	using ComponentPool = _Component::ComponentPool<T>;

	void FreeEntity(const Entity& entity)
	{
		assert(_Entity::LivingEntites.find(entity) != _Entity::LivingEntites.end() 
			&& "Can not find entity to free.");
		Signature sign = _Entity::LivingEntites.find(entity)->second;

		for (int i = 0; i < MAX_COMPONENT; i++)
		{
			if (sign.test(i))
			{
				_Component::FreeComponent(entity, i);
			}
		}

		_Entity::LivingEntites.erase(entity);
	}

	//Create entity with empty signature.
	auto CreateEntity = _Entity::CreateEntity;

	//Get a entity's component by a reference.
	template<typename T>
	T* GetComponent(const Entity& entity)
	{
		IComponentPool* pPool = _Component::GetPool(_Component::GetComponentID(type_name<T>()));
		return (T*)(pPool->GetComponent(entity));
	}

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
