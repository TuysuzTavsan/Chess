#include <Chess/guiSystem.h>
#include <glad/glad.h>
#include <ecs/ECSM.h>
#include <components/button.h>
#include <helper.h>

GUISystem::GUISystem()
	:
	m_GUIShader{new Shader{"ShaderSrc/GUIVertex.glsl", "ShaderSrc/GUIFragment.glsl"}},
	VAO{ 0 },
	VBO{ 0 },
	EBO{ 0 },
	m_indices{ new unsigned int[6] {
	0, 1, 2,	// First triangle
		2, 3, 0	    // Second triangle
		} }
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);;
	
	glBindVertexArray(VAO);
	
	
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, nullptr, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, m_indices.get(), GL_STATIC_DRAW);
	
	glBindVertexArray(0);

	this->m_GUIShader->use();
	glUniformMatrix4fv(glGetUniformLocation(this->m_GUIShader->ID, "projection"), 1, GL_FALSE, &APL::Ortho.x.x);

	this->m_GUIShader->setInt("bgTexture", 0);
	this->m_GUIShader->setInt("hoverTexture", 1);
	this->m_GUIShader->setInt("activeTexture", 2);

}

GUISystem::~GUISystem()
{

}

void GUISystem::Operate(const float& dt)
{
	this->m_GUIShader->use();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindVertexArray(VAO);

	for (auto& button : ECSM::GetPoolData<Button>())
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, button.vertices.get(), GL_STATIC_DRAW);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, button.bgTexture.GetTextureData());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, button.hotTexture.GetTextureData());
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, button.activeTexture.GetTextureData());

		if (helper::IsInside(button.position, button.size, Vec2(static_cast<float>(APL::mousePosx), static_cast<float>(APL::WINDOW_HEIGHT - APL::mousePosy))))
		{
			button.hot = true;

			if (button.isAlreadyFocused == false)
			{
				button.hot = true;
				button.isAlreadyFocused = true;
				button.OnFocusEntered();

			}

			button.OnHot();

			this->m_GUIShader->setInt("state", 1);

			if (button.pressed)
			{

				this->m_GUIShader->setInt("state", 2);
			}

		}
		else
		{
			this->m_GUIShader->setInt("state", 0);

			button.isAlreadyFocused = false;
			button.hot = false;
		}



		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}


	for (auto& button : ECSM::GetPoolData<Button>())
	{
		button.text.Render();
	}



	glDisable(GL_BLEND);
	glBindVertexArray(0);
}


