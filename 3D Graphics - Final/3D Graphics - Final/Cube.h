#pragma once

#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Renderer.h"

//glm for OpenGL Maths
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"


#include <string>

class Cube
{
private:


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

	IndexBuffer IBO;
	VertexArray VAO;
	VertexBuffer VBO;
	VertexBufferLayout Lay;
	Shader Shad;
	Texture Tex;

public:

	Cube();
	~Cube();

	void Init(float InitxPos, float InityPos, float initzPos, float InitHeight, float InitWidth, float InitLength, const std::string& InitTexFP);
	void Render();

	//-----Update
	void UpdateModel();

	//-----Setters
	void SetxPos(float Newx) { xPos = Newx; }
	void SetyPos(float Newy) { yPos = Newy; }
	void SetzPos(float Newz) { zPos = Newz; }
	void SetWidth(float NewW) { Width = NewW; }
	void SetHeight(float NewH) { Height = NewH; }
	void SetLength(float NewL) { Length = NewL; }

	//Getters
	float GetxPos() { return xPos; }
	float GetyPos() { return yPos; }
	float GetzPos() { return zPos; }
	float GetWidth() { return Width; }
	float GetHeight() { return Height; }
	float GetLength() { return Length; }

	VertexArray* GetVAO() { return &VAO; }
	IndexBuffer* GetIBO() { return &IBO; }
	Shader* GetShader() { return &Shad; }

protected:
	//Transform
	GLfloat Scale;
	glm::mat4 Model;

	float xPos;
	float yPos;
	float zPos;
	float Dir;

	float Height;
	float Width;
	float Length;
};