#pragma once


#include <scriptable.h>
#include <ecs/ECSManager.h>
#include <components/button.h>

class ButtonScript : public Scriptable
{
	int x = 0;

	virtual void Instantiate() override
	{

		ECSManager::getManager()->InsertComponent<Button>(this->instance, Button("Fuat", Vec2(300,400), Vec2(100,50), 
			"Resources/Default.png"));
		Button& button = ECSManager::getManager()->GetComponentData<Button>(this->instance);
		button.SetHoverTexture("Resources/Hover.png");
	}

	virtual void Update(const float& dt) override
	{
		//Button& button = ECSManager::getManager()->GetComponentData<Button>(this->instance);
		
	}

	virtual void OnFree() override
	{
		std::cout << "Goodbye! I was a good script.\n";
	}

};