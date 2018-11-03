#include "VertexArray.h"
#include <iostream>

VertexArray::VertexArray()
{
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &RendererID));
}

void VertexArray::Init()
{
	GLCall(glGenVertexArrays(1, &RendererID));
	GLCall(glBindVertexArray(RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{ 

	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalised , layout.GetStride(), (const GLvoid*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
