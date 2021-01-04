#pragma once

#include"test.h"
#include"imgui/imgui.h"
#include"glm/glm.hpp"
#include"VertexArray.h"
#include"Shader.h"
#include"Texture.h"
#include"IndexBuffer.h"
#include"VertexBuffer.h"

#include<memory>

namespace test
{
	class TestTexture2d:public Test
	{
	public:
		TestTexture2d();
		~TestTexture2d();
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		glm::vec3 m_translationA;
		glm::vec3 m_translationB;
		glm::mat4 m_proj, m_view;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr <IndexBuffer> m_indexBuffer;
		std::unique_ptr <Shader> m_shader;
		std::unique_ptr<Texture> m_Texture;
	};
}