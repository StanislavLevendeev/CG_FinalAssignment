#pragma once
#include <GL/glew.h>
class IndexBuffer
{
private:
	GLuint rendererID;
	unsigned int count;
public:
	IndexBuffer(const GLuint* data, unsigned int count);
	~IndexBuffer();
	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return count; }
};

