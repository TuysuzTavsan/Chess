#pragma once
#include <string>
#include <Types/vector.h>
#include <Types/color.h>
#include <apl.h>
#include <glfw/glfw3.h>
#include <signal.h>
#include <texture.h>

#include <components/guiComponent.h>

//todo fix this
#include <text.h>

/*
Implementing general purpose button component is hard.
I will only implement this one. Which will need at least 3 texture to use.
1- normal state texture
2- hover texture
3- active texture
if you do not provide any of them it will render black box instead of nothing.

Text will be aligned to start from middle and left point of the button always.
*/



struct Button : GUIComponent
{
	Text text;
	Signal<void> buttonPressed;
	Signal<void> buttonReleased;
	

	Button(const Button& other)
		: GUIComponent(other)
	{
		this->text = other.text;
	}

	Button(const std::string& text, const Vec2& position, const Vec2& size, std::string bgTexture)
		: GUIComponent(size, position)
	{
		this->text.SetText(text.c_str());
		this->bgTexture.LoadTexture(bgTexture);
		this->text.FitInBox(this->position, this->size);
		this->UpdateVertices();
		
	}

	Button(const std::string& text, const Vec2& position, const Vec2& size, std::string bgTexture, std::string hoverTexture)
		: GUIComponent()
	{
		this->size = size;
		this->text.SetText(text.c_str());
		this->position = position;
		this->bgTexture.LoadTexture(bgTexture);
		this->hoverTexture.LoadTexture(hoverTexture);
		this->text.FitInBox(this->position, this->size);
		this->UpdateVertices();
	}

	Button(const std::string& text, const Vec2& position, const Vec2& size, std::string bgTexture, std::string hoverTexture, std::string activeTexture)
		: GUIComponent()
	{
		this->size = size;
		this->text.SetText(text.c_str());
		this->position = position;
		this->bgTexture.LoadTexture(bgTexture);
		this->hoverTexture.LoadTexture(hoverTexture);
		this->activeTexture.LoadTexture(activeTexture);
		this->text.FitInBox(this->position, this->size);
		this->UpdateVertices();
	}


	void SetText(const std::string& text)
	{
		this->text.SetText(text.c_str());
	}

	void SetTextColor(const Color& color)
	{
		this->text.SetColor(color);
	}

	void SetTextSize(const float& size)
	{
		this->text.SetSize(size);
	}

	void OnActive() override
	{
		switch (glfwGetMouseButton(APL::window, GLFW_MOUSE_BUTTON_LEFT))
		{
		case GLFW_RELEASE:
			buttonReleased.Emmit();
			break;
		case GLFW_PRESS:
			if(!active)
				buttonPressed.Emmit();
			active = true;
			break;
		}
	}

	void OnHot() override
	{
		APL::audioManager.Request("Resources/rollover5.wav", AudioAttribute::playLoop, 0.5f);
	}
};