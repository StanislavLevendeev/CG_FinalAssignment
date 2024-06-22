#pragma once
#include "Geometry.h"
#include "IndexBuffer.h"
class PrimitiveGeometry : public Geometry
{
private:
public:
	PrimitiveGeometry();
	~PrimitiveGeometry();
	void Draw(GLProgram& program, const glm::mat4 view) const override;
	void SetUp(const GLuint programID);
	int trianglesSize;
	GLuint* triangles;
	std::vector<glm::vec3> verticesShape;
	std::vector<glm::vec3> normalsShape;
	std::vector<glm::vec2> uvsShape;
protected:
	void CalculateNormals();
	virtual void CreateTriangles() = 0;
	virtual void CreateUVs() = 0;

};

