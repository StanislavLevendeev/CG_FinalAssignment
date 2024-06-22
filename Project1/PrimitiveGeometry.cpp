#include "PrimitiveGeometry.h"
#include "Renderer.h"

PrimitiveGeometry::PrimitiveGeometry() : Geometry()
{
}

PrimitiveGeometry::~PrimitiveGeometry()
{
	delete[] triangles;
}

void PrimitiveGeometry::Draw(GLProgram& program, const glm::mat4 view) const
{
	if (texture != nullptr) texture->Bind(program);
	else {
		program.SetUniform3fv("objectColor", color);
	}
	program.SetUniform1i("useTexture", HasTexture() ? 1 : 0);

	glm::mat4 mv = view * GetModelMatrix();
	Renderer::GetInstance().Draw(*vao, program, vertices.size(), mv);
	if (texture != nullptr)	texture->Unbind();
}

void PrimitiveGeometry::SetUp(const GLuint programID)
{//based on triangles generate array of vertices normals and uvs
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

void PrimitiveGeometry::CalculateNormals()
{
	//calculate normals for each vertex
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

	// Normalize normals
	for (size_t i = 0; i < normalsShape.size(); ++i) {
		normalsShape[i] = glm::normalize(normalsShape[i]);
	}
}

