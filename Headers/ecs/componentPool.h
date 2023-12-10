#ifndef COMPONENT_POOL_H
#define COMPONENT_POOL_H

#include <ecs/ecsTypes.h>
#include <map>
#include <vector>
#include <ecs/entity.h>
#include <ecs/component.h>


namespace _Component
{
	/*
* ComponentPool is responsible for the templated component type data.
* Data is contigous, however ordering is not promised!
*/
	template<typename T>
	struct ComponentPool : IComponentPool
	{
		using Index = uint32_t; //Type alias.
		Index counter; //Counter to count last component index on the pool.
		std::map<_Entity::Entity, Index> EntityToIndex; //Entity to index map. Warning: We store counter. Not counter -1.
		std::vector<T> pool; //Actual data pool.

		ComponentPool() : counter(0)
		{
			pool.reserve(MAX_ENTITES);
		}

		~ComponentPool() {}

		/*
		* Insert the data to the pool.
		* Increase the counter by 1.
		*/
		void InsertComponent(_Entity::Entity entity, const T& component)
		{
			assert((counter + 1) < MAX_ENTITES && "Pool is full!");
			pool.push_back(component);
			++counter;
			EntityToIndex.insert({ entity, counter });
			SignEntity<T>(entity);
		}

		/*
		* Erase the component data from the pool.
		* Hole in the pool will be filled with the last element on the pool.
		* Therefore contigous data on the pool is guarenteed.
		*/
		void EraseComponent(const Entity& entity) override
		{
			assert(_Entity::LivingEntites.find(entity) != _Entity::LivingEntites.end()
				&& EntityToIndex.find(entity) != EntityToIndex.end()
				&& "Entity does not exist or does not have specified component!");

			Index deletedIndex = EntityToIndex.find(entity)->second;
			Index lastIndex = counter;
			pool[deletedIndex - 1] = pool[lastIndex - 1];
			EntityToIndex.erase(entity);
			counter--;

			for (auto& pair : EntityToIndex)
			{
				if (pair.second == lastIndex)
				{
					pair.second = deletedIndex;
					break;
				}
			}

		}

		/*
		* Get the component data that an entity has.
		* Warning: This function will return a reference to component data.
		*/
		void* GetComponent(const Entity& entity) override
		{
			assert(_Entity::LivingEntites.find(entity) != _Entity::LivingEntites.end()
				&& EntityToIndex.find(entity) != EntityToIndex.end()
				&& "Entity does not exist or does not have specified component!");

			Index index = EntityToIndex.find(entity)->second;
			return &pool[index - 1];

		}
	};
}


#endif // COMPONENT_POOL_H
