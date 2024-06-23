#include "JsonReader.h"
#include <fstream>
#include "Cube.h"
#include "Cylinder.h"
#include "objloader.h"
#include <iostream>
#include <stdexcept>

// Constructor to initialize the programId
JsonReader::JsonReader(unsigned int programId) : programId(programId) {}

// Function to read JSON file and return a vector of Mesh pointers
std::vector<Mesh*> JsonReader::ReadJson(const std::string& jsonFilePath)
{
	std::ifstream file(jsonFilePath);
	if (!file.is_open())
		throw std::runtime_error("Could not open file: " + jsonFilePath);

	json data;
	file >> data;
	file.close();

	if (!data.is_array())
		throw std::runtime_error("Invalid JSON format: expected an array");

	std::vector<Mesh*> meshes;
	for (const auto& meshJson : data) {
		meshes.push_back(ParseMesh(meshJson));
	}

	return meshes;
}

// Function to parse a single mesh from JSON
Mesh* JsonReader::ParseMesh(const json& meshJson)
{
	Mesh* mesh;

	if (meshJson.contains("geometry") && meshJson["geometry"].is_object() &&
		meshJson.contains("material") && meshJson["material"].is_object()) {
		Geometry* geometry = ParseGeometry(meshJson["geometry"]);
		Material* material = ParseMaterial(meshJson["material"]);
		mesh = new Mesh(geometry, material);
	}
	else if (meshJson.contains("meshes") && meshJson["meshes"].is_array()) {
		mesh = ParseMeshGroup(meshJson);
	}
	else
	{
		throw std::runtime_error("Mesh must have geometry and material or meshes");
		return nullptr;
	}

	if (meshJson.contains("position") && meshJson["position"].is_array())
		mesh->Translate(glm::vec3(meshJson["position"][0], meshJson["position"][1], meshJson["position"][2]));

	if (meshJson.contains("rotation") && meshJson["rotation"].is_array())
		mesh->Rotate(glm::vec3(meshJson["rotation"][0], meshJson["rotation"][1], meshJson["rotation"][2]));

	if (meshJson.contains("scale") && meshJson["scale"].is_array())
		mesh->Scale(glm::vec3(meshJson["scale"][0], meshJson["scale"][1], meshJson["scale"][2]));

	return mesh;
}

Texture* JsonReader::ParseTexture(const json& textureJson)
{
	if (textureJson.contains("fileName") && textureJson["fileName"].is_string())
	{
		std::string filename = textureJson["fileName"];
		if (textureJson.contains("scaleFactor") && textureJson["scaleFactor"].is_number()) {
			float scaleFactor = textureJson["scaleFactor"];
			return new Texture(filename, scaleFactor);
		}
		return new Texture(filename);
	}
	return nullptr;
}

// Function to parse material properties from JSON
Material* JsonReader::ParseMaterial(const json& materialJson)
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

// Function to parse geometry properties from JSON
Geometry* JsonReader::ParseGeometry(const json& geometryJson)
{
	Geometry* geometry;

	if (geometryJson.contains("type") && geometryJson["type"].is_string()) {
		std::string type = geometryJson["type"];
		if (type == "cube") {
			geometry = new Cube(programId);
		}
		else if (type == "cylinder") {
			if (!geometryJson.contains("height") || !geometryJson["height"].is_number() ||
				!geometryJson.contains("radius") || !geometryJson["radius"].is_number() ||
				!geometryJson.contains("sides") || !geometryJson["sides"].is_number())
				throw std::runtime_error("Cylinder geometry is missing height, radius, or sides");
			else
				geometry = new Cylinder(geometryJson["height"], geometryJson["radius"], geometryJson["sides"], programId);
		}
		else {
			throw std::runtime_error("Unknown geometry type: " + type);
		}
	}
	else {
		std::vector<glm::vec3> vertices, normals;
		std::vector<glm::vec2> uvs;
		bool res;

		if (!geometryJson.contains("file") || !geometryJson["file"].is_string())
			throw std::runtime_error("Geometry file is missing or not a string");

		std::string fileName = geometryJson["file"];
		std::cout << "Loading geometry from file: " << fileName << std::endl;
		res = loadOBJ(fileName.c_str(), vertices, uvs, normals);

		if (!res)
			throw std::runtime_error("Failed to load OBJ file: " + fileName);

		geometry = new Geometry(vertices, normals, uvs, programId);
	}
	if (geometryJson.contains("color") && geometryJson["color"].is_array()) {
		geometry->color = glm::vec3(geometryJson["color"][0], geometryJson["color"][1], geometryJson["color"][2]);
	}
	else if (geometryJson.contains("texture") && geometryJson["texture"].is_object()) {
		if (geometry)
			geometry->SetTexture(ParseTexture(geometryJson["texture"]));
	}
	else {
		throw std::runtime_error("Geometry must have either a texture or a color");
	}

	return geometry;
}

MeshGroup* JsonReader::ParseMeshGroup(const json& meshGroupJson)
{
	MeshGroup* meshGroup = new MeshGroup();

	if (meshGroupJson.contains("meshes") && meshGroupJson["meshes"].is_array()) {
		for (const auto& meshJson : meshGroupJson["meshes"]) {
			meshGroup->AddMesh(ParseMesh(meshJson));
		}
	}
	else {
		throw std::runtime_error("MeshGroup must have meshes");
	}
	if (meshGroupJson.contains("position") && meshGroupJson["position"].is_array())
		meshGroup->Translate(glm::vec3(meshGroupJson["position"][0], meshGroupJson["position"][1], meshGroupJson["position"][2]));
	if (meshGroupJson.contains("rotation") && meshGroupJson["rotation"].is_array())
		meshGroup->Rotate(glm::vec3(meshGroupJson["rotation"][0], meshGroupJson["rotation"][1], meshGroupJson["rotation"][2]));
	if (meshGroupJson.contains("scale") && meshGroupJson["scale"].is_array())
		meshGroup->Scale(glm::vec3(meshGroupJson["scale"][0], meshGroupJson["scale"][1], meshGroupJson["scale"][2]));

	return meshGroup;
}
