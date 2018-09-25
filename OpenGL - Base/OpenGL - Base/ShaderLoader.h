#pragma once

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>
#include <map>


class ShaderLoader
{
	private:
		std::string ReadShader(char *filename);
		GLuint CreateShader(GLenum shaderType,
			std::string source,
			char* shaderName);

		std::map<char*, GLuint> FragmentShadersMap;
		std::map<char*, GLuint> VertexShadersMap;
		std::map<char*, GLuint> ProgramsMap;

	public:
		ShaderLoader(void);
		~ShaderLoader(void);
		GLuint CreateProgramOriginal(char* VertexShaderFilename,
			char* FragmentShaderFilename);
		GLuint CreateProgram(char* VertexShaderFilename,
			char* FragmentShaderFilename);

};
