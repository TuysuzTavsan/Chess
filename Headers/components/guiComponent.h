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

	GUIComponent(const Vec2& size = Vec2(100,100), const Vec2& position = Vec2(100,100))
		:
		position(position),
		size(size),
		vertices(new float[16] {
		position.x, position.y, 0.0f, 1.0f, // Top left
			position.x , position.y - (size.y), 0.0f, 0.0f, // Bottom left
			position.x + (size.x), position.y - (size.y), 1.0f, 0.0f,// Bottom right
			position.x + (size.x), position.y, 1.0f, 1.0f,// Top right
			})
	{

	}


	GUIComponent(const GUIComponent& other)
	{
		this->position = other.position;
		this->size = other.size;
		this->bgTexture = other.bgTexture;
		this->hoverTexture = other.hoverTexture;
		this->activeTexture = other.activeTexture;
		this->vertices = other.vertices;
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
		pvert[0] = position.x;
		pvert[1] = position.y;
		pvert[4] = position.x;
		pvert[5] = position.y - (size.y);
		pvert[8] = position.x + (size.x);
		pvert[9] = position.y - (size.y);
		pvert[12] = position.x + (size.x);
		pvert[13] = position.y;
	}


	virtual void OnActive() = 0;
};