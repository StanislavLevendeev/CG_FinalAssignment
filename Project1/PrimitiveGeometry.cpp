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
