#pragma once
#include <string>
#include <Types/vector.h>
#include <Types/color.h>
#include <apl.h>
#include <glfw/glfw3.h>
#include <signal.h>
#include <texture.h>

#include <components/guiElement.h>

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



struct Button : GUIElement
{
	Text text;
	Signal<void> buttonPressed;
	Signal<void> buttonReleased;
	bool pressed = false;
	

	Button(const Button& other)
		: GUIElement(other)
	{
		this->text = other.text;
	}

	Button(const std::string& text, const Vec2& position, const Vec2& size, std::string bgTexture)
		: GUIElement(size, position)
	{
		this->text.SetText(text.c_str());
		this->bgTexture.LoadTexture(bgTexture);
		this->text.FitInBox(this->position, this->size);
		this->UpdateVertices();
		
	}

	Button(const std::string& text, const Vec2& position, const Vec2& size, std::string bgTexture, std::string hotTexture)
		: GUIElement()
	{
		this->size = size;
		this->text.SetText(text.c_str());
		this->position = position;
		this->bgTexture.LoadTexture(bgTexture);
		this->hotTexture.LoadTexture(hotTexture);
		this->text.FitInBox(this->position, this->size);
		this->UpdateVertices();
	}

	Button(const std::string& text, const Vec2& position, const Vec2& size, std::string bgTexture, std::string hotTexture, std::string activeTexture)
		: GUIElement()
	{
		this->size = size;
		this->text.SetText(text.c_str());
		this->position = position;
		this->bgTexture.LoadTexture(bgTexture);
		this->hotTexture.LoadTexture(hotTexture);
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

	void OnHot() override
	{
		switch (glfwGetMouseButton(APL::window, GLFW_MOUSE_BUTTON_LEFT))
		{
		case GLFW_RELEASE:
			buttonReleased.Emmit();
			pressed = false;
			break;
		case GLFW_PRESS:
			if (!pressed)
			{
				buttonPressed.Emmit();
				pressed = true;
			}
			break;
		default: pressed = false;
		}
	}

	void OnFocusEntered() override
	{
		APL::audioManager.Request("Resources/rollover5.wav", AudioAttribute::playLoop, 0.5f);
	}
};