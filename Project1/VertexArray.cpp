#include "VertexArray.h"
#include "Renderer.h"

int VertexArray::count = 1;
VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(this->count, &this->rendererID));
	this->count++;
	GLCall(glBindVertexArray(this->rendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteBuffers(1, &rendererID));
}

void VertexArray::AddBuffer(VertexAttribute& vertexAttrib, VertexBuffer& vertexBuffer)
{
	vertexBuffer.Bind();
	vertexAttrib.Define();
	vertexBuffer.Unbind();
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(this->rendererID));
}
void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
