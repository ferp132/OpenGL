#pragma once
#ifndef __TEXTLABEL_H_
#define __TEXTLABEL_H__

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>
#include <string>
#include <iostream>

struct FontChar
{
	GLuint	   TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	GLuint	   Advance;

};

class TextLabel
{
private:
	GLuint GenerateTexture(FT_Face face);

	std::string Text;
	glm::vec3 Color;
	GLfloat Scale;
	glm::vec2 Position;
	glm::vec2 TextSize;

	VertexArray TextVAO;
	VertexBuffer TextVBO;
	VertexBufferLayout TextLayout;

	Shader TextShader;
	glm::mat4 proj;
	std::map<GLchar, FontChar> Characters;

public:
	TextLabel();
	~TextLabel();

	void Init(std::string InitText, std::string InitFont, glm::vec2 InitPos, glm::vec3 InitColor = glm::vec3(1.0f, 1.0f, 1.0f), float InitScale = 1.0f);

	void Render();
	void Update();
	void SetText(std::string NewText) { Text = NewText; }
	void SetColor(glm::vec3 NewColor) { Color = NewColor; }
	void SetScale(GLfloat NewScale) { Scale = NewScale; }
	void SetPosition(glm::vec2 NewPos) { Position = NewPos; }
	glm::vec2 GetTextSize() { return TextSize; }
};
#endif // !__TEXTLABEL_H_
