#pragma once
#include "PrimitiveGeometry.h"

class Cube : public PrimitiveGeometry
{
public:
	Cube();
	Cube(const GLuint);
	Cube(float height, float width, float depth);
	void SetUp(const GLuint programID) override;
private:
	void CalculateNormals();
	void CreateTriangles();
	void CreateUVs();
};

