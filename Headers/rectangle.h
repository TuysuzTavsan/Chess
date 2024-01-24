#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <drawable2D.h>
#include <vector.h>
#include <texture.h>

class Rectangle : public Drawable2D
{
	Vec2 topLeft;
	Vec2 bottomRight;
	Vec2 size; // (width, length)
	Texture texture0;
public:
	

	/*
	Default constructor.
	Will assing vertex array pointer, element array pointer to draw rectangle on Heap.
	*/
	Rectangle();
	Rectangle(const Vec2& size);

	//Copy constructor
	Rectangle(Rectangle& copy);
	//Assignment operator
	Rectangle& operator=(const Rectangle& other);
	//Rectangle(const Vec2& top_right, const Vec2& bottom_left);

	bool LoadTexture(const std::string& path);


	~Rectangle();
	void SetCorner(const Vec2& top_left, const Vec2& bottom_right);
	void ApplyChanges() override;
	void Render() override;
};


#endif // !1
