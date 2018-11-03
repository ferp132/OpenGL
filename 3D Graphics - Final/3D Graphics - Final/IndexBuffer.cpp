#include "IndexBuffer.h"
#include "Renderer.h"
#include "Dependencies\glew\glew.h"

IndexBuffer::IndexBuffer()
{
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &RendererID));
}

void IndexBuffer::Init(const GLuint* data, unsigned int InitCount)
{
	Count = InitCount;

	GLCall(glGenBuffers(1, &RendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(GLuint), data, GL_STATIC_DRAW));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, RendererID));
}

void IndexBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
