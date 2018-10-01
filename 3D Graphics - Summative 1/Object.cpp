#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::Init(float InitxPos, float InityPos, float InitHeight, float InitWidth, const std::string& InitTexFP)
{

	Height = InitHeight;
	Width = InitWidth;

	GLfloat HalfWidth  = Width * 0.5;
	GLfloat HalfHeight = Height * 0.5;

	xPos = InitxPos - HalfWidth;
	yPos = InityPos - HalfHeight;

	GLfloat Vertices[4][4] = {
		//Position			//Texture
		0.0f, 0.0f,			1.0f, 1.0f,	//0, Bottom Left
		Width, 0.0f,		0.0f, 1.0f,	//1, Bottom Right
		Width, Height,		0.0f, 0.0f,	//2, Top Right
		0.0f, Width,		1.0f, 0.0f	//3, Top Left
	};

	UpdateModel();

	Tex.Init("Resources/Textures/AwesomeFace.png");
	Tex.Bind();
	Tex.SetSlot(1);

	Shad.Init("Resources/Shaders/Basic.shader");
	Shad.Bind();
	Shad.setUniform1i("u_Texture", 0);						//Set Texture Uniform
	Shad.Unbind();

	VAO.Init();
	VBO.Init(Vertices, 4 * 4 * sizeof(GLfloat), GL_DYNAMIC_DRAW);
	IBO.Init(Indices, sizeof(Indices));
	Lay.Push<float>(2);															//Vertices
	Lay.Push<float>(2);															//Texture
	VAO.AddBuffer(VBO, Lay);													//Stop using Shader
}

void Object::Render()
{
	//MVP calc
	UpdateModel();
	glm::mat4 Projection = glm::ortho(-400.0f, 400.0f, -400.0f, 400.0f, -1.0f, 1.0f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -1));
	glm::mat4 MVP = Projection * View * Model; //change to Camera.getview, get Projection?

	//Bind Shader
	Shad.Bind();
	Shad.setUniformMat4f("u_MVP", MVP);

	//Set Vertices
	GLfloat HalfWidth = Width * 0.5;
	GLfloat HalfHeight = Height * 0.5;

	GLfloat Vertices[4][4] = {
		//Position			//Texture
		-HalfWidth, -HalfHeight,		1.0f, 1.0f,	//0, Bottom Left
		 HalfWidth, -HalfHeight,		0.0f, 1.0f,	//1, Bottom Right
		 HalfWidth,  HalfHeight,		0.0f, 0.0f,	//2, Top Right
		-HalfWidth,  HalfHeight,		1.0f, 0.0f	//3, Top Left
	}; 

	VAO.Bind();
	VBO.Bind();	
	VBO.BufferSubData(Vertices, 4 * 4 * sizeof(GLfloat));
	IBO.Bind();
	Shad.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, IBO.GetCount(), GL_UNSIGNED_INT, nullptr));

	VAO.Unbind();
	VBO.UnBind();
	IBO.UnBind();

}

void Object::UpdateModel()
{
	Model = glm::translate(glm::mat4(1.0f),  glm::vec3(xPos + Width * 0.5, yPos + Height * 0.5, 0));
}
