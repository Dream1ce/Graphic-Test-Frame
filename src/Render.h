#pragma once
#include<GL/glew.h>
#include<iostream>

#include"VertexArray.h"
#include"IndexBuffer.h"
#include"Shader.h"

#define Assert(x) if(!x) __debugbreak();
#define GLCall(x) GLClearError();\
        x;\
        Assert(GLLogCall(#x,__FILE__,__LINE__));


static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR)
	{

	}
}
static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[openGL error](" << error << ")" << function << " " << file << " " << line << std::endl;
		return false;
	}
	return true;
}
class Render
{
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void Clear();
};