#include "VertexAttribute.h"
#include "Renderer.h"

VertexAttribute::VertexAttribute(GLuint program, const GLchar* name, GLint size, GLenum type, GLboolean normalized)
	:size(size), type(type), normalized(normalized)
{
	GLCall(this->rendererID = glGetAttribLocation(program, name));
}

VertexAttribute::~VertexAttribute()
{

}

void VertexAttribute::Define()
{
	GLCall(glVertexAttribPointer(this->rendererID, this->size, this->type, this->normalized, 0, 0));
	GLCall(glEnableVertexAttribArray(this->rendererID));
}
