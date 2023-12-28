#pragma once
#include <Types/vector.h>
#include <texture.h>


struct Sprite
{
	Vec3 position;
	Vec2 size;
	float* vertices;
	Texture texture;
};