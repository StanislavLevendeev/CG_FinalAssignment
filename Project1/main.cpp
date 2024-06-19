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
#include "Material.h"
#include "Mesh.h"
#include "Light.h"
#include "Camera.h"
#include "PrimitiveGeometry.h"
#include "Cube.h"


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

Light* light;

//--------------------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------------------

// ID's
GLProgram* program;
PrimitiveGeometry* cubeG;
Renderer* renderer = nullptr;
Geometry* cube = nullptr;
Geometry* torus = nullptr;
Mesh* cubeMesh = nullptr;
Mesh* torusMesh = nullptr;
Mesh* cubeGMesh = nullptr;

// Matrices
glm::mat4 model, view, projection;

Camera cam;

Material* material = nullptr;
int xS = 0, yS = 0;

//--------------------------------------------------------------------------------
// Mouse poesition listener
//--------------------------------------------------------------------------------

void mousePositionListener(int x, int y) {
	std::cout << "Mouse position: " << x << " " << y << std::endl;
	if (xS != 0 && yS != 0)
		cam.ProcessMouseMovement(x - xS, y - yS);
	xS = x;
	yS = y;
}
void mouseWheel(int button, int dir, int x, int y)
{
	cam.ProcessMouseScroll(dir);
	std::cout << "Mouse wheel: " << dir << std::endl;
	std::cout << "Button: " << button << " " << x << " " << y << std::endl;
	if (dir > 0)
	{
	}
	else
	{
		// Zoom out
	}

	return;
}

//--------------------------------------------------------------------------------
// Keyboard handling
//--------------------------------------------------------------------------------

void keyboardHandler(unsigned char key, int a, int b)
{
	if (key == 27)
		glutExit();
	if (key == 'I') {
		cam.Move(FORWARD, 1);
		view = cam.GetViewMatrix();
	}
	if (key == 'K') {
		cam.Move(BACKWARD, 1);
		view = cam.GetViewMatrix();
	}
	if (key == 'L') {
		cam.Move(RIGHT, 1);
		view = cam.GetViewMatrix();
	}
	if (key == 'J') {
		cam.Move(LEFT, 1);
		view = cam.GetViewMatrix();
	}
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
// Rendering
//--------------------------------------------------------------------------------

void Render()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	program->SetUniformMat4fv("projection", cam.GetProjectionMatrix(WIDTH / HEIGHT));
	cube->Rotate(0.01f, glm::vec3(0.5f, 1.0f, 0.2f));
	cubeMesh->Draw(*program, cam.GetViewMatrix());
	torus->Rotate(0.01f, glm::vec3(0.5f, 1.0f, 0.2f));
	torusMesh->Draw(*program, cam.GetViewMatrix());
	cubeG->Rotate(0.01f, glm::vec3(0.5f, 1.0f, 0.2f));
	cubeGMesh->Draw(*program, cam.GetViewMatrix());
	light->SetUniforms(*program);
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
	glutCreateWindow("Stanislav Levendeev's scene (s1169467)");
	glutDisplayFunc(Render);
	glutKeyboardFunc(keyboardHandler);
	glutTimerFunc(DELTA_TIME, Render, 0);
	glutPassiveMotionFunc(mousePositionListener);
	glutMouseWheelFunc(mouseWheel);
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
	program = new GLProgram(shaders, 2);
}


//------------------------------------------------------------
// void InitMatrices()
//------------------------------------------------------------

void InitMatrices()
{
	model = glm::mat4();
	view = cam.GetViewMatrix();

	projection = glm::perspective(
		glm::radians(45.0f),
		1.0f * WIDTH / HEIGHT, 0.1f,
		20.0f);
}

//------------------------------------------------------------
// void InitMaterialsLight()
//------------------------------------------------------------

void InitMaterialsLight()
{
	light = new Light(glm::vec3(4.0, 4.0, 4.0));

}
void InitUniforms() {
	program->SetUniformMat4fv("projection", cam.GetProjectionMatrix(45));
	light->SetUniforms(*program);
}
void InitGeometry() {
	vector<glm::vec3> vertices, normals;
	vector<glm::vec2> uvs;
	bool res;
	res = loadOBJ("Objects/box.obj", vertices, uvs, normals);
	cube = new Geometry(vertices, normals, uvs, program->GetID());

	vector<glm::vec3> vertices2, normals2;
	vector<glm::vec2> uvs2;
	bool res2;
	res2 = loadOBJ("Objects/torus.obj", vertices2, uvs2, normals2);

	torus = new Geometry(vertices2, normals2, uvs2, program->GetID());


	cubeG = new Cube();
	cubeG->SetUp(program->GetID());

}
void InitTextures() {
	cube->SetTexture(new Texture("Textures/Yellobrk.bmp"));

	cubeG->SetTexture(new Texture("Textures/Yellobrk.bmp"));
	torus->color = glm::vec3(0.0, 1.0, 0.0);
}
void InitRenderer() {
	renderer = &Renderer::GetInstance();
}

void InitMeshes() {
	cubeMesh = new Mesh(cube, material);
	//cubeMesh->Translate(glm::vec3(0.0, 1.0, 0.0));
	torusMesh = new Mesh(torus, material);
	cubeGMesh = new Mesh(cubeG, material);
	//cubeGMesh->Translate(glm::vec3(0.0, -1.0, 0.0));
}

void InitMaterial() {
	material = new Material();
	material->ambient = glm::vec3(0.2, 0.2, 0.1);
	material->diffuse = glm::vec3(0.5, 0.5, 0.3);
	material->specular = glm::vec3(1.0, 1.0, 1.0);
	material->shininess = 1024;
}
int main(int argc, char** argv)
{
	try
	{
		InitGlutGlew(argc, argv);
		InitShaders();
		InitRenderer();
		InitMatrices();
		InitGeometry();
		InitTextures();
		InitMaterial();
		InitMeshes();
		InitMaterialsLight();
		InitUniforms();

		// Hide console window
		HWND hWnd = GetConsoleWindow();
		ShowWindow(hWnd, SW_HIDE);

		// Main loop
		glutMainLoop();
	}
	catch (const std::exception&)
	{
		std::cerr << "An error occured" << std::endl;
		return 1;
	}
	return 0;
}
