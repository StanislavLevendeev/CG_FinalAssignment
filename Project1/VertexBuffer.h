#pragma once

#include <GL/glew.h>


class VertexBuffer
{
private:
	const void* data;
public:
	GLuint rendererID;
	VertexBuffer(const void* data, GLuint size);
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;
};

