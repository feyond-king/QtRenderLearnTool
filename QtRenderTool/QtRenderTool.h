#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtRenderTool.h"

class QtRenderTool : public QWidget
{
    Q_OBJECT

public:
    QtRenderTool(QWidget *parent = nullptr);
    ~QtRenderTool();

private:
    Ui::QtRenderToolClass ui;
};
