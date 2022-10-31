#version 330 core
layout (location = 0) in vec3 position; // 位置变量的属性位置值为 0 

uniform mat4 model;
uniform mat4 view;
uniform mat4 perspect;

out vec3 ourColor; // 向片段着色器输出一个颜色

void main()
{
    gl_Position = perspect * view * model * vec4(position, 1.0);
    ourColor = vec3(1.f,1.f,0.f); // 将ourColor设置为我们从顶点数据那里得到的输入颜色
}