#ifndef COLOR_H
#define	COLOR_H

#include <vector.h>

/*
Class to work with Colors.
*/
struct Color
{
	float r, g, b, a;
	
	//Default constructor. Will set R G B A to 1.0f as default.
	explicit Color(const float& R = 1.0f, const float& G = 1.0f, const float& B = 1.0f, const float& A = 1.0f)
		: r(R), g(G), b(B), a(A)
	{

	}

	//Constructor that takes a vec3 to set R G B.
	explicit Color(const Vec3& vec3, const float& a = 1.0f)
		: r(vec3.x), g(vec3.y), b(vec3.z), a(a)
	{

	}

	//Copy constructor.
	Color(const Color& other)
	{
		this->r = other.r;
		this->g = other.g;
		this->b = other.b;
		this->a = other.a;
	}



	//Destructor
	~Color() {}

	// *********** OPERATOR OVERLOAD SECTION ***********

	//Assignment operator.
	void operator = (const Color& other)
	{
			this->r = other.r;
			this->g = other.g;
			this->b = other.b;
			this->a = other.a;

	}

	//plus operator.
	friend Color operator - (const Color& color1, const Color& color2)
	{
		return Color(color1.r - color2.r, color1.g - color2.g, color1.b - color2.b, color1.a - color2.a);
	}

	//multiply operator.
	friend Color operator * (const Color& color1, const Color& color2)
	{
		return Color(color1.r * color2.r, color1.g * color2.g, color1.b * color2.b, color1.a * color2.a);
	}

};

#endif // !COLOR_H

