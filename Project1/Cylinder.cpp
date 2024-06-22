#define _USE_MATH_DEFINES
#include "Cylinder.h"
#include <cmath>
Cylinder::Cylinder()
{
}

Cylinder::Cylinder(float height, float radius, int sectors, const GLuint programId) :height(height), radius(radius), sectors(sectors)
{
	CreateVertices();
	CreateTriangles();
	SetUp(programId);
}

void Cylinder::CreateTriangles()
{
	std::vector<int> indices;
	int k1 = 0;                         // 1st vertex index at base
	int k2 = sectors + 1;           // 1st vertex index at top

	// indices for the side surface
	for (int i = 0; i < sectors; ++i, ++k1, ++k2)
	{
		indices.push_back(k1);
		indices.push_back(k1 + 1);
		indices.push_back(k2);

		// k2 => k1+1 => k2+1
		indices.push_back(k2);
		indices.push_back(k1 + 1);
		indices.push_back(k2 + 1);
	}
	int topCenterIndex = baseCenterIndex + sectors + 1;
	for (int i = 0, k = baseCenterIndex + 1; i < sectors; ++i, ++k)
	{
		if (i < sectors - 1)
		{
			indices.push_back(baseCenterIndex);
			indices.push_back(k + 1);
			indices.push_back(k);
		}
		else // last triangle
		{
			indices.push_back(baseCenterIndex);
			indices.push_back(baseCenterIndex + 1);
			indices.push_back(k);
		}
	}

	// indices for the top surface
	for (int i = 0, k = topCenterIndex + 1; i < sectors; ++i, ++k)
	{
		if (i < sectors - 1)
		{
			indices.push_back(topCenterIndex);
			indices.push_back(k);
			indices.push_back(k + 1);
		}
		else // last triangle
		{
			indices.push_back(topCenterIndex);
			indices.push_back(k);
			indices.push_back(topCenterIndex + 1);
		}
	}
	triangles = new GLuint[indices.size()];
	for (int i = 0; i < indices.size(); ++i)
		triangles[i] = indices[i];

	trianglesSize = indices.size();
}

std::vector<glm::vec3> Cylinder::GetUnitCircleVertices()
{
	const float PI = 3.1415926f;
	float sectorStep = 2 * PI / sectors;
	float sectorAngle;  // radian

	std::vector<glm::vec3> unitCircleVertices;
	for (int i = 0; i <= sectors; ++i)
	{
		sectorAngle = i * sectorStep;
		unitCircleVertices.push_back(glm::vec3(cos(sectorAngle), sin(sectorAngle), 0));
	}
	return unitCircleVertices;
}

void Cylinder::CreateVertices()
{
	// clear memory of prev arrays
	std::vector<glm::vec3>().swap(verticesShape);
	std::vector<glm::vec3>().swap(normalsShape);
	std::vector<glm::vec2>().swap(uvsShape);

	// get unit circle vectors on XY-plane
	std::vector<glm::vec3> unitVertices = GetUnitCircleVertices();

	// put side vertices to arrays
	for (int i = 0; i < 2; ++i)
	{
		float h = -height / 2.0f + i * height;           // z value; -h/2 to h/2
		float t = 1.0f - i;                              // vertical tex coord; 1 to 0

		for (int j = 0, k = 0; j <= sectors; ++j, k++)
		{
			glm::vec3 vec = unitVertices[k];
			// position vector
			verticesShape.push_back(glm::vec3(vec.x * radius, vec.y * radius, h));
			// normal vector
			normalsShape.push_back(glm::vec3(vec.x, vec.y, vec.z));
			// texture coordinate
			uvsShape.push_back(glm::vec2((float)j / sectors, t));
		}
	}

	// the starting index for the base/top surface
	//NOTE: it is used for generating indices later
	this->baseCenterIndex = (int)verticesShape.size();

	// put base and top vertices to arrays
	for (int i = 0; i < 2; ++i)
	{
		float h = -height / 2.0f + i * height;           // z value; -h/2 to h/2
		float nz = -1 + i * 2;                           // z value of normal; -1 to 1

		// center point
		verticesShape.push_back(glm::vec3(0, 0, h));
		normalsShape.push_back(glm::vec3(0, 0, nz));
		uvsShape.push_back(glm::vec2(0.5f, 0.5f));

		for (int j = 0, k = 0; j < sectors; ++j, k++)
		{
			glm::vec3 vec = unitVertices[k];
			// position vector
			verticesShape.push_back(glm::vec3(vec.x * radius, vec.y * radius, h));
			// normal vector
			normalsShape.push_back(glm::vec3(0, 0, nz));
			// texture coordinate
			uvsShape.push_back(glm::vec2(-vec.x * 0.5f + 0.5f, -vec.y * 0.5f + 0.5f));
		}
	}
}

void Cylinder::SetUp(const GLuint programID)
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	// Populate vertices, normals, and uvs based on the triangles indices
	for (int i = 0; i < trianglesSize; ++i) {
		vertices.push_back(verticesShape[triangles[i]]);
		normals.push_back(normalsShape[triangles[i]]);
		uvs.push_back(uvsShape[triangles[i]]);
	}

	this->SetVertices(vertices, programID);
	this->SetNormals(normals, programID);
	this->SetUVs(uvs, programID);
}