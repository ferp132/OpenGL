#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Renderer.h"

class IndexBuffer
{
private:
	GLuint RendererID;
	GLuint Count;
public:
	IndexBuffer(const GLuint* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	inline GLuint GetCount() const { return Count; }
};