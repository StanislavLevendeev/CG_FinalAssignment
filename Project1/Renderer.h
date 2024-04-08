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
private:
    // Private constructor to prevent external instantiation
    Renderer()
    {
        std::cout << "Renderer instance created."
            << std::endl;
    }

    // Private destructor to prevent external deletion
    ~Renderer()
    {
        std::cout << "Renderer instance destroyed."
            << std::endl;
    }

    // Private static instance variable
    static Renderer* instance;
public:
    void Draw(const VertexArray& va, GLProgram& program, const int, glm::mat4 mv) const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const GLProgram& program, glm::mat4 mv) const;
    void Clear() const;
    static Renderer& GetInstance()
    {
        // If the instance doesn't exist, create it
        if (!instance) {
            instance = new Renderer();
        }
        return *instance;
    }
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

};
