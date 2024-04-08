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
#include "Geometry.h"



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
Renderer* renderer = nullptr;
Texture* texture;
Geometry* cube = nullptr;
Geometry* torus = nullptr;
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
// Keyboard handling
//--------------------------------------------------------------------------------

void keyboardHandler(unsigned char key, int a, int b)
{
	if (key == 27)
		glutExit();
	//if pressed W outzoom the camera by changing view matrix
	//if pressed arrow down inzoom the camera by changing view matrix

	if (key == 'W') {
		view = glm::lookAt(
			glm::vec3(0.0, 2.0, 6.0),
			glm::vec3(0.0, 0.5, 0.0),
			glm::vec3(0.0, 1.0, 0.0));
	}
	if (key == 'w') {
		view = glm::lookAt(
			glm::vec3(0.0, 2.0, 2.0),
			glm::vec3(0.0, 0.5, 0.0),
			glm::vec3(0.0, 1.0, 0.0));
	}
	if (key == 'd') {
		(*torus).Translate(glm::vec3(0.1, 0.0, 0.0));
	}
	if (key == 'D') {
		(*torus).Translate(glm::vec3(-0.1, 0.0, 0.0));
	}
	std::cout << "Key pressed: " << key << std::endl;
}

//--------------------------------------------------------------------------------
// Error handling
//--------------------------------------------------------------------------------



//--------------------------------------------------------------------------------
// Rendering
//--------------------------------------------------------------------------------

void Render()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	cube->Rotate(0.01f, glm::vec3(0.5f, 1.0f, 0.2f));
	cube->Draw(*program_id, view);
	torus->Rotate(0.01f, glm::vec3(0.5f, 1.0f, 0.2f));
	torus->Draw(*program_id, view);

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
// void InitMaterialsLight()
//------------------------------------------------------------

void InitMaterialsLight()
{
	light.position = glm::vec3(4.0, 4.0, 4.0);
	material.ambient_color = glm::vec3(0.2, 0.2, 0.1);
	material.diffuse_color = glm::vec3(0.5, 0.5, 0.3);
	specular = glm::vec3(1.0, 1.0, 1.0);
	power = 0;
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
void InitGeometry() {
	cube = new Geometry();
	vector<glm::vec3> vertices, normals;
	vector<glm::vec2> uvs;
	bool res;
	res = loadOBJ("Objects/box.obj", vertices, uvs, normals);
	(*cube).SetVertices(vertices, program_id->GetID());
	(*cube).SetNormals(normals, program_id->GetID());
	(*cube).SetUVs(uvs, program_id->GetID());

	torus = new Geometry();
	vector<glm::vec3> vertices2, normals2;
	vector<glm::vec2> uvs2;
	bool res2;
	res2 = loadOBJ("Objects/torus.obj", vertices2, uvs2, normals2);
	(*torus).SetVertices(vertices2, program_id->GetID());
	(*torus).SetNormals(normals2, program_id->GetID());
	(*torus).SetUVs(uvs2, program_id->GetID());
	(*torus).Translate(glm::vec3(2.0, 0.0, 0.0));


}
void InitTextures() {
	cube->SetTexture(new Texture("Textures/Yellobrk.bmp"));
	torus->SetTexture(new Texture("Textures/uvtemplate.bmp"));
}
void InitRenderer() {
	renderer = &Renderer::GetInstance();
}
int main(int argc, char** argv)
{

	InitGlutGlew(argc, argv);
	InitShaders();
	InitMatrices();
	InitRenderer();
	InitGeometry();
	InitTextures();
	InitUniforms();
	InitMaterialsLight();
	//InitBuffers();

	// Hide console window
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	// Main loop
	glutMainLoop();

	return 0;
}
