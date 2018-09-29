#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "ShaderLoader.h"
#include "Dependencies\soil\SOIL.h"
#include "Renderer.h"
#include "IndexBuffer.h"
#include "vertexbuffer.h"
#include "VertexArray.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;

};

#define M_PI 3.1415926535897932384626433832795

using namespace std;


int location;
GLuint shader;
GLuint VAO;

GLfloat vertices[] = {
	//Hexagon
	//Position
	-0.5f, -0.5f,
	0.5f, -0.5f,
	0.5f, 0.5f,
	-0.5f, 0.5f

};

GLuint indices[] = {
	0, 1, 2,	// First Triangle
	2, 3, 0
};

VertexArray* vap;
VertexBuffer* vbp;
VertexBufferLayout* lp;
IndexBuffer* ibp;

//-----

//GLuint program;
//GLuint VBO, VBO2;				//Vertex Buffer Object
	
//, VAO2;				//Vertex Array Object
//GLuint EBO, EBO2;
//GLuint RaymanTex;
//GLuint AwesomeDTex;
//std::string RayFilepath = "Rayman.jpg";
//std::string AweFilepath = "AwesomeFace.png";
//float RotationValue = 0.0f;

/*
GLuint indices2[] = {
	0, 1, 2,	// Seventh
	0, 2, 3,	//eighth
};

GLfloat vertices2[] = {
	//Quad
	//Position					//color				//Tex Coords
	-0.2f, -0.2f, 0.0f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,		//Bottom Left		
	-0.2f,  0.2f, 0.0f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		//Top Left
	 0.2f,  0.2f, 0.0f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,		//Top Right
	 0.2f, -0.2f, 0.0f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,		//Bottom Right
};
*/



void Init();
void render(void);
//void Update();
static GLuint CompileShader(GLuint type, const std::string& source);
static GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
static ShaderProgramSource ParseShader(const std::string& filepath);

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





	vap->Bind();
	//register callbacks
	glutDisplayFunc(render);
	//glutIdleFunc(Update);
	glutMainLoop();						//Ensure this is the last glut line called
	return 0;
}

void Init()
{
	GLCall(glGenVertexArrays(1, &VAO));
	GLCall(glBindVertexArray(VAO));

	VertexArray va;
	vap = &va;
	VertexBuffer vb(vertices, 6 * sizeof(GLfloat));
	vbp = &vb;
	VertexBufferLayout layout;
	lp = &layout;
	IndexBuffer ib(indices, sizeof(indices));
	ibp = &ib;

	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

//	ShaderLoader shaderLoader;
	//program = shaderLoader.CreateProgram("VertexShader.vs", "FragmentShader.fs");
	
	ShaderProgramSource source = ParseShader("Resources/Shaders/Basic.shader");
	shader = CreateShader(source.VertexSource, source.FragmentSource);
	GLCall(glUseProgram(shader));



	//-----Hexagon

	GLCall(location = glGetUniformLocation(shader, "u_Color"));
	ASSERT(location != -1);

	/*
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

*/
}

void render(void)
{

	float r = 0.0f;
	float increment = 0.05f;

	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	GLCall(glClearColor(0.0, 0.0, 0.0, 1.0));

	GLCall(glUseProgram(shader));
	GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));
	vap->Bind();
	ibp->Bind();
	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

	if (r > 1.0f)
		increment = -0.5f;
	else if (r < 0.0f)
		increment = 0.5f;

	r += increment;

	/*
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

	GLint RotationLoc = glGetUniformLocation(program, "Rotation");
	glUniform1f(RotationLoc, RotationValue);
	if (RotationValue > 2 * M_PI)
	{
		RotationValue = 0.0f;
	}
	RotationValue += M_PI / 100;
	

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);				//Unbind VAO2
	*/
	glutSwapBuffers();
}
/*
void Update()
{
	//Update game information.
	GLfloat currentTime = (GLfloat)glutGet(GLUT_ELAPSED_TIME);	//Get Current time
	currentTime = currentTime / 1000;					// Convert millisecond to seconds

	GLint currentTimeLoc = glGetUniformLocation(program, "currentTime");
	glUniform1f(currentTimeLoc, currentTime);

	glutPostRedisplay();		//Render function is called
}
*/
static GLuint CompileShader(GLuint type, const std::string& source)
{
	GLuint id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << endl;
		cout << message << endl;
		return 0;

	}
	return id;
}

static GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLuint Program = glCreateProgram();
	GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(Program, vs);
	glAttachShader(Program, fs);
	glLinkProgram(Program);
	glValidateProgram(Program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return Program;
}

static ShaderProgramSource ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath); 

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}	
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}
