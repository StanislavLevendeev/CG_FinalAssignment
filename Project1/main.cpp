#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"
#include "objloader.h"
#include "texture.h"
#include "VertexBuffer.h"
#include "Renderer.h"
#include "VertexAttribute.h"
#include "VertexArray.h"
#include "GLProgram.h"



//--------------------------------------------------------------------------------
// Consts
//--------------------------------------------------------------------------------

const int WIDTH = 800, HEIGHT = 600;

const char* fragshader_name = "fragmentshader.frag";
const char* vertexshader_name = "vertexshader.vert";

unsigned const int DELTA_TIME = 10;


//--------------------------------------------------------------------------------
// Typedefs
//--------------------------------------------------------------------------------

struct LightSource
{
	glm::vec3 position;
};

struct Material
{
	glm::vec3 ambient_color;
	glm::vec3 diffuse_color;
};


//--------------------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------------------

// ID's
GLProgram* program_id;
VertexArray* vao = nullptr;
Renderer renderer;
Texture* texture;

// Uniform ID's
GLuint uniform_mv;

// Matrices
glm::mat4 model, view, projection;
glm::mat4 mv;

// Material and light
LightSource light;
Material material;

glm::vec3 specular;
float power;


//--------------------------------------------------------------------------------
// Mesh variables
//--------------------------------------------------------------------------------

vector<glm::vec3> vertices;
vector<glm::vec3> normals;
vector<glm::vec2> uvs;


//--------------------------------------------------------------------------------
// Keyboard handling
//--------------------------------------------------------------------------------

void keyboardHandler(unsigned char key, int a, int b)
{
	if (key == 27)
		glutExit();
}

//--------------------------------------------------------------------------------
// Error handling
//--------------------------------------------------------------------------------



//--------------------------------------------------------------------------------
// Rendering
//--------------------------------------------------------------------------------

void Render()
{
	// Do transformation
	model = glm::rotate(model, 0.01f, glm::vec3(0.5f, 1.0f, 0.2f));
	mv = view * model;

	renderer.Draw(*vao, *program_id, vertices.size(), mv);
	texture->Bind();
	// Swap buffers
	glutSwapBuffers();

}


//------------------------------------------------------------
// void Render(int n)
// Render method that is called by the timer function
//------------------------------------------------------------

void Render(int n)
{
	Render();
	glutTimerFunc(DELTA_TIME, Render, 0);
}


//------------------------------------------------------------
// void InitGlutGlew(int argc, char **argv)
// Initializes Glut and Glew
//------------------------------------------------------------

void InitGlutGlew(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Hello OpenGL");
	glutDisplayFunc(Render);
	glutKeyboardFunc(keyboardHandler);
	glutTimerFunc(DELTA_TIME, Render, 0);

	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);

	glewInit();
}


//------------------------------------------------------------
// void InitShaders()
// Initializes the fragmentshader and vertexshader
//------------------------------------------------------------

void InitShaders()
{
	Shader vertexShader(GL_VERTEX_SHADER, vertexshader_name);
	Shader fragmentShader(GL_FRAGMENT_SHADER, fragshader_name);
	Shader shaders[2] = { vertexShader, fragmentShader };
	program_id = new GLProgram(shaders, 2);
}


//------------------------------------------------------------
// void InitMatrices()
//------------------------------------------------------------

void InitMatrices()
{
	model = glm::mat4();
	view = glm::lookAt(
		glm::vec3(0.0, 2.0, 4.0),
		glm::vec3(0.0, 0.5, 0.0),
		glm::vec3(0.0, 1.0, 0.0));
	projection = glm::perspective(
		glm::radians(45.0f),
		1.0f * WIDTH / HEIGHT, 0.1f,
		20.0f);
	mv = view * model;
}


//------------------------------------------------------------
// void InitObjects()
//------------------------------------------------------------

void InitObjects()
{
	bool res;

	// Objects
	res = loadOBJ("Objects/box.obj", vertices, uvs, normals);
}


//------------------------------------------------------------
// void InitMaterialsLight()
//------------------------------------------------------------

void InitMaterialsLight()
{
	light.position = glm::vec3(4.0, 4.0, 4.0);
	material.ambient_color = glm::vec3(0.2, 0.2, 0.1);
	material.diffuse_color = glm::vec3(0.5, 0.5, 0.3);
	specular = glm::vec3(1.0, 1.0, 1.0);
	power = 1024;
	//material.diffuse_color = glm::vec3(0.5, 0.0, 0.0);
}


//------------------------------------------------------------
// void InitBuffers()
// Allocates and fills buffers
//------------------------------------------------------------

void InitBuffers()
{
	VertexBuffer vbo_vertex(&vertices[0], vertices.size() * sizeof(glm::vec3));
	VertexBuffer vbo_normal(&normals[0], normals.size() * sizeof(glm::vec3));
	VertexBuffer vbo_uv(&uvs[0], uvs.size() * sizeof(glm::vec2));

	VertexAttribute position(program_id->GetID(), "position", 3, GL_FLOAT, GL_FALSE);
	VertexAttribute normal(program_id->GetID(), "normal", 3, GL_FLOAT, GL_FALSE);
	VertexAttribute uv(program_id->GetID(), "uv", 2, GL_FLOAT, GL_FALSE);
	// Allocate memory for vao

	vao = new VertexArray();

	// Bind to vao

	// Bind vertices to vao

	(*vao).AddBuffer(position, vbo_vertex);

	// Bind normals to vao
	(*vao).AddBuffer(normal, vbo_normal);

	// Bind uvs to vao
	(*vao).AddBuffer(uv, vbo_uv);

	// Stop bind to vao
	(*vao).Unbind();


}
void InitUniforms() {
	// Make uniform vars
	uniform_mv = program_id->GetUniformLocation("mv");
	program_id->SetUniformMat4fv("projection", projection);
	program_id->SetUniform3fv("light_pos", light.position);
	program_id->SetUniform3fv("mat_ambient", material.ambient_color);
	program_id->SetUniform3fv("mat_diffuse", material.diffuse_color);
	program_id->SetUniform3fv("mat_specular", specular);
	program_id->SetUniform1f("mat_power", power);
}

void InitTextures() {
	texture = new Texture("Textures/Yellobrk.bmp");
}

int main(int argc, char** argv)
{

	InitGlutGlew(argc, argv);
	InitShaders();
	InitMatrices();
	InitUniforms();
	InitObjects();
	InitTextures();
	InitMaterialsLight();
	InitBuffers();

	// Hide console window
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	// Main loop
	glutMainLoop();

	return 0;
}
