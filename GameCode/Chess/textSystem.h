#pragma once
#include <ecs/System.h>
#include <glad/glad.h>
#include <Types/vector.h>
#include <map>
#include <freetype/freetype.h>
#include <shader.h>

/*
Struct to hold our preloaded Character glyphs.
Format: TextureID, Size, Bearing, Advance.
*/
struct Character {
	unsigned int textureID; // ID handle of the glyph texture
	Vec2 size;      // Size of glyph
	Vec2 bearing;   // Offset from baseline to left/top of glyph
	unsigned int advance;   // Horizontal offset to advance to next glyph
};


class TextSystem : public System
{
    Shader shader;
    std::map<char, Character> characters; //Map of our preloaded characters.
    std::string fontPath; //Path to font

public:

};