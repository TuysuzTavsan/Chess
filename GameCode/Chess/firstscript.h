#pragma once

#include <scriptable.h>
#include <ecs/ECSManager.h>
#include <components/sprite.h>

class MenuBackGround : public Scriptable
{
	int x = 0;

	virtual void Instantiate() override
	{

		ECSManager::getManager()->InsertComponent<Sprite>(this->instance, Sprite("Resources/background2.jpg"));
		Sprite& sprite = ECSManager::getManager()->GetComponentData<Sprite>(this->instance);
		sprite.SetSize(Vec2(static_cast<float>(APL::WINDOW_WIDTH), static_cast<float>(APL::WINDOW_HEIGHT)));
		sprite.SetPosition(Vec2(0, static_cast<float>(APL::WINDOW_HEIGHT)));
	}

	virtual void Update(const float& dt) override
	{
		
	}

	virtual void OnFree() override
	{
		std::cout << "Goodbye! I was a good script.\n";
	}

};
