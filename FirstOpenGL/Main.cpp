#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "ShaderLoader.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include <iostream>
#include <map>
#define M_PI 3.1415926535897932384626433832795

GLuint program;
GLuint VBO, VBO2;				//Vertex Buffer Object
GLuint VAO, VAO2;				//Vertex Array Object
GLuint EBO, EBO2;
GLuint RaymanTex;
GLuint AwesomeDTex;
std::string RayFilepath = "Rayman.jpg";
std::string AweFilepath = "AwesomeFace.png";
float RotationValue = 0.0f;

GLuint indices[] = {
	0, 2, 1,	// First Triangle
	0, 3, 2,	// Second Triangle
	0, 4, 3,	// Third Triangle
	0, 5, 4,	// Fourth Triangle
	0, 6, 5,	// Fith Triangle
	0, 1, 6,	// Sixth Triangle
};
GLuint indices2[] = {
	0, 1, 2,	// Seventh
	0, 2, 3,	//eighth
};
GLfloat vertices[] = {
	 //Hexagon
	 //Position				//color
     0.0f,  0.0f, 0.0f,		1.0f, 1.0f, 1.0f,	//Middle		
	-0.2f,  0.0f, 0.0f,		1.0f, 1.0f, 0.0f,	//Left			Yellow
	-0.1f,  0.175f, 0.0f,		0.0f, 1.0f, 0.0f,	//Top Left		Green
	 0.1f,  0.175f, 0.0f,		0.0f, 0.0f, 1.0f,	//Top Right		Blue
	 0.2f,  0.0f, 0.0f,		0.58f, 0.0f, 0.83f,	//Right			Violet
	 0.1f, -0.175f, 0.0f,		1.0f, 0.0f, 0.0f,	//Bottom Right	Red
	-0.1f, -0.175f, 0.0f,		1.0f, 0.65f, 0.0f,	//Bottom Left	
};
GLfloat vertices2[] = {
	//Quad
	//Position					//color				//Tex Coords
	-0.2f, -0.2f, 0.0f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,		//Bottom Left		
	-0.2f,  0.2f, 0.0f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		//Top Left
	 0.2f,  0.2f, 0.0f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,		//Top Right
	 0.2f, -0.2f, 0.0f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,		//Bottom Right
};


void Init();
void render(void);
void Update();

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
	glutMainLoop();						//Ensure this is the last glut line called
	return 0;
}

void Init()
{
	ShaderLoader shaderLoader;
	program = shaderLoader.CreateProgram("VertexShader.vs", "FragmentShader.fs");
	
	//-----Hexagon
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
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Hex EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//-----Quad
	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2);
	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);


	//Quad EBO
	glGenBuffers(1, &EBO2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

	////-----Culling
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);
	//glEnable(GL_CULL_FACE);

	//-----Textures
	int width, height, channels;
	//Rayman
	glGenTextures(1, &RaymanTex);
	glBindTexture(GL_TEXTURE_2D, RaymanTex);

	unsigned char* RaymanImage = SOIL_load_image(RayFilepath.c_str(), &width, &height, &channels, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, RaymanImage);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(RaymanImage);
	glBindTexture(GL_TEXTURE_2D, 0);

	//AwesomeD

	glGenTextures(1, &AwesomeDTex);
	glBindTexture(GL_TEXTURE_2D, AwesomeDTex);

	unsigned char* AwesomeDImage = SOIL_load_image(AweFilepath.c_str(), &width, &height, &channels, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, AwesomeDImage);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(AwesomeDImage);
	glBindTexture(GL_TEXTURE_2D, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);	//clear red
		
	glUseProgram(program);
	glBindVertexArray(VAO);				//Bind VAO
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);				//Unbind VAO
	glBindVertexArray(VAO2);			//Bind VAO2

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, RaymanTex);
	glUniform1i(glGetUniformLocation(program, "RaymanTex"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, AwesomeDTex);
	glUniform1i(glGetUniformLocation(program, "AwesomeDTex"), 1);

	//-----Transformation Matrices

	glm::vec3 objPosition = glm::vec3(0.5f, 0.5f, 0.0f);
	glm::mat4 translationMatrix = glm::translate(glm::mat4(), objPosition);

	glm::vec3 rotationAxisZ = glm::vec3(0.0f, 0.0f, 1.0f);
	float rotationAngle = 180;
	glm::mat4 rotationZ = glm::rotate(glm::mat4(), glm::radians(rotationAngle), rotationAxisZ);

	glm::vec3 objScale = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(), objScale);

	glm::mat4 model = translationMatrix * rotationZ * scaleMatrix;
	GLuint modelLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	//--//

	GLint RotationLoc = glGetUniformLocation(program, "Rotation");
	glUniform1f(RotationLoc, RotationValue);
	if (RotationValue > 2 * M_PI)
	{
		RotationValue = 0.0f;
	}
	RotationValue+= M_PI / 100;

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);				//Unbind VAO2

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