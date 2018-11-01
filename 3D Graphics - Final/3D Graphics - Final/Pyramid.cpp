#include "Pyramid.h"
#include "GameManager.h"
Pyramid::Pyramid()
{
}

Pyramid::~Pyramid()
{
}

void Pyramid::Init(float InitxPos, float InityPos, float InitzPos, float InitHeight, float InitLength, float InitWidth, const std::string& InitTexFP)
{

	Height = InitHeight;
	Width = InitWidth;
	Length = InitLength;
	Dir = 0;

	GLfloat HalfWidth = (GLfloat)(Width * 0.5);
	GLfloat HalfHeight = (GLfloat)(Height * 0.5);
	GLfloat HalfLength = (GLfloat)(Length * 0.5);

	xPos = InitxPos - HalfWidth;
	yPos = InityPos - HalfHeight;
	zPos = InitzPos;

	GLfloat Vertices[25] = {
		//Position							//Texture
		0.0f, 0.0f, 0.0f,					0.0f, 0.0f, // 0
		0.0f, 0.0f,  0.0f,					0.0f, 1.0f, // 1
		0.0f, 0.0f,  0.0f,					1.0f, 1.0f, // 2
		0.0f, 0.0f, 0.0f,					1.0f, 0.0f, // 3

		HalfWidth, Height, HalfLength,		0.5f, 0.5f, // 4, Top Point
	};

	UpdateModel();

	VAO.Init();
	VBO.Init(Vertices, sizeof(Vertices), GL_DYNAMIC_DRAW);
	IBO.Init(Indices, sizeof(Indices));
	Lay.Push<float>(3);															//Vertices
	Lay.Push<float>(2);															//Texture
	VAO.AddBuffer(VBO, Lay);

	Tex.Bind(GL_TEXTURE_2D);
	Tex.Init(InitTexFP);
	Tex.SetSlot(0);

	Shad.Init("Resources/Shaders/Basic.shader");
	Shad.Bind();
	Shad.setUniform1i("u_Texture", 0);						//Set Texture Uniform
	Shad.Unbind();
}

void Pyramid::Render()
{

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//MVP calc
	UpdateModel();
	glm::mat4 MVP = GameManager::GetInstance()->GetCam()->GetPxV() * Model;
	//Bind Shader
	Shad.Bind();
	Shad.setUniformMat4f("u_MVP", MVP);

	//Set Vertices
	GLfloat HalfWidth = (GLfloat)(Width * 0.5);
	GLfloat HalfHeight = (GLfloat)(Height * 0.5);
	GLfloat HalfLength = (GLfloat)(Height * 0.5);

	GLfloat Vertices[25] = {
		//Position							//Texture
		 HalfWidth, 0.0f,  HalfLength,		1.0f, 1.0f, // 0
		 HalfWidth, 0.0f, -HalfLength,		1.0f, 0.0f, // 1
		-HalfWidth, 0.0f, -HalfLength,		0.0f, 0.0f, // 2
		-HalfWidth, 0.0f,  HalfLength,		0.0f, 1.0f, // 3

		0.0f, HalfHeight-5, 0.0f,				0.5f, 0.5f, // 4, Top Point
	};

	VAO.Bind();
	VBO.Bind();
	VBO.BufferSubData(Vertices,sizeof(Vertices));
	IBO.Bind();
	Shad.Bind();
	Tex.Bind(GL_TEXTURE_2D);

	GLCall(glDrawElements(GL_TRIANGLES, IBO.GetCount(), GL_UNSIGNED_INT, nullptr));

	VAO.Unbind();
	VBO.UnBind();
	IBO.UnBind();

	glDisable(GL_BLEND);
}

void Pyramid::UpdateModel()
{

	glm::vec3 RotationAxisZ = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::mat4 Rotation = glm::rotate(glm::mat4(), glm::radians(Dir), RotationAxisZ);


	Model = (glm::translate(glm::mat4(1.0f), glm::vec3(xPos + Width * 0.5, yPos + Height * 0.5, zPos))) * Rotation;

}
