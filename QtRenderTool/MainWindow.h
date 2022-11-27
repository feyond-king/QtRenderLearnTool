#pragma once

#include <QtWidgets/QWidget>
#include <memory>
#include "ui_MainWindow.h"

class QtRenderTool;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow ui;
    std::shared_ptr<QtRenderTool> m_WidgetRender;
};
