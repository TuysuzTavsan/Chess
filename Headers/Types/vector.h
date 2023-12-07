#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

/*
Vec3 class.
*/
struct Vec3
{
	float x; //First value of Vec3.
	float y; //Second value of Vec3.
	float z; //Third value of Vec3.

	//Default constructor. Default values are 0.0f.
	explicit Vec3(const float& X = 0.0f, const float& Y = 0.0f, const float& Z = 0.0f)
		: x(X), y(Y), z(Z)
	{};

	//Destructor.
	~Vec3() {};


	// @@@@@@@@@@@@@@@@@@@@@ Operator overloads @@@@@@@@@@@@@@@@@@@@@

	//plus equal operator.
	Vec3& operator+=(const Vec3& other)
	{
		if (this != &other)
		{
			this->x = other.x + this->x;
			this->y = other.y + this->y;
			this->z = other.z + this->z;
		}

		return *this;
	}

	//minus equal operator.
	Vec3& operator-=(const Vec3& other)
	{
		if (this != &other)
		{
			this->x = other.x - this->x;
			this->y = other.y - this->y;
			this->z = other.z - this->z;
		}

		return *this;
	}


	//plus operator.
	friend Vec3 operator+(const Vec3& vec3_a, const Vec3& vec3_b)
	{
		return Vec3(vec3_a.x + vec3_b.x, vec3_a.y + vec3_b.y, vec3_a.z + vec3_b.z);
	}
	
	//extraction operator.
	friend Vec3 operator-(const Vec3& vec3_a, const Vec3& vec3_b)
	{
		return Vec3(vec3_a.x - vec3_b.x, vec3_a.y - vec3_b.y, vec3_a.z - vec3_b.z);
	}

	//multiply operator.
	friend Vec3 operator*(const Vec3&  vec3_a, const Vec3& vec3_b)
	{
		return Vec3(vec3_a.x * vec3_b.x, vec3_a.y * vec3_b.y, vec3_a.z * vec3_b.z);
	}

	//multiply operator.
	friend Vec3 operator*(const Vec3& vec3_a, const float& multiplier)
	{
		return Vec3(vec3_a.x * multiplier, vec3_a.y * multiplier, vec3_a.z * multiplier);
	}

	//divide operator. Will check for value 0. If 0 will throw error.
	friend Vec3 operator/(const Vec3& vec3_a, const Vec3& vec3_b)
	{

		if (vec3_b.x == 0.0f || vec3_b.y == 0.0f || vec3_b.z == 0.0f)
		{
			std::string error = "Vec3 divide operator exception: Attampted to divide by Zero\n";
			std::cout << error;
			throw (error);
		}

		return Vec3(vec3_a.x / vec3_b.x, vec3_a.y / vec3_b.y, vec3_a.z / vec3_b.z);
	}

	//divide operator. Will check for value 0. If 0 will throw error.
	friend Vec3 operator/(const Vec3& vec3_a, const float& divider)
	{
		if (divider == 0.0f)
		{
			std::string error = "Vec3 divide operator exception: Attampted to divide by Zero\n";
			std::cout << error;
			throw (error);
		}

		return Vec3(vec3_a.x / divider, vec3_a.y / divider, vec3_a.z / divider);
	}

	/*
	<< operator to print x y and z.
	Format: "x: 11 y: 22 z: 33" + new line.
	*/
	friend std::ostream& operator << (std::ostream& out, const Vec3& vec)
	{
		out << "x: " << vec.x << " y: " << vec.y << " z: " << vec.z << "\n";
		return out;
	}

	/*
	>> operator to accept input.
	Format: >> x >> y >> z
	*/
	friend std::istream& operator >> (std::istream& in, Vec3& vec)
	{
		in >> vec.x >> vec.y >> vec.z;
		return in;
	}
};


/*
Vec2 Class.
*/
struct Vec2
{
	float x; //First value of Vec2.
	float y; //Second value of Vec2.

	//Default constructor. All default values are 0.0f.
	explicit Vec2(const float& X = 0.0f, const float& Y = 0.0f)
		: x(X), y(Y)
	{};

	//Destructor.
	~Vec2() {};


	// @@@@@@@@@@@@@@@@@@@@@ Operator overloads @@@@@@@@@@@@@@@@@@@@@

	//plus equal operator.
	Vec2& operator+=(const Vec2& other)
	{
		if (this != &other)
		{
			this->x = other.x + this->x;
			this->y = other.y + this->y;

		}

		return *this;
	}

	//minues equal operator.
	Vec2& operator-=(const Vec2& other)
	{
		if (this != &other)
		{
			this->x = other.x - this->x;
			this->y = other.y - this->y;

		}

		return *this;
	}

	//plus operator.
	friend Vec2 operator+(const Vec2& vec2_a, const Vec2& vec2_b)
	{
		return Vec2(vec2_a.x + vec2_b.x, vec2_a.y + vec2_b.y);
	}

	//extraction operator.
	friend Vec2 operator-(const Vec2& vec2_a, const Vec2& vec2_b)
	{
		return Vec2(vec2_a.x - vec2_b.x, vec2_a.y - vec2_b.y);
	}

	//multiply operator.
	friend Vec2 operator*(const Vec2& vec2_a, const Vec2& vec2_b)
	{
		return Vec2(vec2_a.x * vec2_b.x, vec2_a.y * vec2_b.y);
	}

	//multiply operator.
	friend Vec2 operator*(const Vec2& vec2_a, const float& multiplier)
	{
		return Vec2(vec2_a.x * multiplier, vec2_a.y * multiplier);
	}

	//divide operator. Will check for value 0. If 0 will throw error.
	friend Vec2 operator/(const Vec2& vec2_a, const Vec2& vec2_b)
	{

		if (vec2_b.x == 0.0f || vec2_b.y == 0.0f)
		{
			std::string error = "Vec2 divide operator exception: Attampted to divide by Zero\n";
			std::cout << error;
			throw (error);
		}

		return Vec2(vec2_a.x / vec2_b.x, vec2_a.y / vec2_b.y);
	}

	//divide operator. Will check for value 0. If 0 will throw error.
	friend Vec2 operator/(const Vec2& vec2_a, const float& divider)
	{
		if (divider == 0.0f)
		{
			std::string error = "Vec2 divide operator exception: Attampted to divide by Zero\n";
			std::cout << error;
			throw (error);
		}

		return Vec2(vec2_a.x / divider, vec2_a.y / divider);
	}

	/*
	<< operator to print out.
	Format: "x: 13 y: 12 z: 11" + new line.
	*/
	friend std::ostream& operator << (std::ostream& out, const Vec2& vec)
	{
		out << "x: " << vec.x << " y: " << vec.y << " z: " << "\n";
		return out;
	}

	/*
	>> operator to accept input.
	Format: >> x >> y.
	*/
	friend std::istream& operator >> (std::istream& in, Vec2& vec)
	{
		in >> vec.x >> vec.y;
		return in;
	}
};


#endif // !VECTOR_H
