
#include "TextLabel.h"

GLuint TextLabel::GenerateTexture(FT_Face face)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));


	return texture;
}

TextLabel::TextLabel()
{
}

TextLabel::~TextLabel()
{
}

void TextLabel::Init(std::string InitText, std::string InitFont, glm::vec2 InitPos, glm::vec3 InitColor, float InitScale)
{
	Text = InitText;
	Color = InitColor;
	Scale = InitScale;
	Position = InitPos;

	GLfloat Width = 800.0f;
	GLfloat Height = 800.0f;
	proj = glm::ortho(0.0f, Width, 0.0f, Height);
	TextShader.Init("Resources/Shaders/TextShader.shader");

	FT_Library ft;
	FT_Face face;

	if (FT_Init_FreeType(&ft) != 0)
		cout << "FT_Init Failed!" << endl;

	if (FT_New_Face(ft, "Resources/Fonts/arial.ttf", 0, &face) != 0)
		cout << "Failed To Load Font!" << endl;

	FT_Set_Pixel_Sizes(face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte c = 0; c < 128; c++)
	{

		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "Failed to load Glyph!!" << endl;
			continue;
		}

		GLuint texture = GenerateTexture(face);

		FontChar character = { texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(GLuint)face->glyph->advance.x
		};
		Characters.insert(std::pair<GLchar, FontChar>(c, character));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	TextVAO.Init();
	TextVBO.Init(NULL, sizeof(GLfloat) * 6 * 4, GL_DYNAMIC_DRAW);
	TextLayout.Push<float>(4);

	TextVAO.AddBuffer(TextVBO, TextLayout);

	TextVBO.Bind();
	TextVAO.Bind();
}

void TextLabel::Render()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);

	TextShader.Bind();
	TextShader.setUniform3f("textColor", Color.x, Color.y, Color.z);
	TextShader.setUniformMat4f("proj", proj);
	TextVAO.Bind();

	glm::vec2 textPos = Position;
	for (std::string::const_iterator c = Text.begin(); c != Text.end(); c++)
	{
		FontChar ch = Characters[*c];
		GLfloat xpos = textPos.x + ch.Bearing.x * Scale;
		GLfloat ypos = textPos.y - (ch.Size.y - ch.Bearing.y) * Scale;
		GLfloat w = ch.Size.x * Scale;
		GLfloat h = ch.Size.y * Scale;

		GLfloat vertices[6][4] = {
			{xpos, ypos + h, 0.0, 0.0 }, {xpos, ypos, 0.0, 1.0 }, {xpos + w, ypos, 1.0, 1.0 },
			{xpos, ypos + h, 0.0, 0.0 }, { xpos + w, ypos, 1.0, 1.0 }, { xpos + w, ypos + h, 1.0, 0.0 }
		};

		TextVAO.Bind();
		TextVBO.Bind();
		TextVBO.BufferSubData(vertices, sizeof(vertices));
		TextShader.Bind();

		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		TextShader.setUniform1i("u_tex", 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		textPos.x += (ch.Advance >> 6) * Scale;
	}

		TextShader.Unbind();
		TextVBO.UnBind();
		TextVAO.Unbind();
		glBindTexture(GL_TEXTURE_2D, 0);

		glDisable(GL_CULL_FACE);
		glDisable(GL_BLEND);


}
