#pragma once

#include <glm/gtc/type_ptr.hpp>
#include "GLProgram.h"
class Light
{
public:
	Light(const glm::vec3 position);
	~Light();
	void SetUniforms(GLProgram& program) const;
private:
	glm::vec3 position;
};

