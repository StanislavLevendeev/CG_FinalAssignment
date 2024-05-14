#pragma once
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include "VertexArray.h"
#include "GLProgram.h"
#include "Texture.h"
struct Dimensions {
	float width;
	float height;
	float depth;
};
class Geometry
{
public:
	Geometry();
	Geometry(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> uvs, const GLuint);
	~Geometry();
	void virtual Draw(GLProgram& program, const glm::mat4 view) const;
	void SetVertices(std::vector<glm::vec3> vertices, const GLuint);
	void SetNormals(std::vector<glm::vec3> normals, const GLuint);
	void SetTexture(Texture* texture);
	void SetUVs(std::vector<glm::vec2> uvs, const GLuint);
	void Translate(glm::vec3 translation);
	void Rotate(float angle, glm::vec3 axis);
	void Scale(glm::vec3 scale);
	bool HasTexture() const;
	VertexArray* vao;
	glm::mat4 GetModelMatrix() const;
	Texture* texture;
	glm::vec3 color;
protected:
	void CalculateDimensions();
	glm::mat4 model;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	Dimensions dimensions;
};
