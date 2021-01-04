#include "TestTexture2d.h"

#include"Render.h"
#include"imgui/imgui.h"

#include"VertexBuffer.h"
#include"VertexBufferLayout.h"
#include"Texture.h"
#include"VertexArray.h"

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
namespace test
{
	TestTexture2d::TestTexture2d()
		:m_translationA(200,200,0),m_translationB(400,200,0),
		m_proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		m_view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
	{
		float positions[] = {
			-50.0f, -50.0f, 0.0f, 0.0f,
			 50.0f, -50.0f, 1.0f, 0.0f,
			 50.0f,  50.0f, 1.0f, 1.0f,
			-50.0f,  50.0f, 0.0f, 1.0f
		};
		unsigned int indices[] = {
			0,1,2,
			2,3,0
		};
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		m_indexBuffer = std::make_unique<IndexBuffer>(indices, 6);
		m_shader = std::make_unique<Shader>("res/shader/basic.shader");
		m_shader->bind();
		m_shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
		m_Texture = std::make_unique<Texture>("res/Texture/01.png");
		m_Texture->bind();
		m_shader->SetUniform1i("u_Texture", 0);
	}
	TestTexture2d::~TestTexture2d()
	{
	}
	void TestTexture2d::OnUpdate(float deltaTime)
	{
	}
	void TestTexture2d::OnRender()
	{
		Render renderer;
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
			glm::mat4 mvp = m_proj * m_view * model;
			m_shader->bind();
			m_shader->SetUniformMat4("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_indexBuffer, *m_shader);
		}
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationB);
			glm::mat4 mvp = m_proj * m_view * model;
			m_shader->bind();
			m_shader->SetUniformMat4("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_indexBuffer, *m_shader);
		}
	}
	void TestTexture2d::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation A", &m_translationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat3("Translation B", &m_translationB.x, 0.0f, 960.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}