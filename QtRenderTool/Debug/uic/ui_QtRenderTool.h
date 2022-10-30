/********************************************************************************
** Form generated from reading UI file 'QtRenderTool.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTRENDERTOOL_H
#define UI_QTRENDERTOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtRenderToolClass
{
public:

    void setupUi(QWidget *QtRenderToolClass)
    {
        if (QtRenderToolClass->objectName().isEmpty())
            QtRenderToolClass->setObjectName(QString::fromUtf8("QtRenderToolClass"));
        QtRenderToolClass->resize(600, 400);

        retranslateUi(QtRenderToolClass);

        QMetaObject::connectSlotsByName(QtRenderToolClass);
    } // setupUi

    void retranslateUi(QWidget *QtRenderToolClass)
    {
        QtRenderToolClass->setWindowTitle(QApplication::translate("QtRenderToolClass", "QtRenderTool", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtRenderToolClass: public Ui_QtRenderToolClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTRENDERTOOL_H
