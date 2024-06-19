#pragma once
#include <glm/gtc/type_ptr.hpp>
class Transformable {
public:
	virtual void Translate(glm::vec3 translation) = 0;
	virtual void Rotate(glm::vec3 axis) = 0;
	virtual void Scale(glm::vec3 scale) = 0;
};