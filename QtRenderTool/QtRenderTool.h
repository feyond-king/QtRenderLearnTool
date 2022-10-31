#pragma once

#include <QtWidgets/QWidget>
#include <QTimer>
#include <memory>
#include "ui_QtRenderTool.h"
#include "GLContext.h"
#include "Shader.h"
#include "ModelLoader.h"

class QtRenderTool : public QWidget
{
    Q_OBJECT
protected:
    GLContext   _context;
    QTimer      _renderTimer;

public:
    QtRenderTool(QWidget *parent = nullptr);
    ~QtRenderTool();

private:
    void dataPrepare();

protected:
    void    paintEvent(QPaintEvent* evt);
    void    resizeEvent(QResizeEvent* event);
    virtual QPaintEngine* paintEngine() const { return NULL; }

public Q_SLOTS:
    /**
    *   »æÖÆº¯Êý
    */
    virtual void    render();

private:
    Ui::QtRenderToolClass ui;
    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<Model> m_Model;
};
