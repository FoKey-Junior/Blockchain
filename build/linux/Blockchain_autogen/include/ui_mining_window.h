/********************************************************************************
** Form generated from reading UI file 'mining_window.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINING_WINDOW_H
#define UI_MINING_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MiningWindow
{
public:
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MiningWindow)
    {
        if (MiningWindow->objectName().isEmpty())
            MiningWindow->setObjectName("MiningWindow");
        MiningWindow->resize(800, 500);
        centralwidget = new QWidget(MiningWindow);
        centralwidget->setObjectName("centralwidget");
        MiningWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MiningWindow);
        statusbar->setObjectName("statusbar");
        MiningWindow->setStatusBar(statusbar);

        retranslateUi(MiningWindow);

        QMetaObject::connectSlotsByName(MiningWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MiningWindow)
    {
        MiningWindow->setWindowTitle(QCoreApplication::translate("MiningWindow", "MiningWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MiningWindow: public Ui_MiningWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINING_WINDOW_H
