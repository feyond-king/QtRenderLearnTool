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

void Shader::SetShaderCodeToProgram(std::string vertexCode, std::string fragmentCode)
{
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	if (nullptr == vShaderCode || nullptr == fShaderCode)
	{
		std::cout << "Shader::SetShaderCodeToProgram: ShaderCode is null" << std::endl;
		return;
	}

	// 2. ������ɫ��
	GLint success;
	GLchar infoLog[512];

	// ������ɫ��
	GLuint vertex;
	CREATE_SHADER(vertex, vShaderCode, GL_VERTEX_SHADER, VERTEX);

	// Ƭ����ɫ��Ҳ����
	GLuint fragmentShader;
	CREATE_SHADER(fragmentShader, fShaderCode, GL_FRAGMENT_SHADER, FRAGMENT);

	// ��ɫ������
	if (GL_TRUE == glIsProgram(m_program))
	{
		glDeleteProgram(m_program);
	}
	this->m_program = glCreateProgram();
	glAttachShader(this->m_program, vertex);
	glAttachShader(this->m_program, fragmentShader);
	glLinkProgram(this->m_program);
	// ��ӡ���Ӵ�������еĻ���
	glGetProgramiv(this->m_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->m_program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// ɾ����ɫ���������Ѿ����ӵ����ǵĳ������ˣ��Ѿ�������Ҫ��
	glDeleteShader(vertex);
	glDeleteShader(fragmentShader);
}

