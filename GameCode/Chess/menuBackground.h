#pragma once

#include <scriptable.h>
#include <ecs/ECSM.h>
#include <components/sprite.h>

class MenuBackGround : public Scriptable
{

	virtual void Instantiate() override
	{

		ECSM::InsertComponent<Sprite>(this->instance, Sprite("Resources/background2.jpg"));
		Sprite& sprite = ECSM::GetComponentData<Sprite>(this->instance);
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
