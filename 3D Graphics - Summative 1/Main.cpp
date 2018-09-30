#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
//Simple OpenGL Image Loader for Textures
#include "Dependencies\soil\SOIL.h"
//glm for OpenGL Maths
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"
//fmod
#include <fmod.hpp>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "vertexbuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "Texture.h"
#include "Camera.h"
#include "AudioSystem.h"
#include "TextLabel.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;



GLfloat vertices[] = {
	//Hexagon
	//Position
	200.0f, 200.0f, 1.0f, 1.0f,	//0
	600.0f, 200.0f, 0.0f, 1.0f,	//1
	600.0f, 600.0f,	0.0f, 0.0f, //2
	200.0f, 600.0f, 1.0f, 0.0f	//3

};

GLuint indices[] = {
	0, 1, 2,	// First Triangle
	2, 3, 0
};

TextLabel label;
VertexArray va;
VertexBuffer vb;
VertexBufferLayout layout;
IndexBuffer ib;
Shader shader;
Renderer renderer;
Texture tex;
Camera cam;
AudioSystem as;
FMOD::Sound* fxThump;
FMOD::Sound* trackBackground;

void Init();
void render(void);
void Update();

//-----Audio



//Matrices


glm::mat4 Projection = glm::ortho(0.0f, 800.0f, 0.0f, 800.0f, -1.0f, 1.0f);
glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -1));

glm::vec3 MoveVec = glm::vec3(0, 0, 0);
glm::mat4 Model = glm::translate(glm::mat4(1.0f), MoveVec);



glm::vec3 ScaleVec = glm::vec3(1.0, 1.0, 1.0);
glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), ScaleVec);

//glm::vec3 RotationAxisZ = glm::vec3(0.0f, 0.0f, 1.0f);
//glm::mat4 Rotation = glm::rotate(glm::mat4(), glm::radians(0), RotationAxisZ);
glm::mat4 MVP;

//-----Input

enum InputState
{
	UP,
	DOWN,
	UP_FIRST,
	DOWN_FIRST,
};
enum InputMouse
{
	MOUSE_LEFT,
	MOUSE_MIDDLE,
	MOUSE_RIGHT,
};

InputState KeyState[255];
InputState MouseState[3];

void KeyboardDown(unsigned char key, int x, int y)
{
	KeyState[key] = DOWN;
}

void KeyboardUp(unsigned char key, int x, int y)
{
	KeyState[key] = UP;
}

void ProcessInput()
{
	if (MouseState[MOUSE_LEFT] == DOWN)
	{
		as.PlaySound(fxThump);
	}


	if (KeyState['w'] == DOWN)
	{
		if (KeyState['d'] == DOWN || KeyState['a'] == DOWN) MoveVec.y += 2.5f;
		else MoveVec.y += 5.0f;
	}
	if (KeyState['s'] == DOWN) 
	{
		if (KeyState['d'] == DOWN || KeyState['a'] == DOWN) MoveVec.y -= 2.5f;
		else MoveVec.y -= 5.0f;
	}
	if (KeyState['d'] == DOWN)
	{
		if (KeyState['w'] == DOWN || KeyState['s'] == DOWN) MoveVec.x += 2.5f;
		else MoveVec.x += 5.0f;
	}
	if (KeyState['a'] == DOWN)
	{
		if (KeyState['w'] == DOWN || KeyState['s'] == DOWN) MoveVec.x -= 2.5f;
		else MoveVec.x -= 5.0f;
	}
}

void MouseClick(int button, int state, int x, int y)
{
	if (button >= 3)
		return;

	MouseState[button] = (state == GLUT_DOWN) ? DOWN : UP;
}

void MousePassiveMove(int x, int y)
{
	cout << "Passive x: " << x << " | y: " << y << endl;
}

void MouseMove(int x, int y)
{
	cout << "Clicked x: " << x << " | y: " << y << endl;
}



int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 50);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Triangle");
	glClearColor(1.0, 0.0, 0.0, 1.0); //clear red
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glewInit();
	Init();
	//register callbacks
	glutDisplayFunc(render);
	glutIdleFunc(Update);
	glutKeyboardFunc(KeyboardDown);
	glutKeyboardUpFunc(KeyboardUp);
	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseMove);
	glutPassiveMotionFunc(MousePassiveMove);
	glutMainLoop();						//Ensure this is the last glut line called
	return 0;
}

void Init()
{
	as.Init();
	fxThump = as.CreateSound("Resources/Sounds/Thump.wav", fxThump);
	trackBackground = as.CreateSound("Resources/Sounds/Background.mp3", trackBackground);
	
	cam.Init(800, 800);
	MVP = cam.GetPxV() * Model;

	label.Init("This is some juicy text", "Resources/Fonts/arial.ttf", glm::vec2(-350.0f, 300.0f), glm::vec3(1.0, 1.0, 1.0), 1.0f);

	tex.Init("Resources/Textures/AwesomeFace.png");
	va.Init();
	vb.Init(vertices, 4 * 4 * sizeof(GLfloat), GL_STATIC_DRAW);
	ib.Init(indices, sizeof(indices));
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	shader.Init("Resources/Shaders/Basic.shader");
	shader.Bind();
	//shader.setUniform4f("u_Color", 0.8, 0.3f, 0.8f, 1.0f);
	shader.setUniformMat4f("u_MVP", MVP);
	tex.Bind();
	tex.SetSlot(0);
	shader.setUniform1i("u_Texture", 0);
	shader.Unbind();
	
	as.PlaySound(trackBackground);
}

void render(void)
{
	
	renderer.Clear();
	renderer.rDraw(va, ib, shader);
	label.Render();

	glutSwapBuffers();
}


void Update()
{
	
	//Update game information.
	//GLfloat currentTime = (GLfloat)glutGet(GLUT_ELAPSED_TIME);	//Get Current time
//	currentTime = currentTime / 1000;					// Convert millisecond to seconds

	//-----Input
	ProcessInput();

	//-----Audio
	as.GetID()->update();
	Model = glm::translate(glm::mat4(1.0f), MoveVec);
	MVP = cam.GetPxV() * Model;

	shader.Bind();
	shader.setUniformMat4f("u_MVP", MVP);
	//shader.setUniform4f("u_Color", 0.8, 0.3f, 0.8f, 1.0f);
	shader.Unbind();
	glutPostRedisplay();
}






