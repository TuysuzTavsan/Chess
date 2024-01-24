#include <drawable2D.h>
#include <apl.h>

Drawable2D::Drawable2D()
	: shader(new Shader("ShaderSrc/vertex.glsl", "ShaderSrc/fragment.glsl")),
	color(), position(Vec2(static_cast<float>(APL::WINDOW_WIDTH / 2), static_cast<float>(APL::WINDOW_HEIGHT / 2))),
	origin(),vertices(nullptr), indices(nullptr),
	VBO(0), VAO(0), EBO(0)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

Drawable2D::Drawable2D(Drawable2D& copy)
	: shader(copy.shader),
	color(copy.color), position(copy.position), origin(copy.origin),
	vertices(nullptr), indices(nullptr),
	VBO(0), VAO(0), EBO(0)
{


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

Drawable2D::~Drawable2D()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

Drawable2D& Drawable2D::operator=(const Drawable2D& other)
{
		if (this != &other)
	{
		this->color = other.color;
		this->origin = other.origin;
		this->position = other.position;
		this->shader = other.shader;

		ApplyChanges();
	}
	return *this;
}

void Drawable2D::ApplyChanges()
{

}

void Drawable2D::SetColor(const Color& color)
{
	this->color = color;
}

void Drawable2D::SetOrigin(const Vec2& origin)
{
	this->origin = origin;
}

void Drawable2D::SetPosition(const Vec2& position)
{
	this->position = position;
	ApplyChanges();
}

void Drawable2D::Move(const Vec2& movement)
{
	this->position += movement;
	ApplyChanges();
}
