#pragma once
#include "Mesh.h"
const int TICKS_TO_CHANGE_WHITEBOARD_TEXTURE = 20;
class Whiteboard :
	public Mesh
{
public:
	Whiteboard();
	Whiteboard(unsigned int programId);
	void Animate();

private:
	int ticks = 0;
	int textureIndex = 1;
};

