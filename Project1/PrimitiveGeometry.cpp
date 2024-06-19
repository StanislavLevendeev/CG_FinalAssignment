#include "PrimitiveGeometry.h"
#include "Renderer.h"

PrimitiveGeometry::PrimitiveGeometry() :Geometry()
{
}

PrimitiveGeometry::~PrimitiveGeometry()
{
	delete ibo;
	delete triangles;
}

void PrimitiveGeometry::Draw(GLProgram& program, const glm::mat4 view) const
{
	if (texture != nullptr) texture->Bind();
	else {
		program.SetUniform3fv("objectColor", color);
	}
	program.SetUniform1i("useTexture", HasTexture() ? 1 : 0);

	glm::mat4 mv = view * GetModelMatrix();
	Renderer::GetInstance().Draw(*vao, *ibo, program, mv);
	if (texture != nullptr)	texture->Unbind();
}

void PrimitiveGeometry::SetUp(const GLuint programID)
{
	this->SetVertices(vertices, programID);
	this->SetNormals(normals, programID);
	this->SetUVs(uvs, programID);
	this->vao->Bind();
	ibo = new IndexBuffer(triangles, 36);
	ibo->Bind();
	this->vao->Unbind();
}

void PrimitiveGeometry::CalculateNormals()
{
	normals.resize(vertices.size(), glm::vec3(0.0f));

	for (size_t i = 0; i < 36; i += 3) {
		glm::vec3 v0 = vertices[triangles[i]];
		glm::vec3 v1 = vertices[triangles[i + 1]];
		glm::vec3 v2 = vertices[triangles[i + 2]];
		glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
		normals[triangles[i]] += normal;
		normals[triangles[i + 1]] += normal;
		normals[triangles[i + 2]] += normal;
	}

	// Normalize normals
	for (size_t i = 0; i < normals.size(); ++i) {
		normals[i] = glm::normalize(normals[i]);
	}
}

