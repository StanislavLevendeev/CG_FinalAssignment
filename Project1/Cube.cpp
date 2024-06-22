#include "Cube.h"

Cube::Cube()
{
	verticesShape = {
		glm::vec3(-1.0f, -1.0f, 1.0f), // 0: Front bottom left
		glm::vec3(1.0f, -1.0f, 1.0f), // 1: Front bottom right
		glm::vec3(1.0f, 1.0f, 1.0f), // 2: Front top right
		glm::vec3(-1.0f, 1.0f, 1.0f), // 3: Front top left
		glm::vec3(-1.0f, -1.0f, -1.0f), // 4: Back bottom left
		glm::vec3(1.0f, -1.0f, -1.0f), // 5: Back bottom right
		glm::vec3(1.0f, 1.0f, -1.0f), // 6: Back top right
		glm::vec3(-1.0f, 1.0f, -1.0f) // 7: Back top left
	};
	CreateTriangles();
	CreateUVs();
	normalsShape = {
		glm::vec3(0.0f, 0.0f, 1.0f), // 0: Front
		glm::vec3(0.0f, 0.0f, -1.0f), // 1: Back
		glm::vec3(1.0f, 0.0f, 0.0f), // 2: Right
		glm::vec3(-1.0f, 0.0f, 0.0f), // 3: Left
		glm::vec3(0.0f, 1.0f, 0.0f), // 4: Top
		glm::vec3(0.0f, -1.0f, 0.0f) // 5: Bottom
	};
}

Cube::Cube(const GLuint programId) : Cube()
{
	this->SetUp(programId);
}

Cube::Cube(float height, float width, float depth)
{
	float halfHeight = height / 2.0f;
	float halfWidth = width / 2.0f;
	float halfDepth = depth / 2.0f;

	verticesShape = {
		glm::vec3(-halfWidth, -halfHeight, halfDepth),
		glm::vec3(halfWidth, -halfHeight, halfDepth),
		glm::vec3(halfWidth, halfHeight, halfDepth),
		glm::vec3(-halfWidth, halfHeight, halfDepth),
		glm::vec3(-halfWidth, -halfHeight, -halfDepth),
		glm::vec3(halfWidth, -halfHeight, -halfDepth),
		glm::vec3(halfWidth, halfHeight, -halfDepth),
		glm::vec3(-halfWidth, halfHeight, -halfDepth)
	};

	CreateTriangles();
	CreateUVs();
	CalculateNormals();
}


void Cube::CreateTriangles()
{
	this->trianglesSize = 36;
	triangles = new GLuint[trianglesSize]{
			0,1,2,
			0,2,3,
			1,5,6,
			1,6,2,
			5,4,7,
			5,7,6,
			4,0,3,
			4,3,7,
			3,7,6,
			3,6,2,
			0,1,5,
			0,5,4
	};
}

void Cube::CreateUVs()
{
	uvsShape = {
		glm::vec2(0.0f, 0.0f), // 0: bottom left
		glm::vec2(1.0f, 0.0f), // 1: bottom right
		glm::vec2(1.0f, 1.0f), // 2: top right
		glm::vec2(0.0f, 0.0f), // 3: bottom left
		glm::vec2(1.0f, 1.0f), // 4: top right
		glm::vec2(0.0f, 1.0f), // 5: top left
	};
}
