#include <rectangle.h>
#include <apl.h>

Rectangle::Rectangle()
	: Drawable2D(), topLeft(), bottomRight(), 
	size(Vec2(static_cast<float>(APL::WINDOW_WIDTH) / 2, static_cast<float>(APL::WINDOW_HEIGHT)) / 2), 
	texture0{}
{

	vertices = std::move(std::unique_ptr<float[]>(new float[16] {
		position.x - (size.x / 2), position.y + (size.y / 2), 0.0f, 1.0f, // Top left
			position.x - (size.x / 2), position.y - (size.y / 2), 0.0f, 0.0f, // Bottom left
			position.x + (size.x / 2), position.y - (size.y / 2), 1.0f, 0.0f,// Bottom right
			position.x + (size.x / 2), position.y + (size.y / 2), 1.0f, 1.0f,// Top right
		}));

	indices = std::move(std::unique_ptr<unsigned int[]>(new unsigned int[6] {
		0, 1, 2,	// First triangle
		2, 3, 0	    // Second triangle
	}));

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, this->vertices.get(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2*sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, this->indices.get(), GL_STATIC_DRAW);

}

Rectangle::Rectangle(const Vec2& size)
	: Drawable2D(), topLeft(), bottomRight(), size(size)
{

	vertices = std::move(std::unique_ptr<float[]>(new float[16]{
			position.x - (size.x / 2), position.y + (size.y / 2), 0.0f, 1.0f, // Top left
			position.x - (size.x / 2), position.y - (size.y / 2), 0.0f, 0.0f, // Bottom left
			position.x + (size.x / 2), position.y - (size.y / 2), 1.0f, 0.0f,// Bottom right
			position.x + (size.x / 2), position.y + (size.y / 2), 1.0f, 1.0f,// Top right
	}));

	indices = std::move(std::unique_ptr<unsigned int[]>(new unsigned int[6] {
		0, 1, 2,	// First triangle
		2, 3, 0	    // Second triangle
	}));

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, this->vertices.get(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2*sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, this->indices.get(), GL_STATIC_DRAW);

}

Rectangle::Rectangle(Rectangle& copy)
	: Drawable2D(copy), topLeft(copy.topLeft), bottomRight(copy.bottomRight), size(copy.size)
{
	vertices = std::move(std::unique_ptr<float[]>(new float[16]{
			position.x - (size.x / 2), position.y + (size.y / 2), 0.0f, 1.0f, // Top left
			position.x - (size.x / 2), position.y - (size.y / 2), 0.0f, 0.0f, // Bottom left
			position.x + (size.x / 2), position.y - (size.y / 2), 1.0f, 0.0f,// Bottom right
			position.x + (size.x / 2), position.y + (size.y / 2), 1.0f, 1.0f,// Top right
	}));

	indices = std::move(std::unique_ptr<unsigned int[]>(new unsigned int[6] {
		0, 1, 2,	// First triangle
		2, 3, 0	    // Second triangle
	}));

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, this->vertices.get(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2*sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, this->indices.get(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Rectangle& Rectangle::operator=(const Rectangle& other)
{
	if (this != &other)
	{
		Drawable2D::operator=(other);
		this->topLeft = other.topLeft;
		this->bottomRight = other.bottomRight;
		this->size = other.size;

	}

	return *this;
}

bool Rectangle::LoadTexture(const std::string& path)
{
	return this->texture0.LoadTexture(path);
}


Rectangle::~Rectangle()
{
}

void Rectangle::SetCorner(const Vec2& top_left, const Vec2& bottom_right)
{
	this->topLeft = top_left;
	this->bottomRight = bottom_right;
	this->position.x = (this->bottomRight.x + this->topLeft.x) / 2;
	this->position.y = (this->topLeft.y + this->bottomRight.y) / 2;
	this->size.x = top_left.x - bottom_right.x;
	this->size.y = top_left.y - bottom_right.y;

}

void Rectangle::ApplyChanges()
{
	if (vertices.get())
	{
		
		vertices.get()[0] = position.x - (size.x / 2);
		vertices.get()[1] = position.y + (size.y / 2);
		vertices.get()[4] = position.x - (size.x / 2);
		vertices.get()[5] = position.y - (size.y / 2);
		vertices.get()[8] = position.x + (size.x / 2);
		vertices.get()[9] = position.y - (size.y / 2);
		vertices.get()[12] = position.x + (size.x / 2);
		vertices.get()[13] = position.y + (size.y / 2);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 16, this->vertices.get()); // be sure to use glBufferSubData and not glBufferData
	}
}


void Rectangle::Render()
{
	this->shader->use();
	glEnable(GL_BLEND);
	this->shader->setBool("isTexture", this->texture0.IsLoaded());
	if(this->texture0.IsLoaded())
	{
		glBindTexture(GL_TEXTURE_2D, this->texture0.GetTextureData());
		glActiveTexture(GL_TEXTURE0);
	}
	this->shader->setColor("aColor", color);
	glUniformMatrix4fv(glGetUniformLocation(
		this->shader->ID, "projection"), 1, GL_FALSE, &APL::Ortho.x.x);
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glDisable(GL_BLEND);
}
