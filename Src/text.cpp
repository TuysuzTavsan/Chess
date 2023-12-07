#include <text.h>
#include <freetype/freetype.h>
#include <apl.h>

Text::Text()
	: Drawable2D(), Characters(), text(""), font_path("Resources/arial.ttf"), scale(1.0f), size(48.0)
{
	this->shader = SoftPtr<Shader>(new Shader("ShaderSrc/textVertex.glsl", "ShaderSrc/textFragment.glsl"));
	LoadFont(this->font_path, this-> size);

}

Text::~Text()
{
}

void Text::SetText(const char* text)
{
	this->text = text;
}

void Text::Render()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
	this->shader->use();
	glUniform3f(glGetUniformLocation(this->shader->ID, "textColor"),
									 this->color.r, this->color.g, this->color.b);
	
	glUniformMatrix4fv(glGetUniformLocation(
		this->shader->ID, "projection"), 1, GL_FALSE, &APL::Ortho.x.x);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	float x = position.x;
	float y = position.y;

	std::string::const_iterator c;

	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		float xpos = x + ch.Bearing.x * scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;
		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,    ypos + h,   0.0f, 0.0f },
			{ xpos,      ypos,       0.0f, 1.0f },
			{ xpos + w,  ypos,       1.0f, 1.0f },

			{ xpos,      ypos + h,   0.0f, 0.0f },
			{ xpos + w,  ypos,       1.0f, 1.0f },
			{ xpos + w,  ypos + h,   1.0f, 0.0f }
		};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 6 * 4, vertices); // be sure to use glBufferSubData and not glBufferData
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);
}

void Text::SetSize(const float& _size)
{
	if(_size <= 0)
	{
		std::cout << "Failed to set size! Negative parameter";
		return;
	}
	this->size = _size;
	LoadFont(this->font_path, this->size);
}

void Text::SetScale(const float& _scale)
{
	this->scale = _scale;
}

bool Text::SetFont(const std::string& path)
{
	this->font_path = path;
	return LoadFont(this->font_path, this->size);
}

bool Text::LoadFont(const std::string& path, const float& _size)
{
FT_Library ft;

	if (FT_Init_FreeType(&ft))
	{
		std::cout << "Failed to initialize FreeType library!";
		return false;
	}

	FT_Face face;
	if (FT_New_Face(ft, path.c_str(), 0, &face)) 
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return false;
	}
	else 
	{
		// set size to load glyphs as
		FT_Set_Pixel_Sizes(face, 0, static_cast<unsigned int>(_size));

		// disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		ClearGlyphs();

		// load first 128 characters of ASCII set
		for (unsigned char c = 0; c < 128; c++)
		{
			// Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// generate texture
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			// set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// now store character for later use
			Character character = {
				texture,
				Vec2((float)face->glyph->bitmap.width, (float)face->glyph->bitmap.rows),
				Vec2((float)face->glyph->bitmap_left, (float)face->glyph->bitmap_top),
				static_cast<unsigned int>(face->glyph->advance.x)
			};
			this->Characters.insert(std::pair<char, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	FT_Done_Face(face);
	FT_Done_FreeType(ft);


	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return true;
}

void Text::ClearGlyphs()
{
	for(auto& it : this->Characters)
	{
		glDeleteTextures(1, &it.second.TextureID);
	}
	this->Characters.clear();
}

void Text::ApplyChanges()
{
	
}