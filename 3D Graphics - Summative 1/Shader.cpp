#include "Shader.h"

Shader::Shader()
{
	RendererID = 0;
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(RendererID));
}

void Shader::Init(const std::string& InitFilepath)
{
	Filepath = InitFilepath;
	ShaderProgramSource source = ParseShader(Filepath);
	RendererID = CreateShader(source.VertexSource, source.FragmentSource);
	Bind();

}

void Shader::Bind() const
{

	GLCall(glUseProgram(RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::setUniform1i(const std::string & name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::setUniformMat4f(const std::string & name, const glm::mat4 & Matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &Matrix[0][0]));
}

void Shader::setUniform4f(const std::string & name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniform3f(const std::string & name, float v0, float v1, float v2)
{
	GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

GLuint Shader::CompileShader(GLuint type, const std::string& source)
{
	GLuint id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << endl;
		cout << message << endl;
		return 0;

	}
	return id;
}

GLuint Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLuint Program = glCreateProgram();
	GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(Program, vs);
	glAttachShader(Program, fs);
	glLinkProgram(Program);
	glValidateProgram(Program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return Program;
}

int Shader::GetUniformLocation(const std::string & name)
{
	if (UniformLocationCache.find(name) != UniformLocationCache.end())
		return UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(RendererID, name.c_str()));
	if (location == -1)
		cout << "Warning: uniform: " << name << " doesnt exist" << endl;

		UniformLocationCache[name] = location;
	return location;
}
