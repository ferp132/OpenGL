#include "CubeMap.h"
#include "GameManager.h"

CubeMap::CubeMap()
{
}

CubeMap::~CubeMap()
{
}

void CubeMap::Init(Camera camera)
{
	GLfloat Vertices[72] = {
		//Position						
		// Front
		/* 0 */ -0.5f,  0.5f,  0.5f, /* 00 */
		/* 1 */ -0.5f, -0.5f,  0.5f, /* 01 */
		/* 2 */  0.5f, -0.5f,  0.5f, /* 02 */
		/* 3 */  0.5f,  0.5f,  0.5f, /* 03 */

		// Back
		/* 4 */ -0.5f,  0.5f, -0.5f, /* 04 */
		/* 5 */ -0.5f, -0.5f, -0.5f, /* 05 */
		/* 6 */  0.5f, -0.5f, -0.5f, /* 06 */
		/* 7 */  0.5f,  0.5f, -0.5f, /* 07 */

		// Left
		/* 4 */ -0.5f,  0.5f, -0.5f, /* 08 */
		/* 5 */ -0.5f, -0.5f, -0.5f, /* 09 */
		/* 1 */ -0.5f, -0.5f,  0.5f, /* 10 */
		/* 0 */ -0.5f,  0.5f,  0.5f, /* 11 */

		// Right
		/* 3 */  0.5f,  0.5f,  0.5f, /* 12 */
		/* 2 */  0.5f, -0.5f,  0.5f, /* 13 */
		/* 6 */  0.5f, -0.5f, -0.5f, /* 14 */
		/* 7 */  0.5f,  0.5f, -0.5f, /* 15 */

		// Top
		/* 4 */ -0.5f,  0.5f, -0.5f, /* 16 */
		/* 0 */ -0.5f,  0.5f,  0.5f, /* 17 */
		/* 3 */  0.5f,  0.5f,  0.5f, /* 18 */
		/* 7 */  0.5f,  0.5f, -0.5f, /* 19 */

		// Bottom
		/* 4 */  -0.5f, -0.5f,  0.5f, /* 20 */
		/* 5 */  -0.5f, -0.5f, -0.5f, /* 21 */
		/* 6 */   0.5f, -0.5f, -0.5f, /* 22 */
		/* 7 */   0.5f, -0.5f,  0.5f, /* 23 */
	};

	VAO.Init();
	VBO.Init(Vertices, sizeof(Vertices), GL_DYNAMIC_DRAW);
	IBO.Init(Indices, 36);
	VBLay.Push<float>(3);
	VAO.AddBuffer(VBO, VBLay);

	texture.InitCubeMap();

	shader.Init("Resources/Shaders/CubeMap.shader");
	shader.Bind();
	shader.setUniform1i("cubeSampler", 0);						//Set Texture Uniform
	shader.Unbind();

	Update();
}

void CubeMap::Update()
{
	glm::mat4 model = glm::scale(glm::mat4(), glm::vec3(2000.0f, 2000.0f, 2000.0f));
	MVP = GameManager::GetInstance()->GetCam()->GetPxV() * model;
}

void CubeMap::Render()
{

	glEnable(GL_CULL_FACE);
	
	VAO.Bind();
	VBO.Bind();
	IBO.Bind();
	shader.Bind();
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	texture.Bind(GL_TEXTURE_CUBE_MAP);
	
	shader.setUniform1i("cubeSampler", 0);
	shader.setUniformMat4f("MVP", MVP);
	
	
	GLCall(glDrawElements(GL_TRIANGLES, IBO.GetCount(), GL_UNSIGNED_INT, nullptr));

	VAO.Unbind();
	VBO.UnBind();
	IBO.UnBind();

	glDisable(GL_CULL_FACE);
}
