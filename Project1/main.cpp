#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"
#include "Renderer.h"
#include "GLProgram.h"
#include "Light.h"
#include "Camera.h"
#include "JsonReader.h"
#include "Mouse.h"
#include "Whiteboard.h"
//--------------------------------------------------------------------------------
// Consts
//--------------------------------------------------------------------------------

const int WIDTH = 800, HEIGHT = 600;

const char* fragshader_name = "fragmentshader.frag";
const char* vertexshader_name = "vertexshader.vert";

unsigned const int DELTA_TIME = 10;
unsigned const int UPDATETIME = 30;

//--------------------------------------------------------------------------------
// Typedefs
//--------------------------------------------------------------------------------

Light* light;

//--------------------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------------------

// ID's
GLProgram* program;

//Meshesrenderer
std::vector<Mesh*> meshes;

//JsonReader
JsonReader* reader = nullptr;

Camera cam;
Mouse* mouse = nullptr;
Whiteboard* whiteboard = nullptr;
bool Debug = false;
int currentTime = 0;

//--------------------------------------------------------------------------------
// Mouse poesition listener
//--------------------------------------------------------------------------------

void mousePositionListener(int x, int y) {
	cam.ProcessMouseMovement(x, y);
}
void mouseWheel(int button, int dir, int x, int y)
{
	cam.ProcessMouseScroll(dir);
	return;
}

//--------------------------------------------------------------------------------
// Keyboard handling
//--------------------------------------------------------------------------------

void keyboardHandler(unsigned char key, int a, int b)
{
	if (key == 27)
		glutExit();
	cam.ProcessKeyPressed(key);
}


//--------------------------------------------------------------------------------
// Rendering
//--------------------------------------------------------------------------------

void Render()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	currentTime++;
	if (Debug && currentTime >= UPDATETIME) {
		std::cout << "Rendering" << std::endl;
		for (Mesh* mesh : meshes)
			delete mesh;
		meshes.clear();
		meshes = reader->ReadJson("Meshes.json");
		currentTime = 0;
	}

	cam.SetUniforms(*program, WIDTH / HEIGHT);

	light->SetUniforms(*program);

	for (Mesh* mesh : meshes)
		mesh->Draw(*program, cam.GetViewMatrix());
	mouse->Animate();
	mouse->Draw(*program, cam.GetViewMatrix());
	whiteboard->Animate();
	whiteboard->Draw(*program, cam.GetViewMatrix());
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
// void InitMaterialsLight()
//------------------------------------------------------------

void InitMaterialsLight()
{
	light = new Light(glm::vec3(2.0, 5.0, 0.0));
}

void InitJsonReader() {
	reader = new JsonReader(program->GetID());
	meshes = reader->ReadJson("Meshes.json");
}
int main(int argc, char** argv)
{
	InitGlutGlew(argc, argv);
	InitShaders();
	InitJsonReader();
	InitMaterialsLight();
	mouse = new Mouse(program->GetID());
	whiteboard = new Whiteboard(program->GetID());
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	// Main loop
	glutMainLoop();
	for (Mesh* mesh : meshes)
		delete mesh;
	delete program, reader, light;
	return 0;
}
