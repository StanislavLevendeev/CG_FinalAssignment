#include "Geometry.h"
#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
Geometry::Geometry()
	:
	texture(nullptr),
	model(1.0f),
	vao(new VertexArray()),
	vertices(), normals(), uvs()
{
}

Geometry::Geometry(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> uvs, const GLuint program) :
	texture(nullptr),
	model(1.0f),
	vao(new VertexArray())
{
	SetVertices(vertices, program);
	SetNormals(normals, program);
	SetUVs(uvs, program);
}

Geometry::~Geometry()
{
	delete vao;

}

void Geometry::Draw(GLProgram& program, const glm::mat4 view) const
{
	if (texture != nullptr) texture->Bind();
	else {
		program.SetUniform3fv("objectColor", color);
	}
	program.SetUniform1i("useTexture", HasTexture() ? 1 : 0);

	glm::mat4 mv = view * model;
	Renderer::GetInstance().Draw(*vao, program, vertices.size(), mv);
	if (texture != nullptr)	texture->Unbind();
}



void Geometry::SetVertices(std::vector<glm::vec3> vertices, const GLuint programID)
{
	this->vertices = vertices;
	CalculateDimensions();
	VertexBuffer* vbo = new VertexBuffer(&vertices[0], vertices.size() * sizeof(glm::vec3));
	VertexAttribute* vao = new VertexAttribute(programID, "position", 3, GL_FLOAT, GL_FALSE);
	this->vao->AddBuffer(*vao, *vbo);
}



void Geometry::SetNormals(std::vector<glm::vec3> normals, const GLuint programID)
{
	this->normals = normals;
	VertexBuffer* vbo = new VertexBuffer(&normals[0], normals.size() * sizeof(glm::vec3));
	VertexAttribute* vao = new VertexAttribute(programID, "normal", 3, GL_FLOAT, GL_FALSE);
	this->vao->AddBuffer(*vao, *vbo);
}

void Geometry::SetTexture(Texture* texture)
{
	this->texture = texture;
}

void Geometry::SetUVs(std::vector<glm::vec2> uvs, const GLuint programID)
{
	this->uvs = uvs;
	VertexBuffer* vbo = new VertexBuffer(&uvs[0], uvs.size() * sizeof(glm::vec2));
	VertexAttribute* vao = new VertexAttribute(programID, "uv", 2, GL_FLOAT, GL_FALSE);
	this->vao->AddBuffer(*vao, *vbo);
}

void Geometry::Translate(glm::vec3 translation)
{
	model = glm::translate(model, translation);
}

void Geometry::Rotate(float angle, glm::vec3 axis)
{
	model = glm::rotate(model, angle, axis);
}

void Geometry::Scale(glm::vec3 scale)
{
	model = glm::scale(model, scale);
}

bool Geometry::HasTexture() const
{
	return texture != nullptr;
}


glm::mat4 Geometry::GetModelMatrix() const
{
	return model;
}

void Geometry::CalculateDimensions()
{
	float minX = vertices[0].x, minY = vertices[0].y, minZ = vertices[0].z;
	float maxX = vertices[0].x, maxY = vertices[0].y, maxZ = vertices[0].z;

	for (const auto& vertex : vertices) {
		if (vertex.x < minX) minX = vertex.x;
		if (vertex.y < minY) minY = vertex.y;
		if (vertex.z < minZ) minZ = vertex.z;
		if (vertex.x > maxX) maxX = vertex.x;
		if (vertex.y > maxY) maxY = vertex.y;
		if (vertex.z > maxZ) maxZ = vertex.z;
	}

	dimensions.width = maxX - minX;
	dimensions.height = maxY - minY;
	dimensions.depth = maxZ - minZ;

}
