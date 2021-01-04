#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<sstream>
#include<string>
#include<fstream>

#include"Shader.h"
#include"Render.h"
#include"IndexBuffer.h"
#include"VertexBuffer.h"
#include"VertexArray.h"
#include"VertexBufferLayout.h"
#include"Texture.h"

#include"vendor/glm/glm.hpp"
#include"vendor/glm/gtc/matrix_transform.hpp"

#include"vendor/imgui/imgui.h"
#include"vendor/imgui/imgui_impl_opengl3.h"
#include"vendor/imgui/imgui_impl_glfw.h"

#include"test/TestClearColor.h"
#include"test/TestTexture2d.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwSwapInterval(1);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK)
		std::cout << "error" << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;

	{
	
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		Shader shader("res/shader/basic.shader");
		shader.bind();
		//shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
		float r = 0.0f;
		float increatement = 0.05f;

		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330 core");//这里要写OpenGL的版本号，看看空着有没有问题
		ImGui::StyleColorsDark();
	
		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;
		
		testMenu->RegisterTest<test::TestClearColor>("clear color");
		testMenu->RegisterTest<test::TestTexture2d>("Texture 2D");

		test::TestClearColor test;

		Render render;
		while (!glfwWindowShouldClose(window))
		{
			render.Clear();
			
			test.OnUpdate(0.0f);
			test.OnRender();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			if (currentTest)
			{
				currentTest->OnUpdate(0.0f);
				currentTest->OnRender();
				ImGui::Begin("Test");
				if (currentTest != testMenu && ImGui::Button("<-"))//从现行测试返回菜单
				{
					delete currentTest;
					currentTest = testMenu;
				}
				currentTest->OnImGuiRender();
				ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		delete currentTest;
		if (currentTest != testMenu)
			delete testMenu;
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		glfwTerminate();
		return 0;
	}
}
