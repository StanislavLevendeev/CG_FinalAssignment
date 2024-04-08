#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "VertexArray.h"
#include "GLProgram.h"
class Geometry
{
public:
	Geometry();
	~Geometry();
	void Draw(GLProgram& program, const glm::mat4 view) const;
	void SetVertices(std::vector<glm::vec3> vertices, const GLuint );
	void SetNormals(std::vector<glm::vec3> normals, const GLuint);
	void SetUVs(std::vector<glm::vec2> uvs, const GLuint);
	void Translate(glm::vec3 translation);
	void Rotate(float angle, glm::vec3 axis);
	void Scale(glm::vec3 scale);
	VertexArray* vao;
	glm::mat4 GetModelMatrix() const;
private:
	glm::mat4 model;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

};
