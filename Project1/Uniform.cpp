#include "Uniform.h"

Uniform::Uniform(GLfloat* data, UniformType type, const std::string& name) :
	data(data), type(type), name(name)
{
}
Uniform::~Uniform()
{
	delete[] data;
}