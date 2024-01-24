#pragma once
#include <Types/vector.h>
#include <memory>
#include <texture.h>


struct Sprite
{
	Vec3 position;
	Vec2 size;
	std::shared_ptr<float[]> vertices;
	Texture texture;

	Sprite()
	:
	position(100.0, 100.0, 0.0),
	size(100,100),
	vertices(new float[16]{
			position.x - (size.x / 2), position.y + (size.y / 2), 0.0f, 1.0f, // Top left
			position.x - (size.x / 2), position.y - (size.y / 2), 0.0f, 0.0f, // Bottom left
			position.x + (size.x / 2), position.y - (size.y / 2), 1.0f, 0.0f,// Bottom right
			position.x + (size.x / 2), position.y + (size.y / 2), 1.0f, 1.0f,// Top right
	})
	{
		
	}

	Sprite(const std::string& path)
	:
	position(100.0, 100.0, 0.0),
	size(100,100),
	vertices(new float[16]{
			position.x - (size.x / 2), position.y + (size.y / 2), 0.0f, 1.0f, // Top left
			position.x - (size.x / 2), position.y - (size.y / 2), 0.0f, 0.0f, // Bottom left
			position.x + (size.x / 2), position.y - (size.y / 2), 1.0f, 0.0f,// Bottom right
			position.x + (size.x / 2), position.y + (size.y / 2), 1.0f, 1.0f// Top right
	})
	{
		texture.LoadTexture(path);
	}


	bool LoadTexture(const std::string& path)
	{
		return this->texture.LoadTexture(path);
	}

	unsigned int GetTexture()
	{
		if(texture.IsLoaded())
		{
			return texture.GetTextureData();
		}
		return 0;
	}

	void Move(const Vec2& vec2)
	{
		this->position.x += vec2.x;
		this->position.y += vec2.y;
		UpdateVertices();
	}

	private:

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
};