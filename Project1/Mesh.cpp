#include "Mesh.h"

Mesh::Mesh() :
	geometry(nullptr), material(nullptr)
{

}

Mesh::Mesh(Geometry* geometry, Material* material)
{
	this->geometry = geometry;
	this->material = material;
}

Mesh::~Mesh()
{
	delete geometry, material;
}

void Mesh::Draw(GLProgram& program, const glm::mat4 view) const
{

	material->SetUniforms(program);
	geometry->Draw(program, view);
	material->UnsetUniforms(program);
}

void Mesh::SetGeometry(Geometry* geometry)
{
	this->geometry = geometry;
}

void Mesh::SetMaterial(Material* material)
{
	this->material = material;
}
