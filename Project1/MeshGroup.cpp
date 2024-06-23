#include "MeshGroup.h"

void MeshGroup::Draw(GLProgram& program, const glm::mat4 view) const
{
	for (Mesh* mesh : meshes)
		mesh->Draw(program, view * this->GetModelMatrix());

}

void MeshGroup::AddMesh(Mesh* mesh)
{
	meshes.push_back(mesh);
}

MeshGroup::MeshGroup()
{
}

MeshGroup::~MeshGroup()
{
	for (Mesh* mesh : meshes)
		delete mesh;
}
