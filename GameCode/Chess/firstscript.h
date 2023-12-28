#pragma once

#include <scriptable.h>
#include <ecs/ECSManager.h>
#include <components/sprite.h>

class firstScript : public Scriptable
{
	int x = 0;

	virtual void Instantiate() override
	{
		Sprite sprite;
		sprite.texture.LoadTexture("Resources/kalp.png");
		sprite.vertices = new float[16]
		{
			0.5f, 0.5f, 0.0f, 1.0f, // Top left
			0.5f, -0.5f, 0.0f, 0.0f, // Bottom left
			-0.5f, -0.5f, 1.0f, 0.0f,// Bottom right
			-0.5f, 0.5f, 1.0f, 1.0f,// Top right

		};

		ECSManager::getManager()->InsertComponent<Sprite>(this->instance, sprite);
		std::cout << "Hello Script\n";
	}

	virtual void Update(const float& dt) override
	{
	
		std::cout << "Updating script.\n";
	}

	virtual void OnFree() override
	{
		std::cout << "Goodbye! I was a good script.\n";
	}

};
