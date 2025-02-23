#include "Renderer.h"
#include <iostream>
void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {//ASSERT(GLLogCall
	while (GLenum error = glGetError()) {
		std::cout << "OpenGL Error (" << error << ")" //to hex to get error type in glew.h
			<< " caused by " << function << " in line : " << line << std::endl;
		return false;
	}
	return true;
}
Renderer* Renderer::instance = nullptr;
void Renderer::Draw(const VertexArray& va, GLProgram& program, const int count, const glm::mat4 mv) const
{
	Clear();
	va.Bind();
	program.Bind();
	program.SetUniformMat4fv("mv", mv);

	GLCall(glDrawArrays(GL_TRIANGLES, 0, count));

	//GLCall(glutSwapBuffers());
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, GLProgram& program, glm::mat4 mv) const
{
	Clear();
	va.Bind();
	ib.Bind();
	program.Bind();
	program.SetUniformMat4fv("mv", mv);

	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
	//GLCall(glutSwapBuffers());
}

void Renderer::Clear() const
{
	//GLCall(glClearColor(0.0, 0.0, 0.0, 1.0));
	//GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
