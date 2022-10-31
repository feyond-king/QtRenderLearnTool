#version 330 core
layout (location = 0) in vec3 position; // λ�ñ���������λ��ֵΪ 0 

uniform mat4 model;
uniform mat4 view;
uniform mat4 perspect;

out vec3 ourColor; // ��Ƭ����ɫ�����һ����ɫ

void main()
{
    gl_Position = perspect * view * model * vec4(position, 1.0);
    ourColor = vec3(1.f,1.f,0.f); // ��ourColor����Ϊ���ǴӶ�����������õ���������ɫ
}