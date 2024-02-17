#pragma once


#include <scriptable.h>
#include <ecs/ECSM.h>
#include <components/button.h>

class PlayButton : public Scriptable
{
	int x = 0;

	virtual void Instantiate() override
	{

		ECSM::InsertComponent<Button>(this->instance, Button("PLAY",
			Vec2(300, 380), Vec2(200, 100), "Resources/gui/Button/Rect/Default@2x.png"));
		Button& button = ECSM::GetComponentData<Button>(this->instance);
		button.SetHoverTexture("Resources/gui/Button/Rect/Hover@2x.png");
		button.buttonPressed.Connect([this]() {buttonClicked(); });
		button.SetActiveTexture("Resources/gui/Button/Rect/Active@2x.png");
		
	}

	void buttonClicked()
	{
		std::cout << "Button Clicked! Source: PlayButton\n";
		APL::audioManager.Request("Resources/click3.wav", AudioAttribute::playLoop, 0.5f);
	}

	virtual void Update(const float& dt) override
	{
		
	}

	virtual void OnFree() override
	{
		std::cout << "Goodbye! I was a good script.\n";
	}

};