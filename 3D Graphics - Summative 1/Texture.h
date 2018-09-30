#pragma once
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Renderer.h"
#include <string>
class Texture
{
private:
	GLuint TextureID;
	std::string FilePath;
	unsigned char* LocalBuffer;


	int TexWidth;
	int TexHeight;
	int TexSlot;
	int TexChannels;

public: 
	Texture();
	~Texture();

	void Init(const std::string& InitFilePath);

	void Bind();
	void Unbind();

	int GetWidth();
	int GetHeight();
	int GetSlot();
	int GetChannels();

	void SetWidth(int NewWidth);
	void SetHeight(int NewHeight);
	void SetSlot(int NewSlot);
	void SetChannels(int NewChannels);
};

#endif // !__TEXTURE_H__