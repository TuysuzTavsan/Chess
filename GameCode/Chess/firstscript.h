#pragma once

#include <scriptable.h>
#include <ecs/ECSManager.h>

class firstScript : public Scriptable
{
	int x = 0;

	virtual void Instantiate() override
	{
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
