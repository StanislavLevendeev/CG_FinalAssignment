#include "JsonReader.h"
#include <fstream>
#include "Cube.h"
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
	else {
		mesh = new Mesh();
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

	if (geometryJson.contains("texture") && geometryJson["texture"].is_object()) {
		if (geometry)
			geometry->SetTexture(ParseTexture(geometryJson["texture"]));
	}
	else if (geometryJson.contains("color") && geometryJson["color"].is_array()) {
		geometry->color = glm::vec3(geometryJson["color"][0], geometryJson["color"][1], geometryJson["color"][2]);
	}
	else {
		throw std::runtime_error("Geometry must have either a texture or a color");
	}

	return geometry;
}
