#pragma once
#include <glm/gtc/type_ptr.hpp>
#include "GLProgram.h"

class Material
{
public:
	Material();
	~Material();
	//	Ambient lighting: even when it is dark there is usually still some light somewhere in the world (the moon, a distant light)
	//  so objects are almost never completely dark.
	glm::vec3 ambient;
	//	Diffuse lighting: the most basic type of lighting. This is the minimum lighting effect that a material must have to be visible.
	glm::vec3 diffuse;
	//	Specular lighting: the bright spot that appears on a surface when a light is reflected off of it.
	glm::vec3 specular;
	//	Shininess: the size of the specular highlight. The larger the value, the smaller and more concentrated the highlight becomes.
	float shininess;
	void SetUniforms(GLProgram& program) const;
	void UnsetUniforms(GLProgram& program) const;
};
