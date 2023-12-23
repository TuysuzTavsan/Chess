#ifndef SYSTEM_H
#define SYSTEM_H

#include <ecs/component.h>
#include <ecs/type_name.h>

/*
* Systems are highly customisable. Users can define their systems that suits their needs.
* template T must match with the component type which system operate on.
*/
template<typename T>
class System
{
protected:
	_Component::ComponentPool<T> componentPool;

public:

	System()
	{
		_Component::RegisterComponent<T>(&this->componentPool);
	}

	//Attach component pool to the operating system.
	/*void AttachPool(_Component::ComponentPool<T>* poolPointer)
	{
		assert(poolPointer != nullptr && "Pointer is null!");
		assert(_Component::ComponentList.find(std::string(type_name<T>()))
			!= _Component::ComponentList.end()
			&& "Component is not registered!");

		pPool = poolPointer;
	}*/

	void InsertComponent(_Entity::Entity entity, const T& component)
	{
		componentPool.AddComponent(entity, component);
	}

	
};


#endif // !SYSTEM_H
