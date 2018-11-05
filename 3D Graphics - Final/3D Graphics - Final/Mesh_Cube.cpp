#include "Mesh_Cube.h"
#include "GameManager.h"

CubeMesh::CubeMesh(const std::string & TextureFP, const std::string & ShaderFP)
: Mesh(TextureFP, ShaderFP)
{
	GLfloat Vertices[192] = {
		//Position						//Normals			//Texture
		// Front
		/* 0 */ -1.0f,  1.0f,  1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, /* 00 */
		/* 1 */ -1.0f, -1.0f,  1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f, /* 01 */
		/* 2 */  1.0f, -1.0f,  1.0f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, /* 02 */
		/* 3 */  1.0f,  1.0f,  1.0f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f, /* 03 */

		// Back
		/* 4 */ -1.0f,  1.0f, -1.0f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f, /* 04 */
		/* 5 */ -1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, /* 05 */
		/* 6 */  1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f, /* 06 */
		/* 7 */  1.0f,  1.0f, -1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, /* 07 */

		// Left
		/* 4 */ -1.0f,  1.0f, -1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, /* 08 */
		/* 5 */ -1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f, /* 09 */
		/* 1 */ -1.0f, -1.0f,  1.0f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, /* 10 */
		/* 0 */ -1.0f,  1.0f,  1.0f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f, /* 11 */

		// Right
		/* 3 */  1.0f,  1.0f,  1.0f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f, /* 12 */
		/* 2 */  1.0f, -1.0f,  1.0f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, /* 13 */
		/* 6 */  1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f, /* 14 */
		/* 7 */  1.0f,  1.0f, -1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, /* 15 */

		// Top
		/* 4 */ -1.0f,  1.0f, -1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, /* 16 */
		/* 0 */ -1.0f,  1.0f,  1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f, /* 17 */
		/* 3 */  1.0f,  1.0f,  1.0f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, /* 18 */
		/* 7 */  1.0f,  1.0f, -1.0f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f, /* 19 */

		// Bottom
		/* 4 */  -1.0f, -1.0f,  1.0f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f, /* 20 */
		/* 5 */  -1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, /* 21 */
		/* 6 */   1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f, /* 22 */
		/* 7 */   1.0f, -1.0f,  1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, /* 23 */
	};
	GLuint Indices[36] = {
		0, 1, 2,	//Front
		0, 2, 3,	//Front

		7, 6, 5,	//Back
		7, 5, 4,	//Back

		8, 9,  10,	//Left
		8, 10, 11,	//Left

		12, 13, 14,	//Right
		12, 14, 15,	//Right

		16, 17, 18,	//Top
		16, 18, 19,	//Top

		20, 21, 22,	//Bottom
		20, 22, 23,	//Bottom
	};

	VAO.Init();
	VBO.Init(Vertices, sizeof(Vertices), GL_DYNAMIC_DRAW);
	IBO.Init(Indices, 36);
	Lay.Push<float>(3);		//Vertices
	Lay.Push<float>(3);		//Normals
	Lay.Push<float>(2);		//Texture
	VAO.AddBuffer(VBO, Lay);

	Tex.Bind(GL_TEXTURE_2D);
	Tex.Init(TextureFP);
	Tex.SetSlot(0);

	Shad.Init(ShaderFP);
	Shad.Bind();
	Shad.setUniform1i("u_Texture", 0);						//Set Texture Uniform
	Shad.Unbind();

	if (TextureFP == "Resources/Shaders/Reflection.shader") Reflect = true;
	else Reflect = false;
}

CubeMesh::~CubeMesh()
{
}
