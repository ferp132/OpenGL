#pragma once

#include "Renderer.h"
#include "vertexbuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
	GLuint RendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};