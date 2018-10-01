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

class Object
{
private:

	GLuint Indices[6] = {
		0, 1, 2,	//First Triangle
		2, 3, 0		//Second Triangle
	};

	IndexBuffer IBO;
	VertexArray VAO;
	VertexBuffer VBO;
	VertexBufferLayout Lay;
	Shader Shad;
	Texture Tex;

public:

	Object();
	~Object();

	void Init(float InitxPos, float InityPos, float InitHeight, float InitWidth, const std::string& InitTexFP);
	void Render();

	//-----Update
	void UpdateModel();

	//-----Setters
	void SetxPos	(float Newx) { xPos = Newx; }
	void SetyPos	(float Newy) { yPos = Newy; }
	void SetWidth	(float NewW) { Width = NewW; }
	void SetHeight	(float NewH) { Height = NewH; }

	//Getters
	float GetxPos()   { return xPos; }
	float GetyPos()   { return yPos; }
	float GetWidth()  { return Width; }
	float GetHeight() { return Height; }

	VertexArray* GetVAO() { return &VAO; }
	IndexBuffer* GetIBO() { return &IBO; }
	Shader* GetShader() { return &Shad; }

protected:
	//Transform
	GLfloat Scale;
	glm::mat4 Model;

	float xPos;
	float yPos;
	float Dir;

	float Height;
	float Width;
};