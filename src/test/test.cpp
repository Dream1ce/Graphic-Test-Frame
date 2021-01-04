
#include"test.h"
#include"imgui/imgui.h"

namespace test
{
	TestMenu::TestMenu(Test*& currentTestPointer)
		: m_Currenttest(currentTestPointer)
	{
	}
	void TestMenu::OnImGuiRender()
	{
		for (auto& test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str()))
			{
				m_Currenttest = test.second();
			}
		}
	}
}