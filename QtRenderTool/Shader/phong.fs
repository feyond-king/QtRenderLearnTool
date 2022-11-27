#version 330 core

in vec2 outTextCoord; 
in vec3 outNormal; 
in vec3 fragPos;
in vec3 tangent;
in vec3 bitTangent;

out vec4 color;

uniform sampler2D texture1;
uniform sampler2D texture2; //normal texture

uniform vec3 cameraPos;
uniform vec3 lightPos;
uniform vec3 lightambient;
uniform vec3 lightdiffuse;
uniform vec3 lightspecular;

void main()
{
    vec4 textureColor = texture(texture1, outTextCoord);

    vec3 result;
    //Ambient
    float ambientStrength = 0.1f;
    result += lightambient * ambientStrength;


    //mat3 TNB = mat3(tangent, bitTangent, cross(tangent,bitTangent));
    //vec3 normal = texture(texture2, outTextCoord).xyz;
    //normal = normalize(normal*2.f - 1.f);
    //normal = normalize(TNB * normal);
    vec3 normal = normalize(outNormal);

    vec3 lightDir = normalize(lightPos - fragPos);
    //diffuse
    result += lightdiffuse*max(dot(normal, lightDir), 0.0);

    //specular
    //1.phong
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(cameraPos - fragPos);
    //vec3 reflectDir = reflect(-lightDir,normal);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    //result += spec*specularStrength*lightspecular;

    //2.blinn phong
    vec3 halfDir = normalize(viewDir + lightDir);
    float spec = pow(max(dot(halfDir, normal), 0.0), 32);
    result += spec*specularStrength*lightspecular;

    color = vec4(result,1.f) * textureColor;
}