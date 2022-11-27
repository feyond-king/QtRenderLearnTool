#version 330 core
layout (location = 0) in vec3 position; // 位置变量的属性位置值为 0 
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textcoord;  
layout (location = 3) in vec3 Tangent;  
layout (location = 4) in vec3 BitTangent;  

uniform mat4 model;
uniform mat4 view;
uniform mat4 perspect;

out vec2 outTextCoord; 
out vec3 outNormal; 
out vec3 fragPos;
out vec3 tangent;
out vec3 bitTangent;

void main()
{
    gl_Position = perspect * view * model * vec4(position, 1.0);
 
    outTextCoord = textcoord;
    outNormal = normal;
    fragPos = vec3(gl_Position.x,gl_Position.y,gl_Position.z);

    tangent = Tangent;
    bitTangent = BitTangent;
}