#include "JsonReader.h"
#include <fstream>
#include "Cube.h"
#include "objloader.h"
std::vector<Mesh*> JsonReader::ReadJson(const std::string& jsonFilePath)
{
	std::ifstream f("Meshes.json");
	if (!f.is_open())
		throw std::runtime_error("Could not open file");
	json data;
	f >> data;
	f.close();
	if (!data.is_array())
		throw std::runtime_error("Could not open file");
	std::vector<Mesh*> meshes;
	for (const auto& mesh : data) {
		meshes.push_back(ParseMesh(mesh));
	}
	return meshes;
}

JsonReader::JsonReader(unsigned int programId)
{
	this->programId = programId;
}

Mesh* JsonReader::ParseMesh(const json meshJson)
{
	Mesh* mesh;
	if (meshJson.contains("geometry") &&
		meshJson["geometry"].is_object() &&
		meshJson.contains("material") &&
		meshJson["material"].is_object()) {
		Geometry* geometry = ParseGeometry(meshJson["geometry"]);
		Material* material = ParseMaterial(meshJson["material"]);
		mesh = new Mesh(geometry, material);
	}
	else
		mesh = new Mesh();
	if (meshJson.contains("position") && meshJson["position"].is_array())
		mesh->Translate(glm::vec3(meshJson["position"][0], meshJson["position"][1], meshJson["position"][2]));
	if (meshJson.contains("rotation") && meshJson["rotation"].is_array())
		mesh->Rotate(glm::vec3(meshJson["rotation"][0], meshJson["rotation"][1], meshJson["rotation"][2]));
	if (meshJson.contains("scale") && meshJson["scale"].is_array())
		mesh->Scale(glm::vec3(meshJson["scale"][0], meshJson["scale"][1], meshJson["scale"][2]));

	return mesh;
}

Material* JsonReader::ParseMaterial(const json materialJson)
{
	Material* material = new Material();
	if (materialJson.contains("ambient") && materialJson["ambient"].is_array() &&
		materialJson.contains("diffuse") && materialJson["diffuse"].is_array() &&
		materialJson.contains("specular") && materialJson["specular"].is_array() &&
		materialJson.contains("shininess") && materialJson["shininess"].is_number()) {
		material->ambient = glm::vec3(materialJson["ambient"][0], materialJson["ambient"][1], materialJson["ambient"][2]);
		material->diffuse = glm::vec3(materialJson["diffuse"][0], materialJson["diffuse"][1], materialJson["diffuse"][2]);
		material->specular = glm::vec3(materialJson["specular"][0], materialJson["specular"][1], materialJson["specular"][2]);
		material->shininess = materialJson["shininess"];
	}

	return material;
}


Geometry* JsonReader::ParseGeometry(const json geometryJson)
{
	Geometry* geometry;
	if (geometryJson.contains("type") && geometryJson["type"].is_string()) {
		std::string type = geometryJson["type"];
		if (geometryJson["type"] == "cube") {
			geometry = new Cube(programId);
		}
		else
			geometry = new Cube(programId);

	}
	else {
		vector<glm::vec3> vertices, normals;
		vector<glm::vec2> uvs;
		bool res;

		std::string fileName = geometryJson["file"];
		std::cout << fileName << std::endl;
		std::cout << "I'm trying to get geometry" << std::endl;
		res = loadOBJ(fileName.c_str(), vertices, uvs, normals);
		geometry = new Geometry(vertices, normals, uvs, programId);

		std::cout << "Geometry got succesfully" << std::endl;
	}
	if (geometryJson.contains("texture") && geometryJson["texture"].is_string()) {
		std::cout << geometryJson["texture"] << std::endl;
		std::cout << "I'm trying to get Texture" << std::endl;
		geometry->SetTexture(new Texture(geometryJson["texture"]));
		std::cout << "Texture got succesfully" << std::endl;
	}

	else
		geometry->color = glm::vec3(geometryJson["color"][0], geometryJson["color"][1], geometryJson["color"][2]);


	return geometry;
}
