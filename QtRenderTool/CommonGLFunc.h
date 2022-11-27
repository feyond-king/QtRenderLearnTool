#pragma once
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL.h>
#include <string>

namespace GLCOM
{
    GLuint textureFromFile(const char* path, std::string directory);
};

