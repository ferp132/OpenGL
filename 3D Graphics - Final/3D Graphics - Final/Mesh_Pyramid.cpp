#include "Mesh_Pyramid.h"

PyramidMesh::PyramidMesh(const std::string & TextureFP, const std::string & ShaderFP)
	: Mesh(TextureFP, ShaderFP) 
{
	GLfloat Vertices[40] = {
		//Position				//Normals				//Texture
		-1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f, // 0
		-1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f, // 1
		1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f, // 2
		1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, // 3

		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,		0.5f, 0.5f, // 4, Top Point
	};

	GLuint Indices[18] = {
		1, 4, 0,	//First Triangle
		0, 4, 3,	//Second Triangle
		3, 4, 2,
		2, 4, 1,

		1, 0, 3,
		1, 3, 2,
	};

	VAO.Init();
	VBO.Init(Vertices, sizeof(Vertices), GL_DYNAMIC_DRAW);
	IBO.Init(Indices, 18);
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

PyramidMesh::~PyramidMesh()
{
}
