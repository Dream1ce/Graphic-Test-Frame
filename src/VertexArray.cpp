#include"VertexArray.h"
#include"Render.h"
#include"VertexBufferLayout.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
	GLCall(glBindVertexArray(m_RendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1,&m_RendererID))
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	bind();
	vb.Bind();
	const auto& Elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < Elements.size(); i++)
	{
		const auto& element = Elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized,layout.GetStride() , (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}
void VertexArray::bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}
void VertexArray::unbind() const
{
	GLCall(glBindVertexArray(0));
}