#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const GLuint* data, unsigned int count)
	:Count(count)
{
	GLCall(glGenBuffers(1, &RendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &RendererID));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, RendererID));
}

void IndexBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
