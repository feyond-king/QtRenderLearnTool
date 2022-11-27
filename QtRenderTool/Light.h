#pragma once
// GL Includes
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Light
{
public:
	glm::vec3 m_position;
	glm::vec3 ambient{1.,1.,1.};
	glm::vec3 diffuse{ 1.,1.,1. };
	glm::vec3 specular{ 1.,1.,1. };
};