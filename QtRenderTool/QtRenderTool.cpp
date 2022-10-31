#include "QtRenderTool.h"
#include "Shader.h"
#include <QResizeEvent>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

QtRenderTool::QtRenderTool(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_NoSystemBackground);
    setAutoFillBackground(true);
    _context.setup((HWND)winId(), GetDC((HWND)winId()));

    glewInit();

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

void QtRenderTool::dataPrepare()
{
    m_Shader = std::make_shared<Shader>("./Shader/ShaderVertex.glsl", "./Shader/ShaderFragment.glsl");

    m_Model = std::make_shared<Model>("./Model/spot_triangulated_good.obj");
}

void QtRenderTool::paintEvent(QPaintEvent* evt)
{
}

void QtRenderTool::resizeEvent(QResizeEvent* event)
{
   // glViewport(0, 0, event->size().width(), event->size().height());
}

void QtRenderTool::render()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_Shader->Use();

    glm::mat4 modelMat{1.};
    modelMat = glm::rotate(modelMat, 35.f, glm::vec3(0.0f, 1.f, 0.f));

    glm::mat4 viewMat{1.};
    viewMat = glm::translate(viewMat, glm::vec3(0.f, 0.f, -3.f));
    glm::mat4 perspectMat{1.};
    perspectMat = glm::perspective(45.0f, (float)(this->width() / this->height()), 0.1f, 100.0f);

    //°ó¶¨Êý¾Ý
    glUniformMatrix4fv(glGetUniformLocation(m_Shader.get()->Program,"model"), 1, GL_FALSE, glm::value_ptr(modelMat));
    glUniformMatrix4fv(glGetUniformLocation(m_Shader.get()->Program, "view"), 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(glGetUniformLocation(m_Shader.get()->Program,"perspect"), 1, GL_FALSE, glm::value_ptr(perspectMat));

    m_Model->Draw(*m_Shader.get());

   // glBindVertexArray(VAO);
   // glDrawArrays(GL_TRIANGLES, 0, 3);
    //glBindVertexArray(0);

    _context.swapBuffer();
}