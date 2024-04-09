#include "Shader.h"
#include "Renderer.h"
#include <iostream>



Shader::Shader(const GLuint type, const std::string& filepath) :shaderType(type), filepath(filepath)
{
	Compile();
}

Shader::~Shader()
{
	GLCall(glDeleteShader(rendererID));
}
void Shader::Recompile(const std::string& filepath)
{
	this->filepath = filepath;
	Compile();
}

void Shader::Compile()
{
	switch (shaderType)
	{
	case GL_VERTEX_SHADER:
	{
		GLCall(char* vertexshader = glsl::readFile(filepath.c_str()));
		GLCall(rendererID = glsl::makeVertexShader(vertexshader));
	}
	break;
	case GL_FRAGMENT_SHADER:
	{
		GLCall(char* fragshader = glsl::readFile(filepath.c_str()));
		GLCall(rendererID = glsl::makeFragmentShader(fragshader));
	}	
	break;
	default:
		std::cout << "Invalid shader type" << std::endl;
		break;
	}
}

bool Shader::isCompiled()
{
	int result;
	GLCall(glGetShaderiv(rendererID, GL_COMPILE_STATUS, &result));

	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(rendererID, GL_INFO_LOG_LENGTH, &length));

		char* message = (char*)(alloca(length * sizeof(char)));
		GLCall(glGetShaderInfoLog(rendererID, length, &length, message));

		std::cout << "Failed to compile " << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
		std::cout << message << std::endl;

		GLCall(glDeleteShader(rendererID));
		return false;
	}

	return true;
}
