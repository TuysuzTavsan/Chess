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





struct Button : GUIComponent
{
	Text text;
	Signal<void> buttonPressed;
	Signal<void> buttonReleased;

	Button(Button& other)
		: GUIComponent(other)
	{

		this->text = other.text;
	}

	Button(const std::string& text, const Vec2& position, const Vec2& size, std::string bgTexture)
		: GUIComponent()
	{
		this->size = size;
		this->text.SetText(text.c_str());
		this->position = position;
		this->bgTexture.LoadTexture(bgTexture);
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
			buttonPressed.Emmit();
			break;
		}
	}


};