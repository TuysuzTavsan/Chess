#pragma once

#include <scriptable.h>
#include <ecs/ECSManager.h>
#include <components/sprite.h>

class firstScript : public Scriptable
{
	int x = 0;

	virtual void Instantiate() override
	{

		ECSManager::getManager()->InsertComponent<Sprite>(this->instance, Sprite("Resources/kalp.png"));
		std::cout << "Hello Script\n";
	}

	virtual void Update(const float& dt) override
	{
		std::cout << "Updating script.\n";
		Sprite& sprite = ECSManager::getManager()->GetComponentData<Sprite>(this->instance);
		sprite.Move(Vec2(0.1, 0.1));
		if(sprite.position.x > 150)
		{
			this->endScene.Emmit();
		}
		
	}

	virtual void OnFree() override
	{
		std::cout << "Goodbye! I was a good script.\n";
	}

};
