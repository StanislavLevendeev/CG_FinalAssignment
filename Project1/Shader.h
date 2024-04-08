#pragma once
#include <string>
#include <GL/glew.h>
#include "glsl.h"

class Shader
{
public:
	Shader(const GLuint type, const std::string& filepath);
	~Shader();
	inline unsigned int GetID() const
	{
		return rendererID;
	}
	inline unsigned int GetType() const
	{
		return shaderType;
	}
private:
	void Recompile(const std::string& filepath);
	GLuint shaderType;
	std::string filepath;
	unsigned int rendererID;
	void Compile();
	bool isCompiled();

};

