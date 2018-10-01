#include "Object.h"
#include "GameManager.h"
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
	Dir = 0;

	GLfloat HalfWidth  = (GLfloat)(Width * 0.5);
	GLfloat HalfHeight = (GLfloat)(Height * 0.5);

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



	VAO.Init();
	VBO.Init(Vertices, 4 * 4 * sizeof(GLfloat), GL_DYNAMIC_DRAW);
	IBO.Init(Indices, sizeof(Indices));
	Lay.Push<float>(2);															//Vertices
	Lay.Push<float>(2);															//Texture
	VAO.AddBuffer(VBO, Lay);													

	Tex.Bind();
	Tex.Init(InitTexFP);
	Tex.SetSlot(0);

	Shad.Init("Resources/Shaders/Basic.shader");
	Shad.Bind();
	Shad.setUniform1i("u_Texture", 0);						//Set Texture Uniform
	Shad.Unbind();
}

void Object::Render()
{

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//MVP calc
	UpdateModel();
	glm::mat4 MVP = GameManager::GetInstance()->GetCam()->GetPxV() * Model;
	//Bind Shader
	Shad.Bind();
	Shad.setUniformMat4f("u_MVP", MVP);

	//Set Vertices
	GLfloat HalfWidth = (GLfloat)(Width * 0.5);
	GLfloat HalfHeight = (GLfloat)(Height * 0.5);

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
	Tex.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, IBO.GetCount(), GL_UNSIGNED_INT, nullptr));

	VAO.Unbind();
	VBO.UnBind();
	IBO.UnBind();

	glDisable(GL_BLEND);
}

void Object::UpdateModel()
{

	glm::vec3 RotationAxisZ = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::mat4 Rotation = glm::rotate(glm::mat4(), glm::radians(Dir), RotationAxisZ);


	Model = (glm::translate(glm::mat4(1.0f),  glm::vec3(xPos + Width * 0.5, yPos + Height * 0.5, 0))) * Rotation;

}
