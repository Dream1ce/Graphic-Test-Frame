#include "Shader.h"
#include"Render.h"


Shader::Shader(const std::string& filepath)
	:m_FilePath(filepath),m_RendererID(0)
{
	ShaderSource ss = PraseShader(filepath);
	m_RendererID = CreateShader(ss.VertexShader, ss.FragmentShader);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void Shader::bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	unsigned int location = GetUniformLocation(name);
	GLCall(glUniform1i(location, value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	unsigned int location = GetUniformLocation(name);
	GLCall(glUniform1f(location, value));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	unsigned int location = GetUniformLocation(name);
	GLCall(glUniform4f(location, v0, v1, v2, v3));
}

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

unsigned int Shader::GetUniformLocation(const std::string& name)
{
	if (m_LocationCache.find(name) != m_LocationCache.end())
		return m_LocationCache[name];
	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform " << name << " dosen't exits!!"<<std::endl;
	else
		m_LocationCache[name] = location;
	return location;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//TODO: Error hand
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = new char(length);
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& VertexShader, const std::string& FragmentShader)
{
	unsigned int pro = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, VertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);

	glAttachShader(pro, vs);
	glAttachShader(pro, fs);
	glLinkProgram(pro);
	int success;
	glGetProgramiv(pro, GL_LINK_STATUS, &success);
	if (!success)
	{
		int len;
		glGetProgramiv(pro, GL_INFO_LOG_LENGTH, &len);
		char* res = new char(len);
		glGetProgramInfoLog(pro, len, &len, res);
		std::cout << "there are some erro in linkingpro!!" << std::endl;
		std::cout << res << std::endl;
	}
	glValidateProgram(pro);//?
	glDeleteShader(vs);
	glDeleteShader(fs);
	return pro;
}

ShaderSource Shader::PraseShader(const std::string& FilePath)
{
	std::ifstream stream(FilePath);
	std::string line;
	std::stringstream ss[2];
	enum Shadertype
	{
		NONE = -1, VertexShader = 0, FragmentShader = 1
	};
	Shadertype type = NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = VertexShader;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = FragmentShader;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str(),ss[1].str() };
}
