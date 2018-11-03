#pragma once
#include "Camera.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "Texture.h"

class CubeMap
{
public:
	CubeMap();
	~CubeMap();

	void Init(Camera camera);
	void Update();
	void Render();
	
private:

	GLuint Indices[36] = {
		0, 2, 1,	//Front
		0, 3, 2,	//Front

		7, 5, 6,	//Back
		7, 4, 5,	//Back

		8, 10, 9,	//Left
		8, 11, 10,	//Left

		12, 14, 13,	//Right
		12, 15, 14,	//Right

		16, 18, 17,	//Top
		16, 19, 18,	//Top

		20, 22, 21,	//Bottom
		20, 23, 22,	//Bottom
	};

	VertexArray		   VAO;
	IndexBuffer		   IBO;
	VertexBuffer	   VBO;
	VertexBufferLayout VBLay;
	Shader			   shader;
	Texture			   texture;
	glm::mat4		   MVP;
};