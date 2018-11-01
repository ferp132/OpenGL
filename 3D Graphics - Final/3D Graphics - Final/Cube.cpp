#include "Cube.h"
#include "GameManager.h"
Cube::Cube()
{
}

Cube::~Cube()
{
}

void Cube::Init(float InitxPos, float InityPos, float InitzPos, float InitHeight, float InitLength, float InitWidth, const std::string& InitTexFP)
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

	GLfloat Vertices[192] = {
		//Position						//Normals			//Texture
			// Front
		/* 0 */ -0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, /* 00 */
		/* 1 */ -0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f, /* 01 */
		/* 2 */  0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, /* 02 */
		/* 3 */  0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f, /* 03 */

			// Back
		/* 4 */ -0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f, /* 04 */
		/* 5 */ -0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, /* 05 */
		/* 6 */  0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f, /* 06 */
		/* 7 */  0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, /* 07 */

			// Left
		/* 4 */ -0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, /* 08 */
		/* 5 */ -0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f, /* 09 */
		/* 1 */ -0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, /* 10 */
		/* 0 */ -0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f, /* 11 */

			// Right
		/* 3 */  0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f, /* 12 */
		/* 2 */  0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, /* 13 */
		/* 6 */  0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f, /* 14 */
		/* 7 */  0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, /* 15 */

			// Top
		/* 4 */ -0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, /* 16 */
		/* 0 */ -0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f, /* 17 */
		/* 3 */  0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, /* 18 */
		/* 7 */  0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f, /* 19 */

			// Bottom
		/* 4 */  -0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f, /* 20 */
		/* 5 */  -0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, /* 21 */
		/* 6 */   0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f, /* 22 */
		/* 7 */   0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, /* 23 */
	};

	UpdateModel();

	VAO.Init();
	VBO.Init(Vertices, sizeof(Vertices), GL_DYNAMIC_DRAW);
	IBO.Init(Indices, sizeof(Indices));
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

void Cube::Render()
{

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//MVP calc
	UpdateModel();
	glm::mat4 MVP = GameManager::GetInstance()->GetCam()->GetPxV() * Model;
	glm::vec3 CameraPosition = GameManager::GetInstance()->GetCam()->getPosition();
	//Bind Shader
	Shad.Bind();
	Shad.setUniformMat4f("u_MVP", MVP);
	Shad.setUniformMat4f("model", Model);
	Shad.setUniform3f("camPos", CameraPosition.x, CameraPosition.y, CameraPosition.z);

	//Set Vertices
	GLfloat HalfWidth = (GLfloat)(Width * 0.5);
	GLfloat HalfHeight = (GLfloat)(Height * 0.5);
	GLfloat HalfLength = (GLfloat)(Length * 0.5);

	GLfloat Vertices[192] = {
		//Position											//Normals				//Texture
		// Front
		/* 0 */ -HalfWidth,  HalfHeight,  HalfLength,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f, /* 00 */
		/* 1 */ -HalfWidth, -HalfHeight,  HalfLength,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f, /* 01 */
		/* 2 */  HalfWidth, -HalfHeight,  HalfLength,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f, /* 02 */
		/* 3 */  HalfWidth,  HalfHeight,  HalfLength,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, /* 03 */

		// Back
		/* 4 */ -HalfWidth,  HalfHeight, -HalfLength,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, /* 04 */
		/* 5 */ -HalfWidth, -HalfHeight, -HalfLength,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f, /* 05 */
		/* 6 */  HalfWidth, -HalfHeight, -HalfLength,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f, /* 06 */
		/* 7 */  HalfWidth,  HalfHeight, -HalfLength,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f, /* 07 */

		// Left
		/* 4 */ -HalfWidth,  HalfHeight, -HalfLength,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f, /* 08 */
		/* 5 */ -HalfWidth, -HalfHeight, -HalfLength,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f, /* 09 */
		/* 1 */ -HalfWidth, -HalfHeight,  HalfLength,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f, /* 10 */
		/* 0 */ -HalfWidth,  HalfHeight,  HalfLength,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, /* 11 */

		// Right
		/* 3 */  HalfWidth,  HalfHeight,  HalfLength,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, /* 12 */
		/* 2 */  HalfWidth, -HalfHeight,  HalfLength,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f, /* 13 */
		/* 6 */  HalfWidth, -HalfHeight, -HalfLength,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f, /* 14 */
		/* 7 */  HalfWidth,  HalfHeight, -HalfLength,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f, /* 15 */

		// Top
		/* 4 */ -HalfWidth,  HalfHeight, -HalfLength,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f, /* 16 */
		/* 0 */ -HalfWidth,  HalfHeight,  HalfLength,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f, /* 17 */
		/* 3 */  HalfWidth,  HalfHeight,  HalfLength,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f, /* 18 */
		/* 7 */  HalfWidth,  HalfHeight, -HalfLength,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, /* 19 */

		// Bottom
		/* 4 */  -HalfWidth, -HalfHeight,  HalfLength,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, /* 20 */
		/* 5 */  -HalfWidth, -HalfHeight, -HalfLength,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f, /* 21 */
		/* 6 */   HalfWidth, -HalfHeight, -HalfLength,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f, /* 22 */
		/* 7 */   HalfWidth, -HalfHeight,  HalfLength,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f, /* 23 */
	};

	VAO.Bind();
	VBO.Bind();
	VBO.BufferSubData(Vertices, sizeof(Vertices));
	IBO.Bind();
	Shad.Bind();
	Tex.Bind(GL_TEXTURE_2D);

	GLCall(glDrawElements(GL_TRIANGLES, IBO.GetCount(), GL_UNSIGNED_INT, nullptr));

	VAO.Unbind();
	VBO.UnBind();
	IBO.UnBind();

	glDisable(GL_BLEND);
}

void Cube::UpdateModel()
{

	glm::vec3 RotationAxisZ = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::mat4 Rotation = glm::rotate(glm::mat4(), glm::radians(Dir), RotationAxisZ);


	Model = (glm::translate(glm::mat4(1.0f), glm::vec3(xPos + Width * 0.5, yPos + Height * 0.5, zPos))) * Rotation;

}
