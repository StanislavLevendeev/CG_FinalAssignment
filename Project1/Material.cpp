#include "Material.h"

Material::Material()
{
	//Fill default values so that it doesn't effect the object anyhow
	ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	specular = glm::vec3(1.0f, 1.0f, 1.0f);
	shininess = 32.0f;
}

Material::~Material()
{
	delete this;
}

void Material::SetUniforms(GLProgram& program) const
{
	program.SetUniform3fv("material.ambient", ambient);
	program.SetUniform3fv("material.diffuse", diffuse);
	program.SetUniform3fv("material.specular", specular);
	program.SetUniform1f("material.shininess", shininess);
}

void Material::UnsetUniforms(GLProgram& program) const
{
	program.SetUniform3fv("material.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	program.SetUniform3fv("material.diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
	program.SetUniform3fv("material.specular", glm::vec3(0.0f, 0.0f, 0.0f));
	program.SetUniform1f("material.shininess", 0.0f);
}
