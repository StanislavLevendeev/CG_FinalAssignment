#include "GLProgram.h"
#include "Renderer.h"

void GLProgram::LinkProgram()
{
	GLCall(glLinkProgram(rendererID));
	GLCall(glValidateProgram(rendererID));

	unsigned int count = shaders.size();

	for (unsigned int i = 0; i < count; i++)
	{
		GLCall(glDeleteShader(shaders[i]->GetID()));
	}

}

GLProgram::GLProgram(Shader shaders[], unsigned int count)
{
	GLCall(rendererID = glCreateProgram());
	Attach(shaders, count);
	Bind();

}

GLProgram::GLProgram()
{
	GLCall(rendererID = glCreateProgram());
}

GLProgram::~GLProgram()
{
	delete uniformLocations;
	for (unsigned int i = 0; i < shaders.size(); i++)
	{
		GLCall(glDetachShader(rendererID, shaders[i]->GetID()));
		delete shaders[i];
	}
	GLCall(glDeleteProgram(rendererID));
}

void GLProgram::Attach(Shader shaders[], unsigned int count)
{
	for (unsigned int i = 0; i < count; i++)
	{
		GLCall(glAttachShader(rendererID, shaders[i].GetID()));
		this->shaders.push_back(&shaders[i]);
	}
	LinkProgram();
}

void GLProgram::Attach(Shader& shader)
{
	GLCall(glAttachShader(rendererID, shader.GetID()));
	shaders.push_back(&shader);
	LinkProgram();
}


void GLProgram::Bind() const
{
	GLCall(glUseProgram(rendererID));
}

void GLProgram::Unbind() const
{
	GLCall(glUseProgram(0));
}

GLuint GLProgram::SetUniform1i(const GLchar* name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
	return uniformMap[name];
}

GLuint GLProgram::SetUniformMat4fv(const char* name, const glm::mat4& value)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)));
	return uniformMap[name];
}

GLuint GLProgram::SetUniform3fv(const GLchar* name, const glm::vec3& vector)
{
	GLCall(glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(vector)));
	return uniformMap[name];
}

GLuint GLProgram::SetUniform1f(const GLchar* name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
	return uniformMap[name];
}

GLuint GLProgram::GetUniformLocation(const std::string& name)
{
	if (uniformMap.find(name) == uniformMap.end())
		GLCall(uniformMap[name] = glGetUniformLocation(rendererID, name.c_str()));
	return uniformMap[name];
}

