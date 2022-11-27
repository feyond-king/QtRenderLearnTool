#pragma once

#include <QtWidgets/QWidget>
#include <QTimer>
#include <memory>
#include "ui_QtRenderTool.h"
#include "GLContext.h"
#include "ShaderLoader.h"
#include "Camera.h"
#include "ModelLoader.h"
#include "Light.h"

class QtRenderTool : public QWidget
{
    Q_OBJECT
protected:
    GLContext   _context;
    QTimer      _renderTimer;

public:
    QtRenderTool(QWidget *parent = nullptr);
    ~QtRenderTool();

    void ChangeCamera(int index);

    void ChangeShaderCode(std::string vertexShaderCode, std::string fragmentShaderCode);

private:
    void dataPrepare();
    GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil);

protected:
    void    paintEvent(QPaintEvent* evt) override;
    void    resizeEvent(QResizeEvent* event) override;
    QPaintEngine* paintEngine() const override { return NULL; }

    void keyPressEvent(QKeyEvent* event)override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

public Q_SLOTS:
    /**
    *   »æÖÆº¯Êý
    */
    virtual void    render();

private:
    Ui::QtRenderToolClass ui;
    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<Model> m_Model;
    std::shared_ptr<Camera> m_CurCamera;

    std::vector<std::shared_ptr<Camera>> m_CameraList;
    std::vector<std::shared_ptr<Light>> m_LightList;
};
