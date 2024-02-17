#pragma once

#include <bitset>

//ComponentID is name alias for uint16
using ComponentID = uint16_t;
//SystemID is name alias for uint16_t
using SystemID = uint16_t;
//First element -> string view, Second element -> ComponentId.
using ComponentPair = std::pair<std::string_view, ComponentID>;
//Constant max component value. You can not exceed this number in runtime.
constexpr uint16_t MAX_COMPONENT = 32;
//Constant max entities number. You can not exceed this in runtime.
constexpr uint32_t MAX_ENTITES = 1000;
//Constant max system number. You can not exceed this in runtime.
constexpr uint16_t MAX_SYSTEMS = 64;
//Bitset to compare entity's components and communicate between entities.
using Signature = std::bitset<MAX_COMPONENT>;
//Entity is just an integer.
using Entity = uint32_t;
//EntityPair {Entity, Signature} is a helper type alias to use in map.
using EntityPair = std::pair<Entity, Signature>;

class EntityManager;
class ComponentManager;
class SystemManager;
class System;
struct IComponentPool;

template<typename T>
class ComponentPool;

class ECSM;

struct IComponentPool
{
	virtual ~IComponentPool() = default;
	virtual void EraseComponent(Entity entity) = 0;
};