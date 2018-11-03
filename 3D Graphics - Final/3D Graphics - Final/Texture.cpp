#include "Texture.h"
#include "Dependencies\soil\SOIL.h"
#include "Renderer.h"


Texture::Texture()
{
	LocalBuffer = nullptr;
	TexWidth = 0;
	TexHeight = 0;
	TexSlot = 0;
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &TextureID));
}

void Texture::Init(const std::string& InitFilePath)
{
	FilePath = InitFilePath;
	GLCall(glGenTextures(1, &TextureID));

	Bind(GL_TEXTURE_2D);

	unsigned char* Image = SOIL_load_image(InitFilePath.c_str(), &TexWidth, &TexHeight, &TexChannels, SOIL_LOAD_RGBA);
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TexWidth, TexHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, Image));


	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	SOIL_free_image_data(Image);
	 Unbind(GL_TEXTURE_2D);

}

void Texture::InitCubeMap()
{
	const std::string InitTextureFPs[6] = { "right.png", "left.png", "top.png", "bottom.png", "back.png",  "front.png" };


	GLCall(glGenTextures(1, &TextureID));
	
	
	Bind(GL_TEXTURE_CUBE_MAP);

		for (int i = 0; i < 6; i++)
		{
			std::string fullPathName = "Resources/Textures/CubeMap/";
			fullPathName.append(InitTextureFPs[i]);
			unsigned char* image = SOIL_load_image(		fullPathName.c_str(),
														&TexWidth,
														&TexHeight,
														0,
														SOIL_LOAD_RGBA);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGBA,
				TexWidth,
				TexHeight,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				image);
			SOIL_free_image_data(image);
			
		}

	
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

	GLCall(glGenerateMipmap(GL_TEXTURE_CUBE_MAP));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}



void Texture::Bind(unsigned int Type)
{
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(Type, TextureID));
}

void Texture::Unbind(unsigned int Type)
{
	GLCall(glBindTexture(Type, 0));
}

int Texture::GetWidth()
{
	return TexWidth;
}

int Texture::GetHeight()
{
	return TexHeight;
}

int Texture::GetSlot()
{
	return TexSlot;
}

int Texture::GetChannels()
{
	return TexChannels;
}

void Texture::SetWidth(int NewWidth)
{
	TexWidth = NewWidth;
}

void Texture::SetHeight(int NewHeight)
{
	TexHeight = NewHeight;
}

void Texture::SetSlot(int NewSlot)
{
	TexSlot = NewSlot;
}

void Texture::SetChannels(int NewChannels)
{
	TexChannels = NewChannels;
}
