#ifndef TEXT_H
#define TEXT_H

#include <drawable2D.h>

#include <map>

/*
Struct to hold our preloaded Character glyphs.
Format: TextureID, Size, Bearing, Advance.
*/
struct Character {
	unsigned int TextureID; // ID handle of the glyph texture
	Vec2 Size;      // Size of glyph
	Vec2 Bearing;   // Offset from baseline to left/top of glyph
	unsigned int Advance;   // Horizontal offset to advance to next glyph
};

/*
Text class to load font and draw strings to screen.
*/
class Text : public Drawable2D{

	std::map<char, Character> Characters; //Map of our preloaded characters.
	std::string text; //String to print.
	std::string font_path; //Path to font
	float scale; //Scaling factor.
	float size; //Size of text.

public:

	//Default Constructor.
	Text();
	//Destructor.
	~Text();

	//Set text.
	void SetText(const char* text);
	//This method needs to be overridden to update vertices.
	void ApplyChanges() override;
	//Overrided rendering method.
	void Render() override;
	//Set size of font and load.
	void SetSize(const float& size);
	//Set scale.
	void SetScale(const float& scale);
	//Set and load new font.
	bool SetFont(const std::string& path);

private:

	//Load font from path and specified size.
	bool LoadFont(const std::string& path, const float& size);
	//Clear Glyph table. Meaning reset this->Characters.
	void ClearGlyphs();
};


#endif // !TEXT_H
