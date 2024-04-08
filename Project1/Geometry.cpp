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

Geometry::~Geometry()
{
	delete vao;

}

void Geometry::Draw(GLProgram& program, const glm::mat4 view) const
{
	if (texture != nullptr) texture->Bind();
	glm::mat4 mv = view * model;
	Renderer::GetInstance().Draw(*vao, program, vertices.size(), mv);
	if (texture != nullptr)	texture->Unbind();
}



void Geometry::SetVertices(std::vector<glm::vec3> vertices, const GLuint programID)
{
	this->vertices = vertices;
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


glm::mat4 Geometry::GetModelMatrix() const
{
	return model;
}
