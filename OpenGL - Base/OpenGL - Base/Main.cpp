//----- Louis Cresswell
//----- 25/09/2018

//-----Library Includes
#include <iostream>

//-----Local Includes

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "ShaderLoader.h"

using namespace std;

void Render(void);
void Init();

//------GLuints
GLuint Program;
GLuint VBO;
GLuint VertexShader;

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

int main(int argc, char **argv)
{
	glutInit(&argc, argv);														//https://www.opengl.org/resources/libraries/glut/spec3/node10.html
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);					//https://www.opengl.org/resources/libraries/glut/spec3/node12.html
	glutInitWindowPosition(100, 100);											//https://www.opengl.org/resources/libraries/glut/spec3/node11.html
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL Window");											//https://www.opengl.org/resources/libraries/glut/spec3/node16.html

	glewInit();																	//http://glew.sourceforge.net/basic.html
	Init();

	glClearColor(1.0, 0.0, 0.0, 1.0);											//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glClearColor.xhtml

	//Register Callbacks
	glutDisplayFunc(Render);													//https://www.opengl.org/resources/libraries/glut/spec3/node46.html
	glutMainLoop();																//https://www.opengl.org/resources/libraries/glut/spec3/node14.html
	
	return 0;

}

void Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);												//https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glClear.xml
	glClearColor(1.0, 0.0, 0.0, 1.0);

	glUseProgram(Program);														//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUseProgram.xhtml
	glDrawArrays(GL_TRIANGLES, 0, 3);											//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDrawArrays.xhtml

	glutSwapBuffers();															//https://www.opengl.org/resources/libraries/glut/spec3/node21.html
}

void Init()
{
	char filename[] = "VertexShader.vs";
	char filename2[] = "FragmentShader.fs";
	//Generate the VBO & bind it to a unique ID
	glGenBuffers(1, &VBO);
	
	//buffer type of a VBO is GL_ARRAY_BUFFER
	//You can bind as many buffers as you want as long as they have a different type
	//Now bind this VBO to the GL_ARRAY_BUFFER target
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Now any calls made on the GL_ARRAY_BUFFER target will use the currently bound buffer, VBO.
	//Next we bind the previously defined vertex[] array int the current GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBufferData.xhtml

	ShaderLoader shaderLoader;
	Program = shaderLoader.CreateProgram(filename, filename2);

	VertexShader = glCreateShader(GL_VERTEX_SHADER);

}