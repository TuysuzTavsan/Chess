#pragma once
#include <memory>
#include <glad/glad.h>
#include <ecs/System.h>
#include <ecs/ECSM.h>
#include <shader.h>
#include <apl.h>
#include <text.h>
#include <components/sprite.h>
#include <components/button.h>
#include <helper.h>

class RenderSystem : public System
{
public:

	RenderSystem()
		:
		spriteShader(new Shader("ShaderSrc/spriteVertex.glsl", "ShaderSrc/spriteFragment.glsl"))
	{

		indices = (new unsigned int[6] {
			0, 1, 2,	// First triangle
				2, 3, 0	    // Second triangle
			});

		vertices = new float[16] {
			-0.5f, 0.5f, 0.0f, 1.0f, // Top left
			-0.5f, -0.5f, 0.0f, 0.0f, // Bottom left
			0.5f, -0.5f, 1.0f, 0.0f,// Bottom right
			0.5f, 0.5f, 1.0f, 1.0f,// Top right
			};

		this->spriteShader->use();
		this->spriteShader->setInt("texture0", 0);

		glUniformMatrix4fv(glGetUniformLocation(this->spriteShader->ID, "projection"), 1, GL_FALSE, &APL::Ortho.x.x);

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);;

		glBindVertexArray(VAO);


		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);

		
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indices, GL_STATIC_DRAW);

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
		RenderSprites();
	}


	void RenderSprites()
	{
		this->spriteShader->use();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindVertexArray(VAO);


		for (auto& sprite : ECSM::GetPoolData<Sprite>())
		{
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, sprite.vertices.get(), GL_STATIC_DRAW);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, sprite.texture.GetTextureData());
			



			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		glDisable(GL_BLEND);
		glBindVertexArray(0);
	}


private:
	std::shared_ptr<Shader> spriteShader;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	float* vertices;
	unsigned int* indices;

};