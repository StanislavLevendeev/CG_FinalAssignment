#pragma once
#include <GL/glew.h>
#include "VertexAttribute.h"
#include "VertexBuffer.h"

class VertexArray
{
private:
	static int count;
public:
	GLuint rendererID;
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;
	void AddBuffer(VertexAttribute&, VertexBuffer&);
};
