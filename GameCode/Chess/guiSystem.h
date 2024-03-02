#pragma once

#include <ecs/System.h>
#include <memory>
#include <shader.h>

class GUISystem : System
{
public:

	GUISystem();
	~GUISystem();

	void Operate(const float& dt) override;

private:
	std::shared_ptr<Shader> m_GUIShader;
	std::shared_ptr<unsigned int> m_indices;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
};