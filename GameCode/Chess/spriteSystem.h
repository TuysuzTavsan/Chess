#pragma once
#include <memory>
#include <glad/glad.h>
#include <ecs/System.h>
#include <ecs/ECSM.h>
#include <shader.h>
#include <text.h>
#include <rectangle.h>

class SpriteSystem : public System
{
public:

	SpriteSystem()
		:
		shader(new Shader("ShaderSrc/spriteVertex.glsl", "ShaderSrc/spriteFragment.glsl")),
		vertices(new float[16] {
			-0.5f, 0.5f, 0.0f, 1.0f, // Top left
			-0.5f, -0.5f, 0.0f, 0.0f, // Bottom left
			0.5f, -0.5f, 1.0f, 0.0f,// Bottom right
			0.5f, 0.5f, 1.0f, 1.0f// Top right
			}),
		indices(new unsigned int[6] {
			0, 1, 2,	// First triangle
			2, 3, 0	    // Second triangle
			})
	{
		shader->use();
		shader->setInt("texture0", 0);
			glUniformMatrix4fv(glGetUniformLocation(
		this->shader->ID, "projection"), 1, GL_FALSE, &APL::Ortho.x.x);
		
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, vertices.get(), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indices.get(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);


		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}

	~SpriteSystem()
	{
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteVertexArrays(1, &VAO);
	}

	void Operate(const float& dt) override
	{
		ECSManager* manager = ECSManager::getManager();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		this->shader->use();
		glBindVertexArray(VAO);
		
		for (auto& sprite : manager->GetPoolData<Sprite>())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, sprite.GetTexture());
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 16, sprite.vertices.get());
			
			
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		glDisable(GL_BLEND);
		glBindVertexArray(0);
	}

private:
	std::shared_ptr<Shader> shader;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	std::shared_ptr <float[]> vertices;
	std::shared_ptr<unsigned int[]> indices;

};