#pragma once
#ifndef __VERTEXBUFFER_H__
#define __VERTEXBUFFER_H__

#include "Dependencies\glew\glew.h"

class VertexBuffer
{
private:
	GLuint RendererID;
public:
	VertexBuffer();
	~VertexBuffer();
	void Init(const void* data, unsigned int InitSize, GLenum Usage);

	void BufferSubData(const void* data, unsigned int Size);
	void Bind() const;
	void UnBind() const;
};
#endif