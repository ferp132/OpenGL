#pragma once
#ifndef __VERTEXARRAY_H__
#define __VERTEXARRAY_H__
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexBufferLayout;

class VertexArray
{
private:
	GLuint RendererID;
public:
	VertexArray();
	~VertexArray();
	void Init();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};

#endif