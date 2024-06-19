#pragma once
#include "Geometry.h"
#include "IndexBuffer.h"
class PrimitiveGeometry : public Geometry
{
private:
	IndexBuffer* ibo;
public:
	PrimitiveGeometry();

	PrimitiveGeometry(const GLuint programId);
	~PrimitiveGeometry();
	void Draw(GLProgram& program, const glm::mat4 view) const override;
	void SetUp(const GLuint programID);
	GLuint* triangles;
protected:
	void CalculateNormals();
	virtual void CreateTriangles() = 0;
	virtual void CreateUVs() = 0;

};

