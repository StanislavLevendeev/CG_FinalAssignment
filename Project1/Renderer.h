#pragma once
#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "GLProgram.h"
#include <glm/detail/type_mat.hpp>
#define ASSERT(x) if(!(x)) __debugbreak(); 
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__, __LINE__));


void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);
// ToDO make it a singleton
class Renderer
{
public:
	void Draw(const VertexArray& va, GLProgram& program, const int, glm::mat4 mv) const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const GLProgram& program, glm::mat4 mv) const;
	void Clear() const;

};