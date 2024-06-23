#pragma once
#include "Mesh.h"
#include <vector>
#include "Transformable.h"
class MeshGroup :
	public Mesh
{
public:
	void Draw(GLProgram& program, const glm::mat4 view) const override;
	void AddMesh(Mesh* mesh);
	MeshGroup();
	~MeshGroup();
private:
	std::vector<Mesh*> meshes;
};

