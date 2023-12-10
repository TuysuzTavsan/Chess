#ifndef ECS_TYPES_H
#define ECS_TYPES_H

#include <bitset>

namespace ECS
{
	//ComponentID is name alias for uint16
	using ComponentID = uint16_t;
	//First element -> string view, Second element -> ComponentId.
	using ComponentPair = std::pair<std::string_view, ComponentID>;
	//Constant max component value. You can not exceed this number in runtime.
	constexpr uint16_t MAX_COMPONENT = 32;
	//Constant max entities number. You can not exceed this in runtime.
	constexpr uint32_t MAX_ENTITES = 1000;
	//Bitset to compare entity's components and communicate between entities.
	using Signature = std::bitset<MAX_COMPONENT>;
	//Entity is just an integer.
	using Entity = uint32_t;
	//EntityPair {Entity, Signature} is a helper type alias to use in map.
	using EntityPair = std::pair<Entity, Signature>;

	struct IComponentPool
	{
		virtual ~IComponentPool() = default;
		virtual void EraseComponent(const Entity& entity) = 0;
		virtual void* GetComponent(const Entity& entity) = 0;
	};
}




#endif // !ECS_TYPES_H
