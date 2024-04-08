#include "Camera.h"

Camera::~Camera()
{
	delete this;
}

glm::mat4 Camera::GetViewMatrix() const
{

	return glm::lookAt(position, position + front, up);
}
