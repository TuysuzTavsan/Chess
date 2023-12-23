#include <newECS/EntityManager.h>

#include <assert.h>

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{

}

Entity EntityManager::CreateEntity()
{
	assert(ID + 1 < MAX_ENTITES && "Too much entities!");

	Entity temp = ++ID;
	Signature sign;
	EntityPair pair(temp, sign);
	LivingEntites.insert(pair);
	return temp;
}

void EntityManager::FreeEntity(Entity entity)
{
	assert(LivingEntites.find(entity) != LivingEntites.end() && "Can not find entity to free.");

	//SELFNOTE: Remember to delete component data!

	LivingEntites.erase(entity);
}

void EntityManager::SetSignature(Entity entity, ComponentID ID, bool val)
{
	Signature sign = GetSignature(entity);
	sign.set(ID, val);
}

Signature& EntityManager::GetSignature(Entity entity)
{
	assert(LivingEntites.find(entity) != LivingEntites.end() && "Entity not found!");

	return LivingEntites.find(entity)->second;
}