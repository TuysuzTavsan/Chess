#pragma once
#include <memory>
#include <glad/glad.h>
#include <ecs/System.h>
#include <ecs/ECSManager.h>
#include <shader.h>
#include <text.h>

class RenderSystem : public System
{
public:

	RenderSystem()
		:
		shader(new Shader("ShaderSrc/spriteVertex.glsl", "ShaderSrc/spriteFragment.glsl")),
		indices(new unsigned int[6] {
		0, 1, 2,	// First triangle
		2, 3, 0	    // Second triangle
			})
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);;

		glBindVertexArray(VAO);

		vertices = new float[16] {
			-0.5f, 0.5f, 0.0f, 1.0f, // Top left
			-0.5f, -0.5f, 0.0f, 0.0f, // Bottom left
			0.5f, -0.5f, 1.0f, 0.0f,// Bottom right
			0.5f, 0.5f, 1.0f, 1.0f,// Top right

			};

		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, vertices, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, this->indices.get(), GL_STATIC_DRAW);

		glBindVertexArray(0);

	}

	~RenderSystem()
	{
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteVertexArrays(1, &VAO);
	}

	void Operate(const float& dt) override
	{
		ECSManager* manager = ECSManager::getManager();

		this->shader->use();
		this->shader->setInt("texture0", 0);
		glBindVertexArray(VAO);
		glUniformMatrix4fv(glGetUniformLocation(this->shader->ID, "projection"), 1, GL_FALSE, &APL::Ortho.x.x);

		for (auto& sprite : manager->GetPoolData<Sprite>())
		{
			//glBindBuffer(GL_ARRAY_BUFFER, VBO);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, vertices, GL_STATIC_DRAW);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, sprite.texture.GetTextureData());
			
			
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		glBindVertexArray(0);


		glfwSwapBuffers(APL::window);
	}

private:
	std::shared_ptr<Shader> shader;
	unsigned int Buff;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	float* vertices;
	std::shared_ptr<unsigned int[]> indices;

};