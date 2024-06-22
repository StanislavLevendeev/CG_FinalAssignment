#pragma once
#include "PrimitiveGeometry.h"

class Cube : public PrimitiveGeometry
{
public:
	Cube();
	Cube(const GLuint);
	Cube(float height, float width, float depth);
	// Inherited via PrimitiveGeometry
	void CreateTriangles() override;
	void CreateUVs() override;

};

