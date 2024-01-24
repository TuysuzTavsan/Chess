#include "shader.h"


Shader::Shader(const char* vertexPath, const char* fragmentPath)
	: ID(0), vertexPath(vertexPath), fragmentPath(fragmentPath)
{
	std::string vertexSrc;
	std::string fragmentSrc;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexSrc = vShaderStream.str();
		fragmentSrc = fShaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "Error! Shader source reading failed." << std::endl;
		std::cout << e.what() << "\n";
	}
	const char* vShaderCode = vertexSrc.c_str();
	const char* fShaderCode = fragmentSrc.c_str();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "Error! Vertex shader compilation failed.\n" << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "Error! Fragment shader compilation failed.\n" << infoLog << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "Error! Shader program linking failed!\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::Shader(Shader& copy)
	: Shader(copy.vertexPath.c_str(), copy.fragmentPath.c_str())
{
	
}

Shader::~Shader()
{
	glDeleteProgram(this->ID);
}

Shader& Shader::operator=(const Shader& copy)
{
	this->vertexPath = copy.vertexPath;
	this->fragmentPath = copy.fragmentPath;
	std::string vertexSrc;
	std::string fragmentSrc;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexSrc = vShaderStream.str();
		fragmentSrc = fShaderStream.str();
	}
	catch (std::ifstream::failure& e) // TODO proper error handling
	{
		std::cout << "Error! Shader source reading failed." << std::endl;
		std::cout << e.what() << "\n";
	}
	const char* vShaderCode = vertexSrc.c_str();
	const char* fShaderCode = fragmentSrc.c_str();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "Error! Vertex shader compilation failed.\n" << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "Error! Fragment shader compilation failed.\n" << infoLog << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "Error! Shader program linking failed!\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return *this;
}


void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, const bool& value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), int(value));
}

void Shader::setInt(const std::string& name, const int& value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, const float& value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, const float& x, const float& y, const float& z) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec3(const std::string& name, const Vec3& vector) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), vector.x, vector.y, vector.z);
}

void Shader::setVec3(const std::string& name, const float* color) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), color[0], color[1], color[2]);
}

void Shader::setColor(const std::string& name, const Color& color) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), color.r, color.g, color.b, color.a);
}

