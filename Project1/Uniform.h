#pragma once
#include <string>
#include <iostream>
#include <GL/glew.h>
enum UniformType
{
	Matrix4fv,
	Vector3fv,
	Float

};
class Uniform
{
private:
	GLfloat* data;
	UniformType type;
	std::string name;
public:
	Uniform(GLfloat* data, UniformType type, const std::string& name);
	~Uniform();

	GLfloat* GetData() const
	{
		if (type < 0)
		{
			std::cout << "Data not found." << std::endl;
			return nullptr;
		}

		return data;
	}

	inline const std::string GetName() const
	{
		return name;
	}

	inline const UniformType GetType() const
	{
		return type;
	}
};

