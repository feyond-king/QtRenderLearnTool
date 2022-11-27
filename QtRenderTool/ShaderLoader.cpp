#include "ShaderLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>


Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	std::string vertexCode, fragmentCode;
	loadShaderCode(vertexPath, vertexCode);
	loadShaderCode(fragmentPath, fragmentCode);

	SetShaderCodeToProgram(vertexCode, fragmentCode);
}

void Shader::Use()
{
	glUseProgram(this->m_program);
}

void Shader::loadShaderCode(const GLchar* shaderPath, std::string& codeString)
{
	// 1. 从文件路径中获取顶点/片段着色器
	std::ifstream shaderFile;
	// 保证ifstream对象可以抛出异常：
	shaderFile.exceptions(std::ifstream::badbit);
	try
	{
		// 打开文件
		shaderFile.open(shaderPath);
		std::stringstream shaderStream;
		// 读取文件的缓冲内容到流中
		shaderStream << shaderFile.rdbuf();
		// 关闭文件
		shaderFile.close();
		// 转换流至GLchar数组
		codeString = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
}

void Shader::SetShaderCodeToProgram(std::string vertexCode, std::string fragmentCode)
{
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	if (nullptr == vShaderCode || nullptr == fShaderCode)
	{
		std::cout << "Shader::SetShaderCodeToProgram: ShaderCode is null" << std::endl;
		return;
	}

	// 2. 编译着色器
	GLint success;
	GLchar infoLog[512];

	// 顶点着色器
	GLuint vertex;
	CREATE_SHADER(vertex, vShaderCode, GL_VERTEX_SHADER, VERTEX);

	// 片段着色器也类似
	GLuint fragmentShader;
	CREATE_SHADER(fragmentShader, fShaderCode, GL_FRAGMENT_SHADER, FRAGMENT);

	// 着色器程序
	if (GL_TRUE == glIsProgram(m_program))
	{
		glDeleteProgram(m_program);
	}
	this->m_program = glCreateProgram();
	glAttachShader(this->m_program, vertex);
	glAttachShader(this->m_program, fragmentShader);
	glLinkProgram(this->m_program);
	// 打印连接错误（如果有的话）
	glGetProgramiv(this->m_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->m_program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
	glDeleteShader(vertex);
	glDeleteShader(fragmentShader);
}

