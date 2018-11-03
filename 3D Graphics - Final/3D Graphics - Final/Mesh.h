#pragma once
#include "Dependencies\glew\glew.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include <string>


class Mesh
{
protected:
	//-----Buffers
	IndexBuffer IBO;
	VertexArray VAO;
	VertexBuffer VBO;
	VertexBufferLayout Lay;

	//-----Shader/Texture
	Shader Shad;
	Texture Tex;
public:
	//-----Con/Destructor
	Mesh(const std::string & TextureFP, const std::string & ShaderFP);
	~Mesh();

	void Render(glm::mat4 MVP, glm::mat4 Model, glm::vec3 CamPos);
};