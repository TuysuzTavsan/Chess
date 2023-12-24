#pragma once

#include <components/scriptable.h>
#include <components/mesh.h>
#include <newECS/ECSManager.h>

class firstScript : public Scriptable
{
	virtual void Instantiate() override
	{
		ECSManager::getManager()->InsertComponent(this->instance, Mesh{1, 2, 3});
		std::cout << "Hello Script\n";
	}

	virtual void Update(const float& dt) override
	{
		std::cout << "Updating script.\n";
		Mesh& mesh = ECSManager::getManager()->GetComponentData<Mesh>(this->instance);
		mesh.x++;
		mesh.y++;
		mesh.z++;
	}

	virtual void OnFree() override
	{
		std::cout << "Goodbye! I was a good script.\n";
	}

};
