#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "ShaderLoader.h"
#include <iostream>
#include <map>

GLuint program;

void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0); //clear red

	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}

void Init() 
{
	ShaderLoader shaderLoader;
	program = shaderLoader.CreateProgram("VertexShader.vs", "FragmentShader.fs");
}

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
	glutMainLoop();						//Ensure this is the last glut line called
	return 0;
}