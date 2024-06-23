#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Transformable {
public:
	virtual void Translate(glm::vec3 translation) {
		position += translation;
	};
	virtual void Rotate(glm::vec3 axis) {
		rotation += axis;
	};
	virtual void Rotate(float angle, glm::vec3 axis)
	{
		axis = glm::normalize(axis);
		if (axis.x != 0.0f)
			rotation.x += angle * axis.x;
		if (axis.y != 0.0f)
			rotation.y += angle * axis.y;
		if (axis.z != 0.0f)
			rotation.z += angle * axis.z;
	}
	virtual void Scale(glm::vec3 scale) { this->scale = scale; };
	virtual glm::mat4 GetModelMatrix() const {
		glm::mat4 newModel = glm::mat4(1.0f); ;
		newModel = glm::translate(newModel, this->position);

		// Apply rotations in the correct order
		newModel = glm::rotate(newModel, rotation.z, glm::vec3(0, 0, 1));
		newModel = glm::rotate(newModel, rotation.y, glm::vec3(0, 1, 0));
		newModel = glm::rotate(newModel, rotation.x, glm::vec3(1, 0, 0));

		// Apply scaling last
		newModel = glm::scale(newModel, scale);

		return newModel;
	};
	glm::vec3  rotation = glm::vec3(0, 0, 0);
	glm::vec3  position = glm::vec3(0, 0, 0);
	glm::vec3  scale = glm::vec3(1, 1, 1);
};