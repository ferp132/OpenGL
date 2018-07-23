#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "ShaderLoader.h"
#include <iostream>
#include <map>

GLuint program;
GLuint VBO;				//Vertex Buffer Object
GLuint VAO;				//Vertex Array Object
GLfloat vertices[] = {
	//Position			//color
   -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, //Left
	0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f, //Right
	0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, //Top

	//Position			//color
	0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f, //Bottom
	0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, //Left
	1.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, //Right
	
};

void Init();
void render(void);
void Update();

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Triangle");
	glClearColor(1.0, 0.0, 0.0, 1.0); //clear red
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glewInit();
	Init();

	//register callbacks
	glutDisplayFunc(render);
	glutIdleFunc(Update);
	glutMainLoop();						//Ensure this is the last glut line called
	return 0;
}

void Init()
{
	ShaderLoader shaderLoader;
	program = shaderLoader.CreateProgram("VertexShader.vs", "FragmentShader.fs");
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*)0);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);	//clear red

	glUseProgram(program);
	glBindVertexArray(VAO);				//Bind VAO
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);				//Unbind VAO

	glutSwapBuffers();
}

void Update()
{
	//Update game information.
	GLfloat currentTime = glutGet(GLUT_ELAPSED_TIME);	//Get Current time
	currentTime = currentTime / 1000;					// Convert millisecond to seconds

	GLint currentTimeLoc = glGetUniformLocation(program, "currentTime");
	glUniform1f(currentTimeLoc, currentTime);

	glutPostRedisplay();		//Render function is called
}