#include"Render.h"

void Render::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.bind();
	va.bind();
	ib.bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Render::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
