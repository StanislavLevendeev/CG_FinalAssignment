#pragma once
#include <string>
#include <vector>
#include "Mesh.h"
#include "External Libraries/json.hpp"
using json = nlohmann::json;
class JsonReader
{
public:
	std::vector<Mesh*> ReadJson(const std::string& jsonFilePath);
	JsonReader(unsigned int);
private:
	unsigned int programId;
	Mesh* ParseMesh(const json meshJson);
	Material* ParseMaterial(const json materialJson);
	Geometry* ParseGeometry(const json geometryJson);
};
