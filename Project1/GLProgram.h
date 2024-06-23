#pragma once
#include <vector>
#include "Shader.h"
#include <glm/detail/type_vec.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
class GLProgram
{
private:
	unsigned int rendererID;
	std::vector<Shader*> shaders;
	std::map<std::string, GLuint> uniformMap;
	int* uniformLocations = nullptr;
	void LinkProgram();
public:
	GLProgram(Shader shaders[], unsigned int count);
	GLProgram();
	~GLProgram();
	void Attach(Shader shaders[], unsigned int count);
	void Attach(Shader& shader);
	void Bind() const;
	void Unbind() const;
	GLuint SetUniform1i(const GLchar* name, int value);
	GLuint SetUniformMat4fv(const char* name, const glm::mat4& value);
	GLuint SetUniform3fv(const GLchar* name, const glm::vec3& vector);
	GLuint SetUniform1f(const GLchar* name, float value);
	GLuint GetUniformLocation(const std::string& name);
	inline const std::vector<Shader*> AttachedShaders() const
	{
		return shaders;
	}

	inline const unsigned int GetID() const
	{
		return rendererID;
	}
};

