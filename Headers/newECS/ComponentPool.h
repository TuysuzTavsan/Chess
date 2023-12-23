#pragma once
#include <newECS/necsTypes.h>
#include <vector>
#include <map>
#include <assert.h>

/*
* ComponentPool is responsible for the templated component type data.
* Data is contigous, however ordering is not promised!
*/
template<typename T>
class ComponentPool : public IComponentPool
{
public:

	ComponentPool()
	{
		pool.reserve(MAX_ENTITES);
	}

	~ComponentPool()
	{

	}

	/*
	* Insert the data to the pool.
	* Increase the counter by 1.
	*/
	void AddComponent(Entity entity, T component) 
	{
		assert((counter + 1) < MAX_ENTITES && "Pool is full!");
		pool.push_back(component);
		++counter;
		EntityToIndex.insert({ entity, counter });

		//remember to sign entity!
	}

	/*
	* Erase the component data from the pool.
	* Hole in the pool will be filled with the last element on the pool.
	* Therefore contigous data on the pool is guarenteed.
	*/
	void EraseComponent(Entity entity) override
	{
		//Remember to assert this!
		//assert(_Entity::LivingEntites.find(entity) != _Entity::LivingEntites.end()
		//	&& EntityToIndex.find(entity) != EntityToIndex.end()
		//	&& "Entity does not exist or does not have specified component!");

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
	T& GetComponent(Entity entity)
	{
		//Remember to assert!
		//assert(_Entity::LivingEntites.find(entity) != _Entity::LivingEntites.end()
		//	&& EntityToIndex.find(entity) != EntityToIndex.end()
		//	&& "Entity does not exist or does not have specified component!");

		Index index = EntityToIndex.find(entity)->second;
		return &pool[index - 1];

	}

private:
	
	using Index = uint32_t; // type alias.
	Index counter; //Counter to count last component index on the pool.
	std::map<Entity, Index> EntityToIndex; //Entity to index map. Warning: We store counter. Not counter -1.
	std::vector<T> pool; //Actual data pool.

};
