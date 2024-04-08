#pragma once
#include <GL/glew.h>
class VertexAttribute
{
private:
public:
	GLuint rendererID;
	const GLchar* name;
	GLint size;
	GLenum type;
	GLboolean normalized;
	VertexAttribute(GLuint program, const GLchar* name, GLint size, GLenum type, GLboolean normalized);
	~VertexAttribute();
	void Define();
};

