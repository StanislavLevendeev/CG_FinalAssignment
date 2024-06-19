#include "Cube.h"

Cube::Cube()
{
	vertices = {
		glm::vec3(-1.0, -1.0, 1.0),
		glm::vec3(1.0, -1.0, 1.0),
		glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(-1.0, 1.0, 1.0),
		glm::vec3(-1.0, -1.0, -1.0),
		glm::vec3(1.0, -1.0, -1.0),
		glm::vec3(1.0, 1.0, -1.0),
		glm::vec3(-1.0, 1.0, -1.0)
	};
	CreateTriangles();
	CreateUVs();
	CalculateNormals();
}

Cube::Cube(float height, float width, float depth)
{
	float halfHeight = height / 2.0f;
	float halfWidth = width / 2.0f;
	float halfDepth = depth / 2.0f;

	vertices = {
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
	triangles = new GLuint[36]{
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
	uvs = {
		   glm::vec2(0.0f, 0.0f), // Front bottom-left
		   glm::vec2(1.0f, 0.0f), // Front bottom-right
		   glm::vec2(1.0f, 1.0f), // Front top-right
		   glm::vec2(0.0f, 1.0f), // Front top-left
		   glm::vec2(0.0f, 0.0f), // Back bottom-left
		   glm::vec2(1.0f, 0.0f), // Back bottom-right
		   glm::vec2(1.0f, 1.0f), // Back top-right
		   glm::vec2(0.0f, 1.0f)  // Back top-left
	};
}
