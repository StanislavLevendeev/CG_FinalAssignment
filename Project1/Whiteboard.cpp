#include "Whiteboard.h"
#include <sstream>
#include "objloader.h"
Whiteboard::Whiteboard()
{
}

Whiteboard::Whiteboard(unsigned int programId)
{
	std::vector<glm::vec3> vertices, normals;
	std::vector<glm::vec2> uvs;
	bool res;
	res = loadOBJ("Objects/Whiteboard.obj", vertices, uvs, normals);
	this->geometry = new Geometry(vertices, normals, uvs, programId);
	this->geometry->scale = glm::vec3(1.5f, 1.73f, 1.5f);
	this->geometry->position = glm::vec3(0, 1, 0);
	std::stringstream ss;
	ss << "Textures/Whiteboard/Whiteboard" << textureIndex << ".bmp";
	std::string textureFilePath = ss.str();
	this->geometry->SetTexture(new Texture(textureFilePath));
	this->material = new Material();
	// Set material properties assuming its a plastic black mouse
	this->material->ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	this->material->diffuse = glm::vec3(0.01f, 0.01f, 0.01f);
	this->material->specular = glm::vec3(0.5f, 0.5f, 0.5f);
	this->material->shininess = 32.0f;
	this->position = glm::vec3(2.5f, 1.5f, -5.2f);
}

void Whiteboard::Animate()
{
	ticks++;
	if (ticks > TICKS_TO_CHANGE_WHITEBOARD_TEXTURE) {
		ticks = 0;
		textureIndex++;
		if (textureIndex > 11) {
			textureIndex = 1;
		}
		std::stringstream ss;
		ss << "Textures/Whiteboard/Whiteboard" << textureIndex << ".bmp";
		std::string textureFilePath = ss.str();
		delete this->geometry->texture;
		this->geometry->SetTexture(new Texture(textureFilePath));
	}
}
