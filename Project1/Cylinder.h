#pragma once
#include "PrimitiveGeometry.h"
class Cylinder : public PrimitiveGeometry
{
public:
	Cylinder();
	Cylinder(float height, float radius, int sides, const GLuint programId);
	void SetUp(const GLuint programID) override;
	int sectors;
	float radius;
	float height;
private:
	std::vector<glm::vec3> GetUnitCircleVertices();
	void CreateVertices();
	int baseCenterIndex;
	void CreateTriangles();
};

