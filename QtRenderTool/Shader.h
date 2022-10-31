#pragma once

#include <GL/glew.h>
#include <string>

class Shader
{
public:

	GLuint Program;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void Use();

private:
	void loadShaderCode(const GLchar* shaderPath,std::string& codeString);
};