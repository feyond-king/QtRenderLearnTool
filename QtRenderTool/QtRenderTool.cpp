#include "QtRenderTool.h"
#include "ShaderLoader.h"
#include <QResizeEvent>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CommonGLFunc.h"

QtRenderTool::QtRenderTool(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_NoSystemBackground);
    setAutoFillBackground(true);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    _context.setup((HWND)winId(), GetDC((HWND)winId()));

    glewInit();
    glEnable(GL_DEPTH_TEST);

    QObject::connect(&_renderTimer, SIGNAL(timeout()), this, SLOT(render()));
    _renderTimer.setInterval(16);
    _renderTimer.start();

    //glViewport(0, 0, 900 , 600);

    dataPrepare();
}

QtRenderTool::~QtRenderTool()
{
    _context.shutdown();
}

void QtRenderTool::ChangeCamera(int index)
{
    if (index > m_CameraList.size() - 1)
        return;

    m_CurCamera = m_CameraList[index];
}

void QtRenderTool::ChangeShaderCode(std::string vertexShaderCode, std::string fragmentShaderCode)
{
    m_Shader->SetShaderCodeToProgram(vertexShaderCode, fragmentShaderCode);
}

GLuint g_test;
GLuint g_normal_test;

// Generates a texture that is suited for attachments to a framebuffer
GLuint QtRenderTool::generateAttachmentTexture(GLboolean depth, GLboolean stencil)
{
    // What enum to use?
    GLenum attachment_type;
    if (!depth && !stencil)
        attachment_type = GL_RGB;
    else if (depth && !stencil)
        attachment_type = GL_DEPTH_COMPONENT;
    else if (!depth && stencil)
        attachment_type = GL_STENCIL_INDEX;

    //Generate texture ID and load texture data 
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    if (!depth && !stencil)
        glTexImage2D(GL_TEXTURE_2D, 0, attachment_type, this->width(), this->height(), 0, attachment_type, GL_UNSIGNED_BYTE, NULL);
    else // Using both a stencil and depth test, needs special format arguments
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, this->width(), this->height(), 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;
}

void QtRenderTool::dataPrepare()
{
    m_Shader = std::make_shared<Shader>("./Shader/phong.vs", "./Shader/phong.fs");
    m_Model = std::make_shared<Model>("./Model/spot_triangulated_good.obj");
    g_test = GLCOM::textureFromFile("./Model/spot_texture.png", std::string());
    //g_normal_test = GLCOM::textureFromFile("./Model/hmap.png", std::string());
  
    m_CurCamera = std::make_shared<Camera>(0., 0., 3.f, 0., 1.f, 0.);
    m_CurCamera->m_width = this->width();
    m_CurCamera->m_height = this->height();
    m_CameraList.push_back(m_CurCamera);

    {
        auto aCamera = std::make_shared<Camera>(3., 0., 0.f, 0., 1.f, 0.);
        aCamera->m_width = this->width();
        aCamera->m_height = this->height();
        aCamera->Front = glm::vec3(-1.,0,0);
        m_CameraList.push_back(aCamera);
    }

    {
        auto aCamera = std::make_shared<Camera>(0., 5., 0.f, 0., 0.f, -1.f);
        aCamera->m_width = this->width();
        aCamera->m_height = this->height();
        aCamera->Front = glm::vec3(0., -1.f, 0);
        m_CameraList.push_back(aCamera);
    }


    auto light = std::make_shared<Light>();
    light->m_position = glm::vec3(0, 5., 0);
    m_LightList.push_back(light);

    //

    GLuint frameBuffer;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER,frameBuffer);

    GLuint textureColorbuffer = generateAttachmentTexture(false, false);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, this->width(), this->height()); // Use a single renderbuffer object for both a depth AND stencil buffer.
    //glNamedRenderbufferStorage(rbo, GL_RED, this->width(), this->height());//无需绑定
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // Now actually attach it
   
     // Now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void QtRenderTool::paintEvent(QPaintEvent* evt)
{
   // render();
}

void QtRenderTool::resizeEvent(QResizeEvent* event)
{
    glViewport(0, 0, this->width(), this->height());
    m_CurCamera->m_width = this->width();
    m_CurCamera->m_height = this->height();
}

void QtRenderTool::keyPressEvent(QKeyEvent* event)
{
    float cameraSpeed = 0.05f;
    if (event->key() == Qt::Key_A)
    {
        m_CurCamera->Position -= cameraSpeed * glm::normalize( glm::cross(m_CurCamera->Front,m_CurCamera->Up));
    }
    else if (event->key() == Qt::Key_D)
    {
        m_CurCamera->Position += cameraSpeed * glm::normalize(glm::cross(m_CurCamera->Front, m_CurCamera->Up));
    }
    else if (event->key() == Qt::Key_W)
    {
        m_CurCamera->Position += cameraSpeed * m_CurCamera->Front;
    }
    else if (event->key() == Qt::Key_S)
    {
        m_CurCamera->Position -= cameraSpeed * m_CurCamera->Front;
    }
    else if (event->key() == Qt::Key_Space)
    {
        //fit
    }
}

void QtRenderTool::mouseMoveEvent(QMouseEvent* event)
{
    return;
    static bool firstMouse = true;
    static GLfloat lastX, lastY;
    static GLfloat yaw = -90., pitch = 0.;
    if (firstMouse)
    {
        lastX = this->width()*0.5;
        lastY = this->height() * 0.5;
        firstMouse = false;
    }

    GLfloat xoffset = event->pos().x() - lastX;
    GLfloat yoffset = lastY - event->pos().y();
    lastX = event->pos().x();
    lastY = event->pos().y();

    GLfloat sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    m_CurCamera->Front = glm::normalize(front);
}

void QtRenderTool::mousePressEvent(QMouseEvent* event)
{
}

void QtRenderTool::mouseReleaseEvent(QMouseEvent* event)
{
}

void QtRenderTool::wheelEvent(QWheelEvent* event)
{
    GLfloat speed = 0.1f;
    if (event->delta() > 0) //当滚轮向上滑，远离使用者
    {
        m_CurCamera->m_aspect -= speed;
    }
    else //当滚轮向下滑，靠近使用者
    {
        m_CurCamera->m_aspect += speed;
    }
}

void QtRenderTool::render()
{
   // glClearColor(1, 1, 1, 1);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_Shader->Use();

    glm::mat4 modelMat{1.};
    modelMat = glm::rotate(modelMat, 35.f, glm::vec3(0.0f, 1.f, 0.f));
    glm::mat4 viewMat = m_CurCamera->GetViewMatrix();
    glm::mat4 perspectMat = m_CurCamera->GetPerspectiveMatrix();

    //绑定数据
    glUniformMatrix4fv(glGetUniformLocation(m_Shader.get()->GetProgram(),"model"), 1, GL_FALSE, glm::value_ptr(modelMat));
    glUniformMatrix4fv(glGetUniformLocation(m_Shader.get()->GetProgram(), "view"), 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(glGetUniformLocation(m_Shader.get()->GetProgram(),"perspect"), 1, GL_FALSE, glm::value_ptr(perspectMat));

    glUniform3f(glGetUniformLocation(m_Shader.get()->GetProgram(), "cameraPos"), m_CurCamera->Position.x, m_CurCamera->Position.y, m_CurCamera->Position.z);
    if (!m_LightList.empty())
    {
        auto& light = m_LightList[0];
        glUniform3f(glGetUniformLocation(m_Shader.get()->GetProgram(), "lightPos"), light->m_position.x, light->m_position.y, light->m_position.z);
        glUniform3f(glGetUniformLocation(m_Shader.get()->GetProgram(), "lightambient"), light->ambient.x, light->ambient.y, light->ambient.z);
        glUniform3f(glGetUniformLocation(m_Shader.get()->GetProgram(), "lightdiffuse"), light->diffuse.x, light->diffuse.y, light->diffuse.z);
        glUniform3f(glGetUniformLocation(m_Shader.get()->GetProgram(), "lightspecular"), light->specular.x, light->specular.y, light->specular.z);
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, g_test);
    glUniform1i(glGetUniformLocation(m_Shader.get()->GetProgram(), "texture1"), 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, g_normal_test);
    glUniform1i(glGetUniformLocation(m_Shader.get()->GetProgram(), "texture2"), 1);

    m_Model->Draw(*m_Shader.get());
   // glBindVertexArray(VAO);
   // glDrawArrays(GL_TRIANGLES, 0, 3);
    //glBindVertexArray(0);

    _context.swapBuffer();
}