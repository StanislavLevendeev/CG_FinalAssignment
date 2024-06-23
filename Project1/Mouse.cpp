#include "Mouse.h"
#include "objloader.h"
Mouse::Mouse() :Mesh()
{
}
Mouse::Mouse(unsigned int programId) :Mouse()
{
	std::vector<glm::vec3> vertices, normals;
	std::vector<glm::vec2> uvs;
	bool res;
	res = loadOBJ("Objects/mouse.obj", vertices, uvs, normals);
	this->geometry = new Geometry(vertices, normals, uvs, programId);
	this->geometry->scale = glm::vec3(0.03f, 0.03f, 0.03f);
	this->geometry->color = glm::vec3(0.0f, 0.0f, 0.0f);
	this->geometry->position = glm::vec3(-0.1, 0, 0);
	this->material = new Material();
	// Set material properties assuming its a plastic black mouse
	this->material->ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	this->material->diffuse = glm::vec3(0.01f, 0.01f, 0.01f);
	this->material->specular = glm::vec3(0.5f, 0.5f, 0.5f);
	this->material->shininess = 32.0f;
	this->position = glm::vec3(2.8f, 1.4f, -2.4f);
}

Mouse::~Mouse()
{
}

void Mouse::Animate()
{
	// Rotate the mouse around the y-axis
	this->rotation.y += 0.01f;
}
