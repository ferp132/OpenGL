#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer()
{
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &RendererID));
}

void VertexBuffer::Init(const void* data, unsigned int InitSize, GLenum Usage)
{
	GLCall(glGenBuffers(1, &RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, InitSize, data, Usage));
}

void VertexBuffer::BufferSubData(const void* data, unsigned int Size)
{
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, Size, data));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, RendererID));
}

void VertexBuffer::UnBind() const 
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
