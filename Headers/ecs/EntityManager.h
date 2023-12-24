#pragma once

#include <ecs/ecsTypes.h>

#include <map>


class EntityManager
{
public:

	EntityManager();
	~EntityManager();

	Entity CreateEntity();
	void FreeEntity(Entity entity);
	void SetSignature(Entity entity,ComponentID ID, bool set);
	Signature& GetSignature(Entity entity);
	bool HasEntity(Entity entity);
	bool HasComponent(Entity entity, ComponentID id);

private:


	//Counter to give entities number.
	uint32_t ID = 0;
	//Map of currently alive entites and their signatures.
	std::map<Entity, Signature> LivingEntites;

};