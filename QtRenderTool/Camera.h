#pragma once

// Std. Includes
#include <vector>

// GL Includes
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front{0.f,0.f,-1.f};
    glm::vec3 Up{0.f,1.f,0.f};
    GLfloat m_aspect{ 45. };
    GLfloat m_width{ 0.f };
    GLfloat m_height{ 0.f };
    GLfloat m_near{0.1f};
    GLfloat m_far{100.f};

    Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ)
    {
        this->Position = glm::vec3(posX, posY, posZ);
        this->Up = glm::normalize(glm::vec3(upX, upY, upZ));
        //this->updateCameraVectors();
    }

    // Returns the view matrix calculated using Eular Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
    }

    glm::mat4 GetPerspectiveMatrix()
    {
        return glm::perspective(m_aspect, m_width / m_height, m_near, m_far);
    }
};