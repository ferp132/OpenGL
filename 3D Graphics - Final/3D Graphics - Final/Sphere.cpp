#include "Sphere.h"
#include "GameManager.h"

/*
	float radius = 0.5f;

	const int sections = 30;
	const int vertexAttrib = 8;
	const int indexPerQuad = 6;

	double phi = 0;
	double theta = 0;

	float vertices[(sections) * (sections)* vertexAttrib];
	int offset = 0;
	for (int i = 0; i < sections; i++)
	{
		theta = 0;

		for (int j = 0; j < sections; j++)
		{
			float x = float(cos(phi) * sin(theta));
			float y = float(cos(theta));
			float z = float(sin(phi) * sin(theta));

			vertices[offset++] = x * radius;
			vertices[offset++] = y * radius;
			vertices[offset++] = z * radius;

			vertices[offset++] = x;
			vertices[offset++] = y;
			vertices[offset++] = z;

			vertices[offset++] = (float)i / (sections - 1);
			vertices[offset++] = (float)j / (sections - 1);

			theta += (M_PI / (sections - 1));
		}

		phi += (2 * M_PI) / (sections - 1);
	}


	GLuint indices[(sections) * (sections)* indexPerQuad];
	offset = 0;
	for (int i = 0; i < sections; i++)
	{
		for (int j = 0; j < sections; j++)
		{
			indices[offset++] = (((i + 1) % sections) * sections) + ((j + 1) % sections);
			indices[offset++] = (i * sections) + (j);
			indices[offset++] = (((i + 1) % sections) * sections) + (j);

			indices[offset++] = (i * sections) + ((j + 1) % sections);
			indices[offset++] = (i * sections) + (j);
			indices[offset++] = (((i + 1) % sections) * sections) + ((j + 1) % sections);
		}
	}

	*/

Sphere::Sphere()
{
}

Sphere::~Sphere()
{
}

void Sphere::Init(float InitxPos, float InityPos, float initzPos, float InitHeight, float InitWidth, float InitLength, const std::string & InitTexFP)
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
	zPos = initzPos;


	float radius = 0.5f;

	const int sections = 30;
	const int vertexAttrib = 8;
	const int indexPerQuad = 6;

	double phi = 0;
	double theta = 0;

	GLfloat vertices[(sections) * (sections)* vertexAttrib];
	int offset = 0;
	for (int i = 0; i < sections; i++)
	{
		theta = 0;

		for (int j = 0; j < sections; j++)
		{
			float x = float(cos(phi) * sin(theta));
			float y = float(cos(theta));
			float z = float(sin(phi) * sin(theta));

			vertices[offset++] = x * radius;
			vertices[offset++] = y * radius;
			vertices[offset++] = z * radius;

			vertices[offset++] = x;
			vertices[offset++] = y;
			vertices[offset++] = z;

			vertices[offset++] = (float)i / (sections - 1);
			vertices[offset++] = (float)j / (sections - 1);

			theta += (M_PI / (sections - 1));
		}

		phi += (2 * M_PI) / (sections - 1);
	}


	GLuint indices[(sections) * (sections)* indexPerQuad];
	offset = 0;
	for (int i = 0; i < sections; i++)
	{
		for (int j = 0; j < sections; j++)
		{
			indices[offset++] = (((i + 1) % sections) * sections) + ((j + 1) % sections);
			indices[offset++] = (i * sections) + (j);
			indices[offset++] = (((i + 1) % sections) * sections) + (j);

			indices[offset++] = (i * sections) + ((j + 1) % sections);
			indices[offset++] = (i * sections) + (j);
			indices[offset++] = (((i + 1) % sections) * sections) + ((j + 1) % sections);
		}
	}

	UpdateModel();

	VAO.Init();
	VBO.Init(vertices, sizeof(vertices), GL_STATIC_DRAW);
	IBO.Init(indices, (sections) * (sections)* indexPerQuad);
	Lay.Push<float>(3);		//Vertices
	Lay.Push<float>(3);		//Normals
	Lay.Push<float>(2);		//Texture
	VAO.AddBuffer(VBO, Lay);

	Tex.Bind(GL_TEXTURE_2D);
	Tex.Init(InitTexFP);
	Tex.SetSlot(0);

	Shad.Init("Resources/Shaders/BlinnPhong.shader");
	Shad.Bind();
	Shad.setUniform1i("u_Texture", 0);						//Set Texture Uniform
	Shad.Unbind();
}

void Sphere::Render()
{
	UpdateModel();
	glm::mat4 MVP = GameManager::GetInstance()->GetCam()->GetPxV() * Model;
	glm::vec3 CameraPosition = GameManager::GetInstance()->GetCam()->getPosition();
	//Bind Shader
	Shad.Bind();
	Shad.setUniformMat4f("u_MVP", MVP);
	Shad.setUniformMat4f("model", Model);
	Shad.setUniform3f("camPos", CameraPosition.x, CameraPosition.y, CameraPosition.z);

	VAO.Bind();
	VBO.Bind();
	IBO.Bind();
	Shad.Bind();
	Tex.Bind(GL_TEXTURE_2D);

	GLCall(glDrawElements(GL_TRIANGLES, IBO.GetCount(), GL_UNSIGNED_INT, nullptr));

	VAO.Unbind();
	VBO.UnBind();
	IBO.UnBind();

	glDisable(GL_BLEND);
}

void Sphere::UpdateModel()
{
	Model = glm::scale(glm::mat4(), glm::vec3(Width, Height, Length));
}
