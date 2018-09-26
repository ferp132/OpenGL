//----- Louis Cresswell
//----- 25/09/2018

//-----Library Includes
#include <iostream>

//-----Local Includes
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

void Render(void);
void Init();

//------GLuints
GLuint Program;

int main(int argc, char **argv)
{
	glutInit(&argc, argv);												//https://www.opengl.org/resources/libraries/glut/spec3/node10.html
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);			//https://www.opengl.org/resources/libraries/glut/spec3/node12.html
	glutInitWindowPosition(100, 100);									//https://www.opengl.org/resources/libraries/glut/spec3/node11.html
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL Window");									//https://www.opengl.org/resources/libraries/glut/spec3/node16.html

	glewInit();															//http://glew.sourceforge.net/basic.html
	Init();

	glClearColor(1.0, 0.0, 0.0, 1.0);									//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glClearColor.xhtml

	//Register Callbacks
	glutDisplayFunc(Render);											//https://www.opengl.org/resources/libraries/glut/spec3/node46.html
	glutMainLoop();														//https://www.opengl.org/resources/libraries/glut/spec3/node14.html
	
	return 0;

}

void Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);										//https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glClear.xml
	glClearColor(1.0, 0.0, 0.0, 1.0);

	glUseProgram(Program);												//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUseProgram.xhtml
	glDrawArrays(GL_TRIANGLES, 0, 3);									//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDrawArrays.xhtml

	glutSwapBuffers();													//https://www.opengl.org/resources/libraries/glut/spec3/node21.html
}

void Init()
{
	//-----Create Vertex Shader

	std::string vs_source = "Vertex.vs";
	const char* VS_CodePointer = vs_source.c_str();
	const int VS_CodePointerSize = vs_source.size();

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);						//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glCreateShader.xhtml
	glShaderSource(vs, 1, &VS_CodePointer, &VS_CodePointerSize);		//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glShaderSource.xhtml
	glCompileShader(vs);
	
	//-----Create Fragment Shader

	std::string fs_source = "Fragment.vs";
	const char* FS_CodePointer = fs_source.c_str();
	const int FS_CodePointerSize = fs_source.size();

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &FS_CodePointer, &FS_CodePointerSize);
	glCompileShader(fs);

	Program = glCreateProgram();										//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glCreateProgram.xhtml

	glAttachShader(Program, vs);										//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glAttachShader.xhtml
	glAttachShader(Program, fs);
	glLinkProgram(Program);
}