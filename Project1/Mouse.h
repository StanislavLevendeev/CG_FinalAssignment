#pragma once
#include "Mesh.h"
class Mouse :
	public Mesh
{
public:
	Mouse();
	Mouse(unsigned int programId);
	~Mouse();
	void Animate();
};

