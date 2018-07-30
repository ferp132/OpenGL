#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "ShaderLoader.h"
#include "Dependencies\soil\SOIL.h"
#include <iostream>
#include <map>

GLuint program;
GLuint VBO, VBO2;				//Vertex Buffer Object
GLuint VAO, VAO2;				//Vertex Array Object
GLuint EBO;
GLuint tex;
GLuint indices[] = {
	0, 2, 1,  // First Triangle
	0, 3, 2,  // Second Triangle
	0, 4, 3,  // Third Triangle
	0, 5, 4,  // Fourth Triangle
	0, 6, 5,  // Fith Triangle
	0, 1, 6,  // Sixth Triangle

};
GLfloat vertices[] = {
	//Position			//color
     0.0f,  0.0f, 0.0f,	1.0f, 1.0f, 1.0f,	//Middle		
	-0.8f,  0.0f, 0.0f,	1.0f, 1.0f, 0.0f,	//Left			Yellow
	-0.4f,  0.8f, 0.0f,	0.0f, 1.0f, 0.0f,	//Top Left		Green
	 0.4f,  0.8f, 0.0f,	0.0f, 0.0f, 1.0f,	//Top Right		Blue
	 0.8f,  0.0f, 0.0f,	0.58f, 0.0f, 0.83f,	//Right			Violet
	 0.4f, -0.8f, 0.0f,	1.0f, 0.0f, 0.0f,	//Bottom Right	Red
	-0.4f, -0.8f, 0.0f,	1.0f, 0.65f, 0.0f,	//Bottom Left	
};

void Init();
void render(void);
void Update();

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(1000, 1000);
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

	//-----EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//-----Culling
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	//-----Textures
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	int width, height, channels;
	unsigned char* image = SOIL_load_image("h:\GitHub\OpenGL\FirstOpenGL\Rayman.jpg", &width, &height, &channels, SOIL_LOAD_RGBA);


}

void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);	//clear red
		
	glUseProgram(program);
	glBindVertexArray(VAO);				//Bind VAO
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
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