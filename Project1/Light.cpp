#include "Light.h"

Light::Light(const glm::vec3 position)
{
	this->position = position;
}

Light::~Light()
{
}

void Light::SetUniforms(GLProgram& program) const
{
	program.SetUniform3fv("light.position", this->position);
}
