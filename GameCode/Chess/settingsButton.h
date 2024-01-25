#pragma once



#include <scriptable.h>
#include <ecs/ECSManager.h>
#include <components/button.h>

class SettingsButton : public Scriptable
{
	int x = 0;

	virtual void Instantiate() override
	{
		
		ECSManager::getManager()->InsertComponent<Button>(this->instance, Button("Settings",
			Vec2(310, 270), Vec2(180, 80), "Resources/gui/Button/Rect/Default@2x.png"));
		Button& button = ECSManager::getManager()->GetComponentData<Button>(this->instance);
		button.SetHoverTexture("Resources/gui/Button/Rect/Hover@2x.png");
		button.buttonPressed.Connect([this]() {buttonClicked(); });
		button.SetActiveTexture("Resources/gui/Button/Rect/Active@2x.png");

	}

	void buttonClicked()
	{
		std::cout << "Button Clicked! Source: SettingsButton\n";
	}

	virtual void Update(const float& dt) override
	{

	}

	virtual void OnFree() override
	{
		std::cout << "Goodbye! I was a good script.\n";
	}

};