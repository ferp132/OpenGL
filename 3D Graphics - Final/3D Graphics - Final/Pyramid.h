#pragma once

#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Renderer.h"
#include "Object.h"

//glm for OpenGL Maths
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"


#include <string>

class Pyramid
{
private:

	
	GLuint Indices[18] = {
		1, 4, 0,	//First Triangle
		0, 4, 3,	//Second Triangle
		3, 4, 2,
		2, 4, 1,

		1, 0, 3,
		1, 3, 2,
	};

	IndexBuffer IBO;
	VertexArray VAO;
	VertexBuffer VBO;
	VertexBufferLayout Lay;
	Shader Shad;
	Texture Tex;

public:

	Pyramid();
	~Pyramid();

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