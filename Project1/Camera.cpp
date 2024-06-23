#include "Camera.h"

Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix() const
{

	return glm::lookAt(position, position + front, up);
}
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
	:front(glm::vec3(0.0f, 0.0f, -1.0f)),
	movementSpeed(SPEED),
	mouseSensitivity(SENSITIVITY),
	zoom(ZOOM),
	lastX(0),
	lastY(0),
	mode(CameraMode::Walk)

{
	this->position = position;
	worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	UpdateCameraVectors();
}
void Camera::Move(Camera_Movement direction, float deltaTime) {
	float velocity = movementSpeed * deltaTime;
	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;
}
void Camera::ProcessMouseMovement(float posX, float posY, GLboolean constrainPitch)
{
	if (lastX == 0 && lastY == 0) {
		lastX = posX;
		lastY = posY;
	}
	float xoffset = (posX - lastX) * mouseSensitivity;
	float yoffset = (lastY - posY) * mouseSensitivity;

	lastX = posX;
	lastY = posY;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	UpdateCameraVectors();
}
void Camera::ProcessMouseScroll(float yoffset)
{
	zoom -= (float)yoffset;
	if (zoom < 1.0f)
		zoom = 1.0f;
	if (zoom > 45.0f)
		zoom = 45.0f;
}
void Camera::ProcessKeyPressed(unsigned char key) {
	if (key == 'W')
		Move(FORWARD, movementSpeed);

	if (key == 'S')
		Move(BACKWARD, movementSpeed);

	if (key == 'A')
		Move(LEFT, movementSpeed);

	if (key == 'D')
		Move(RIGHT, movementSpeed);

	if (key == 'V')
		ToggleMode();

	UpdateCameraVectors();
}


glm::mat4 Camera::GetProjectionMatrix(float aspectRatio) const {
	return glm::perspective(glm::radians(zoom), aspectRatio, 0.1f, 100.0f);
}
void  Camera::SetUniforms(GLProgram& program, float aspectRatio) {
	program.SetUniformMat4fv("projection", GetProjectionMatrix(aspectRatio));
}
void Camera::UpdateCameraVectors() {
	if (mode == CameraMode::Walk) {
		// Set the position to a fixed height of 1.8 on the y-axis
		position.y = 1.8f;
	}
	// calculate the new Front vector based on the yaw and pitch
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->front = glm::normalize(front);


	// also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(this->front, worldUp));
	up = glm::normalize(glm::cross(right, this->front));
}

void Camera::ToggleMode()
{
	if (mode == CameraMode::Walk) {
		mode = CameraMode::Drone;
		lastPos = position;
		lastYaw = yaw;
		lastPitch = pitch;
		position = POSITION;
		yaw = YAW;
		pitch = PITCH;
	}
	else if (mode == CameraMode::Drone) {
		mode = CameraMode::Walk;
		yaw = lastYaw;
		pitch = lastPitch;
		position = lastPos;
	}
}
