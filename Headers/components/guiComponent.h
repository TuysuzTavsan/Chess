#pragma once
#include <Types/vector.h>
#include <texture.h>
#include <string>


struct GUIComponent
{
	
	Texture bgTexture;
	Texture hoverTexture;
	Texture activeTexture;
	Vec2 position;
	Vec2 size;
	std::shared_ptr<float[]> vertices;

	virtual ~GUIComponent() = default;

	GUIComponent()
		:
		position(100.0, 100.0),
		size(100, 100),
		vertices(new float[16] {
		position.x - (size.x / 2), position.y + (size.y / 2), 0.0f, 1.0f, // Top left
			position.x - (size.x / 2), position.y - (size.y / 2), 0.0f, 0.0f, // Bottom left
			position.x + (size.x / 2), position.y - (size.y / 2), 1.0f, 0.0f,// Bottom right
			position.x + (size.x / 2), position.y + (size.y / 2), 1.0f, 1.0f,// Top right
			})
	{

	}

	GUIComponent(GUIComponent& other)
	{
		this->position = other.position;
		this->size = other.size;
		this->bgTexture = other.bgTexture;
		this->hoverTexture = other.hoverTexture;
		this->activeTexture = other.activeTexture;
		this->UpdateVertices();
	}

	void SetBgTexture(const std::string& path)
	{
		this->bgTexture.LoadTexture(path);
	}

	void SetHoverTexture(const std::string& path)
	{
		this->hoverTexture.LoadTexture(path);
	}

	void SetActiveTexture(const std::string& path)
	{
		this->activeTexture.LoadTexture(path);
	}

	void UpdateVertices()
	{
		float* pvert = vertices.get();
		pvert[0] = position.x - (size.x / 2);
		pvert[1] = position.y + (size.y / 2);
		pvert[4] = position.x - (size.x / 2);
		pvert[5] = position.y - (size.y / 2);
		pvert[8] = position.x + (size.x / 2);
		pvert[9] = position.y - (size.y / 2);
		pvert[12] = position.x + (size.x / 2);
		pvert[13] = position.y + (size.y / 2);
	}


	virtual void OnActive() = 0;
};