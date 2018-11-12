#pragma once
#ifndef __RENDERER_H__
#define __RENDERER_H__


class VertexArray;
class IndexBuffer;
class Shader;


#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
 x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
private:
	
public:
	void Clear();
	void rDraw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;


};

#endif