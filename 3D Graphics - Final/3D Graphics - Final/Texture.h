#pragma once
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <iostream>
#include <string>
#include <vector>

#include "Dependencies\glew\glew.h"

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
	void InitCubeMap();

	void Bind(unsigned int Type);
	void Unbind(unsigned int Type);

	int GetWidth();
	int GetHeight();
	int GetSlot();
	int GetChannels();
	GLuint GetID() { return TextureID; }

	void SetWidth(int NewWidth);
	void SetHeight(int NewHeight);
	void SetSlot(int NewSlot);
	void SetChannels(int NewChannels);
};

#endif // !__TEXTURE_H__