#include "MainWindow.h"
#include "QtRenderTool.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    m_WidgetRender = make_shared<QtRenderTool>(this);
    ui.glLayout->addWidget(m_WidgetRender.get());

    connect(ui.camera1, &QPushButton::clicked, this, [&]() { m_WidgetRender->ChangeCamera(0); });
    connect(ui.camera2, &QPushButton::clicked, this, [&]() { m_WidgetRender->ChangeCamera(1); });
    connect(ui.camera3, &QPushButton::clicked, this, [&]() { m_WidgetRender->ChangeCamera(2); });
    
    connect(ui.pb_Enter, &QPushButton::clicked, this, [&]() {
        m_WidgetRender->ChangeShaderCode(ui.text_VShaer->toPlainText().toStdString(), ui.text_FShaer->toPlainText().toStdString());
    });


}

MainWindow::~MainWindow()
{
}

