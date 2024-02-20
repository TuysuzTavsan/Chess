#pragma once

#include <scriptable.h>
#include <ecs/ECSM.h>
#include <components/button.h>

class backMainButton : public Scriptable
{

	virtual void Instantiate() override
	{

		ECSM::InsertComponent<Button>(this->instance, Button("Main Menu",
			Vec2(200, 100), Vec2(180, 80), "Resources/gui/Button/Rect/Default@2x.png"));
		Button& button = ECSM::GetComponentData<Button>(this->instance);
		button.SetHotTexture("Resources/gui/Button/Rect/Hover@2x.png");
		button.buttonPressed.Connect([this]() {buttonClicked(); });
		button.SetActiveTexture("Resources/gui/Button/Rect/Active@2x.png");

	}

	void buttonClicked()
	{
		std::cout << "Button Clicked! Source: SettingsButton\n";
		APL::audioManager.Request("Resources/click3.wav", AudioAttribute::playLoop, 0.5f);


		APL::sceneManager.Request("settings", SceneRequestType::stop);
		APL::sceneManager.Request("main", SceneRequestType::start);
		

	}

	virtual void Update(const float& dt) override
	{

	}

	virtual void OnFree() override
	{
		std::cout << "Goodbye! I was a good script.\n";
	}

};