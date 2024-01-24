#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <vector.h>
#include <color.h>

#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <matrix.h>

class Shader
{
public:
	
	unsigned int ID;
	std::string vertexPath;
	std::string fragmentPath;

	Shader(const char* vertexPath, const char* fragmentPath);
	Shader(Shader& copy);
	~Shader();

	// Operator overload
	Shader& operator=(const Shader& copy);

	void use();

	void setBool(const std::string& name, const bool& value) const;
	void setInt(const std::string& name, const int& value) const;
	void setFloat(const std::string& name, const float& value) const;
	void setVec3(const std::string& name, const float& x, const float& y, const float& z) const;
	void setVec3(const std::string& name, const Vec3& vector) const;
	void setVec3(const std::string& name, const float* color) const;
	void setColor(const std::string& name, const Color& color) const;
};


#endif // !SHADER_H
