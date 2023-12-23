#pragma once

#include <components/scriptable.h>
#include <components/mesh.h>

class firstScript : public Scriptable
{
	virtual void Instantiate() override
	{
		ECS::RegisterComponent<Mesh>(this->instance, Mesh{ 1,2,3 });
		std::cout << "Hello Script\n";
	}

	virtual void Update(const float& dt) override
	{
		std::cout << "Updating script.\n";
	}

	virtual void OnFree() override
	{
		std::cout << "Goodbye! I was a good script.\n";
	}

};
