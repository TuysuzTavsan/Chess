#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>
#include <bitset>
#include <string_view>
#include <map>
#include <assert.h>
#include <ecs/type_name.h>
#include <ecs/ecsTypes.h>

// TODO Fill the entity list on the startup?
namespace _Entity
{
	using namespace ECS;

	//Counter to give entities number.
	uint32_t ID = 0;
	//Map of currently alive entites and their signatures.
	std::map<Entity, Signature> LivingEntites;

	//Create entity with empty signature and return it.
	Entity CreateEntity()
	{
		assert(_Entity::ID + 1 < MAX_ENTITES && "Too much entities!");

		Entity temp = ++_Entity::ID;
		Signature sign;
		EntityPair pair(temp, sign);
		_Entity::LivingEntites.insert(pair);
		return temp;
	}

	//Get the specified entity's signature.
	Signature& GetSignature(const Entity& entity)
	{
		assert(LivingEntites.find(entity) != LivingEntites.end() && "Entity not found!");

		return LivingEntites.find(entity)->second;

	}	

} // namespace Entity



#endif // !ENTITY_H
