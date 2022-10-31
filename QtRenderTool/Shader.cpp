#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	std::string vertexCode, fragmentCode;
	loadShaderCode(vertexPath, vertexCode);
	loadShaderCode(fragmentPath, fragmentCode);
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	// 2. ������ɫ��
	GLint success;
	GLchar infoLog[512];

	// ������ɫ��
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// ��ӡ�����������еĻ���
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// Ƭ����ɫ��Ҳ����
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);
	// Check for compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// ��ɫ������
	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragmentShader);
	glLinkProgram(this->Program);
	// ��ӡ���Ӵ�������еĻ���
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// ɾ����ɫ���������Ѿ����ӵ����ǵĳ������ˣ��Ѿ�������Ҫ��
	glDeleteShader(vertex);
	glDeleteShader(fragmentShader);
}

void Shader::Use()
{
	glUseProgram(this->Program);
}

void Shader::loadShaderCode(const GLchar* shaderPath, std::string& codeString)
{
	// 1. ���ļ�·���л�ȡ����/Ƭ����ɫ��
	std::ifstream shaderFile;
	// ��֤ifstream��������׳��쳣��
	shaderFile.exceptions(std::ifstream::badbit);
	try
	{
		// ���ļ�
		shaderFile.open(shaderPath);
		std::stringstream shaderStream;
		// ��ȡ�ļ��Ļ������ݵ�����
		shaderStream << shaderFile.rdbuf();
		// �ر��ļ�
		shaderFile.close();
		// ת������GLchar����
		codeString = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
}
