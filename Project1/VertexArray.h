#pragma once
#include <GL/glew.h>
#include "VertexAttribute.h"
#include "VertexBuffer.h"
#include <vector>
#include <tuple>

class VertexArray
{
private:
	static int count;
	std::vector<std::tuple<VertexAttribute*, VertexBuffer*>> buffer;
public:
	GLuint rendererID;
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;
	void AddBuffer(VertexAttribute*, VertexBuffer*);
};
