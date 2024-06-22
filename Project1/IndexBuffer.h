#pragma once
#include <GL/glew.h>
class IndexBuffer
{
private:
	GLuint rendererID;
	unsigned int count;
	const GLuint* data;
public:
	IndexBuffer(const GLuint* data, unsigned int count);
	~IndexBuffer();
	void Bind() const;
	void Unbind() const;
	void Update(const GLuint* data, unsigned int count); // Example: Update IBO if needed
	inline unsigned int GetCount() const { return count; }
};

