#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GLProgram.h"
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 1.0f;
const float SENSITIVITY = 0.5f;
const float ZOOM = 45.0f;


class Camera
{
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	~Camera();
	glm::mat4 GetViewMatrix()const;
	void Move(Camera_Movement, float);
	void ProcessMouseMovement(float, float, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float);
	void ProcessKeyPressed(unsigned char);
	glm::mat4 GetProjectionMatrix(float aspectRatio) const;
	void SetUniforms(GLProgram&, float);
private:
	void UpdateCameraVectors();

	glm::mat4 projection;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	float yaw;
	float pitch;
	float movementSpeed;
	float mouseSensitivity;
	float zoom;
	float lastX, lastY;
};

