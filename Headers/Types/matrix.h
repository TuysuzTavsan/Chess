#ifndef MATRIX_H
#define MATRIX_H

/*
Vec4 class to work with matrix. 
*/
struct Vec4 {
	float x, y, z, w;
		
	Vec4(const float& x = 0.0f, const float& y = 0.0f, const float& z = 0.0f, const float& w = 0.0f)
	: x(x), y(y), z(z), w(w)
	{

	};

	static Vec4 IdentityVec4()
	{
		Vec4 temp(1.0f, 1.0f, 1.0f, 1.0f);
		return temp;
	}

	float& operator[](int index)
	{	
		if (index == 0)
			return x;
		if (index == 1)
			return y;
		if (index == 2)
			return z;

		return w;
	}

	~Vec4()
	{};

};

/*
Matrix4x4 class. TODO: add more operator overloads. And maybe template?
*/
struct Mat4x4 {
public:

	Vec4 x; // First element of the matrix.
	Vec4 y; // Second element of the matrix.
	Vec4 z; // Third element of the matrix.
	Vec4 w; // Forth element of the matrix.

	//Constructor that takes 4 Vec4. Initial value is 0.0f for every value.
	Mat4x4(const Vec4& x = Vec4(), const Vec4& y = Vec4(), 
		const Vec4& z = Vec4(), const Vec4& w = Vec4())
		: x(),  y(), z(), w()
	{};	

	//Destructor.
	~Mat4x4()
	{};

	//Static method for getting IdentityMatrix4v4
	static Mat4x4 IdentityM4x4()
	{
		Mat4x4 temp;
		
		temp.x.x = 1.0f;
		temp.y.y = 1.0f;
		temp.z.z = 1.0f;
		temp.w.w = 1.0f;

		return temp;
	}

	//Static method for creating Orthographic projection. TODO: Maybe remove far and near planes?
	static Mat4x4 Ortho(const float& left, const float& right, const float& bottom, const float& top,
		const float& near, const float& far)
	{
		Mat4x4 temp;


		temp.x.x = (2 / (right - left));
		temp.x.y =  (0.0f);
		temp.x.z =  (0.0f);
		temp.x.w =  (0.0f);
		   
		temp.y.x =  (0.0f);
		temp.y.y =  (2 / (top - bottom));
		temp.y.z =  (0);
		temp.y.w =  (0);
			   
		temp.z.x =  (0);
		temp.z.y =  (0);
		temp.z.z = (-2 / (far - near));
		temp.z.w = (0);
			   
		temp.w.x = (-(right + left) / (right - left));
		temp.w.y = (-(top + bottom) / (top - bottom));
		temp.w.z = (-(far + near) / (far - near));
		temp.w.w = (1.0f);
		
		return temp;

	}



};



#endif // !MATRIX_H

