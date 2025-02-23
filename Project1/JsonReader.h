#pragma once
#include <string>
#include <vector>
#include "Mesh.h"
#include "MeshGroup.h"
#include "External Libraries/json.hpp"
using json = nlohmann::json;
class JsonReader
{
public:
	std::vector<Mesh*> ReadJson(const std::string& jsonFilePath);
	JsonReader(unsigned int);
private:
	unsigned int programId;
	Mesh* ParseMesh(const json& meshJson);
	Texture* ParseTexture(const json& textureJson);
	Material* ParseMaterial(const json& materialJson);
	Geometry* ParseGeometry(const json& geometryJson);
	MeshGroup* ParseMeshGroup(const json& meshGroupJson);
};
