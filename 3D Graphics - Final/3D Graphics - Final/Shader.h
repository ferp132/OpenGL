#pragma once
#ifndef __SHADER_H__
#define __SHADER_H__

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <string>
#include <unordered_map>

//-----glm for OpenGL Maths
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

#include "Dependencies\glew\glew.h"

using namespace std;

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;

};

class Shader
{
private:
	std::string Filepath;
	unsigned int RendererID;
	std::unordered_map<string, int>  UniformLocationCache;

public:
	Shader();
	~Shader();
	void Init(const std::string& InitFilepath);

	void Bind() const;
	void Unbind() const;

	//set uniforms
	void setUniform1i(const std::string& name, int value);
	void setUniformMat4f(const std::string& name, const glm::mat4& Matrix);
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniform3f(const std::string& name, float v0, float v1, float v2);

private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	GLuint CompileShader(GLuint type, const std::string& source);
	GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	int GetUniformLocation(const std::string& name);
};
#endif