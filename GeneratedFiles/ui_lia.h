/********************************************************************************
** Form generated from reading UI file 'lia.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIA_H
#define UI_LIA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LIAClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LIAClass)
    {
        if (LIAClass->objectName().isEmpty())
            LIAClass->setObjectName(QStringLiteral("LIAClass"));
        LIAClass->resize(600, 400);
        menuBar = new QMenuBar(LIAClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        LIAClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LIAClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        LIAClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(LIAClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        LIAClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(LIAClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        LIAClass->setStatusBar(statusBar);

        retranslateUi(LIAClass);

        QMetaObject::connectSlotsByName(LIAClass);
    } // setupUi

    void retranslateUi(QMainWindow *LIAClass)
    {
        LIAClass->setWindowTitle(QApplication::translate("LIAClass", "LIA", 0));
    } // retranslateUi

};

namespace Ui {
    class LIAClass: public Ui_LIAClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIA_H
