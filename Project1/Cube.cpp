#include "Cube.h"

Cube::Cube()
{
	verticesShape = {
		glm::vec3(-1.0f, -1.0f, 1.0f), 
		glm::vec3(1.0f, -1.0f, 1.0f), 
		glm::vec3(1.0f, 1.0f, 1.0f), 
		glm::vec3(-1.0f, 1.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f), 
		glm::vec3(1.0f, -1.0f, -1.0f), 
		glm::vec3(1.0f, 1.0f, -1.0f), 
		glm::vec3(-1.0f, 1.0f, -1.0f) 
	};
	CreateTriangles();
	CreateUVs();
	normalsShape = {
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, -1.0f), 
		glm::vec3(1.0f, 0.0f, 0.0f), 
		glm::vec3(-1.0f, 0.0f, 0.0f), 
		glm::vec3(0.0f, 1.0f, 0.0f), 
		glm::vec3(0.0f, -1.0f, 0.0f) 
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
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f), 
		glm::vec2(0.0f, 0.0f), 
		glm::vec2(1.0f, 1.0f), 
		glm::vec2(0.0f, 1.0f), 
	};
}

void Cube::SetUp(const GLuint programID)
{
	std::vector<glm::vec3> vertices;

	for (int i = 0; i < trianglesSize; i++)
	{
		vertices.push_back(verticesShape[triangles[i]]);
	}

	std::vector<glm::vec3> normals;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			normals.push_back(normalsShape[i]);
		}
	}
	std::vector<glm::vec2> uvs;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			uvs.push_back(uvsShape[j]);
		}
	}
	this->SetVertices(vertices, programID);
	this->SetNormals(normals, programID);
	this->SetUVs(uvs, programID);
	this->vao->Bind();
	this->vao->Unbind();
}

void Cube::CalculateNormals()
{
	normalsShape.resize(verticesShape.size());

	for (size_t i = 0; i < trianglesSize; i += 3) {
		glm::vec3 v1 = verticesShape[triangles[i]];
		glm::vec3 v2 = verticesShape[triangles[i + 1]];
		glm::vec3 v3 = verticesShape[triangles[i + 2]];

		glm::vec3 normal = glm::cross(v2 - v1, v3 - v1);

		normalsShape[triangles[i]] += normal;
		normalsShape[triangles[i + 1]] += normal;
		normalsShape[triangles[i + 2]] += normal;
	}

	for (size_t i = 0; i < normalsShape.size(); ++i) {
		normalsShape[i] = glm::normalize(normalsShape[i]);
	}

}
