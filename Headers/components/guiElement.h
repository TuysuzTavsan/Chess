#pragma once
#include <Types/vector.h>
#include <texture.h>
#include <string>

/*
Every graphical user interface related component will derive from this base class.
GUISystem will decide which GUIElement is hot and call its functions.
*/

struct GUIElement
{	
	Vec2 position; // left bottom position of the generic 2d graphical user component.
	Vec2 size; //Size in screen space coordinates.
	std::shared_ptr<float[]> vertices; // Generic rectangle vertices.
	bool hot; //Flag which indicates user might interract. example = Mouse cursor on the button...
	bool isAlreadyFocused; //Flag which indicates user focus already on the guiElement. If the focus just gained on that specific frame, this flag will become true untill focus lost.
	Texture bgTexture; //Plain background texture.
	Texture hotTexture; //Showed when the gui element is "hot".
	Texture activeTexture; //Showed when the gui element is active. Depends on the implementation and classes derived from this will override Active() func;

	virtual ~GUIElement() = default;

	/*
	Default constructor will use default position and size of Vec2(100,100).
	*/
	GUIElement(const Vec2& size = Vec2(100,100), const Vec2& position = Vec2(100,100))
		:
		position(position),
		size(size),
		vertices(new float[16] {
			position.x, position.y, 0.0f, 1.0f, // Top left
			position.x , position.y - (size.y), 0.0f, 0.0f, // Bottom left
			position.x + (size.x), position.y - (size.y), 1.0f, 0.0f,// Bottom right
			position.x + (size.x), position.y, 1.0f, 1.0f,// Top right
			}),
		hot{false},
		isAlreadyFocused{false}
	{

	}

	//Copy constructor.
	GUIElement(const GUIElement& other)
		:
		position{other.position},
		size{other.size},
		bgTexture{other.bgTexture},
		hotTexture{other.hotTexture},
		activeTexture{other.activeTexture},
		vertices{other.vertices}
	{
		//We have to update vertices to prevent multithread bugs.
		this->UpdateVertices();
	}

	////Move constructor.
	//GUIElement(GUIElement&& other) noexcept
	//	:
	//	position{std::move(other.position)},
	//	size{std::move(other.size)},
	//	bgTexture{std::move(other.bgTexture)},
	//	hotTexture{std::move(other.hotTexture)},
	//	activeTexture{std::move(other.activeTexture)},
	//	vertices{std::move(other.vertices)}
	//{
	//	//We have to update vertices to prevent multithread bugs.
	//	this->UpdateVertices();
	//}


	//copy assignment is prohibited.
	// TODO check!


	//Load bg texture from given path.
	bool SetBgTexture(const std::string& path)
	{
		return this->bgTexture.LoadTexture(path);
	}

	//Load hover texture from given path.
	bool SetHotTexture(const std::string& path)
	{
		return this->hotTexture.LoadTexture(path);
	}

	//Load active texture from given path.
	bool SetActiveTexture(const std::string& path)
	{
		return this->activeTexture.LoadTexture(path);
	}

	//Pure virtual function that will be called when the gui element is "hot".
	virtual void OnHot() = 0;

	//Pure virtual function that will be called once when the gui element becomes hot.
	virtual void OnFocusEntered() = 0;

	//Generic helper function to update vertices based on position and size.
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


};