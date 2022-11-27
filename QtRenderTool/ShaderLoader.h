#pragma once

#include <GL/glew.h>
#include <string>

#define CREATE_SHADER(glShader,glShaderConde,type,errLogStr)	\
glShader = glCreateShader(type);\
glShaderSource(glShader, 1, &glShaderConde, NULL);\
glCompileShader(glShader);\
glGetShaderiv(glShader, GL_COMPILE_STATUS, &success);\
if (!success)\
{\
	glGetShaderInfoLog(glShader, 512, NULL, infoLog);\
	std::cout << "ERROR::SHADER::" << (#errLogStr) <<"::COMPILATION_FAILED\n" << infoLog << std::endl;\
};\

class Shader
{
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	void SetShaderCodeToProgram(std::string vertexCode, std::string fragmentCode);

	GLuint GetProgram() { return m_program; }

	void Use();

private:
	void loadShaderCode(const GLchar* shaderPath,std::string& codeString);

private:
	GLuint m_program;
};