#pragma once
#include "Geometry.h"
#include "Material.h"
class Mesh
{
private:
	Geometry* geometry;
	Material* material;
public:
	Mesh();
	Mesh(Geometry* geometry, Material* material);
	~Mesh();
	void Draw(GLProgram& program, const glm::mat4 view) const;
	void SetGeometry(Geometry* geometry);
	void SetMaterial(Material* material);

};

