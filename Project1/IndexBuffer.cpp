#include "IndexBuffer.h"
#include "Renderer.h"
IndexBuffer::IndexBuffer(const GLuint* data, unsigned int count):count(count)
{
	GLCall(glGenBuffers(1, &this->rendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->rendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &rendererID));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->rendererID));
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
