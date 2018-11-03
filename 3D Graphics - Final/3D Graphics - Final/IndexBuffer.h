#pragma once
#ifndef __INDEXBUFFER_H__
#define __INDEXBUFFER_H__
#include "Dependencies\glew\glew.h"

class IndexBuffer
{
private:
	GLuint RendererID;
	GLuint Count;
public:
	IndexBuffer();
	~IndexBuffer();
	void Init(const GLuint* data, unsigned int InitCount);

	void Bind() const;
	void UnBind() const;

	inline GLuint GetCount() const { return Count; }
};

#endif