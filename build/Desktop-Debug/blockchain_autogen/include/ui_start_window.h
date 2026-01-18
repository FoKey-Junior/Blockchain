/********************************************************************************
** Form generated from reading UI file 'start_window.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_START_WINDOW_H
#define UI_START_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_6;
    QTextBrowser *textBrowser;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_18;
    QPushButton *participant;
    QSpacerItem *horizontalSpacer;
    QPushButton *miner;

    void setupUi(QMainWindow *StartWindow)
    {
        if (StartWindow->objectName().isEmpty())
            StartWindow->setObjectName("StartWindow");
        StartWindow->resize(800, 500);
        centralwidget = new QWidget(StartWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(800, 500));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 0, 801, 501));
        verticalLayout_6 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(15, 15, 15, 15);
        textBrowser = new QTextBrowser(verticalLayoutWidget);
        textBrowser->setObjectName("textBrowser");

        verticalLayout_6->addWidget(textBrowser);

        verticalSpacer = new QSpacerItem(20, 15, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_6->addItem(verticalSpacer);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName("horizontalLayout_18");
        participant = new QPushButton(verticalLayoutWidget);
        participant->setObjectName("participant");
        participant->setMinimumSize(QSize(0, 45));

        horizontalLayout_18->addWidget(participant);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer);

        miner = new QPushButton(verticalLayoutWidget);
        miner->setObjectName("miner");
        miner->setMinimumSize(QSize(0, 45));
        miner->setSizeIncrement(QSize(0, 7));
        miner->setMouseTracking(false);

        horizontalLayout_18->addWidget(miner);


        verticalLayout_6->addLayout(horizontalLayout_18);

        StartWindow->setCentralWidget(centralwidget);

        retranslateUi(StartWindow);

        QMetaObject::connectSlotsByName(StartWindow);
    } // setupUi

    void retranslateUi(QMainWindow *StartWindow)
    {
        StartWindow->setWindowTitle(QCoreApplication::translate("StartWindow", "StartWindow", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("StartWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">\320\224\320\276\320\261\321\200\320\276 \320\277\320\276\320\266\320\260\320\273\320\276\320\262\320\260\321\202\321\214 \320\262 \321\201\320\270\321\201\321\202\320\265\320\274\321\203 \321\200\320\260\321\201\320\277\321\200\320\265\320\264\320\265\320\273\321\221\320\275\320\275\320\276\320\263\320\276 \321\205\321\200\320\260\320\275\320\265\320\275"
                        "\320\270\321\217 \320\270 \320\276\320\261\321\200\320\260\320\261\320\276\321\202\320\272\320\270 \320\264\320\260\320\275\320\275\321\213\321\205 \320\275\320\260 \320\276\321\201\320\275\320\276\320\262\320\265 \320\261\320\273\320\276\320\272\321\207\320\265\320\271\320\275-\321\202\320\265\321\205\320\275\320\276\320\273\320\276\320\263\320\270\320\271</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\237\321\200\320\276\320\265\320\272\321\202 \321\201\320\276\320\267\320\264\320\260\320\275 \320\264\320\273\321\217 \320\276\320\261\320\265\321\201\320\277\320\265\321\207\320\265\320\275\320\270\321\217 <span style=\" font-weight:700;\">\320\275\320\260\320\264\321\221\320\266\320\275\320\276\320\263\320\276, \320\267\320\260\321\211\320\270\321\211\321\221\320\275\320\275\320\276\320\263\320\276 \320\270 \320\277\321\200\320\276\320\267\321\200\320\260\321\207\320\275\320\276\320\263\320\276 \320\276\320\261\320"
                        "\274\320\265\320\275\320\260 \320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\320\265\320\271</span> \320\262 \320\264\320\265\321\206\320\265\320\275\321\202\321\200\320\260\320\273\320\270\320\267\320\276\320\262\320\260\320\275\320\275\320\276\320\271 \321\201\320\265\321\202\320\270. \320\224\320\260\320\275\320\275\321\213\320\265 \320\272\321\200\320\270\320\277\321\202\320\276\320\263\321\200\320\260\321\204\320\270\321\207\320\265\321\201\320\272\320\270 \320\267\320\260\321\211\320\270\321\211\320\265\320\275\321\213, \320\260 \320\262\321\201\320\265 \320\276\320\277\320\265\321\200\320\260\321\206\320\270\320\270 \320\272\320\276\320\275\321\202\321\200\320\276\320\273\320\270\321\200\321\203\321\216\321\202\321\201\321\217 \320\277\321\200\320\276\321\202\320\276\320\272\320\276\320\273\320\260\320\274\320\270 \320\272\320\276\320\275\321\201\320\265\320\275\321\201\321\203\321\201\320\260</p>\n"
"<h3 style=\" margin-top:14px; margin-bottom:12px; margin-left:0px; margin-righ"
                        "t:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:large; font-weight:700;\">\320\232\320\273\321\216\321\207\320\265\320\262\321\213\320\265 \320\277\321\200\320\265\320\270\320\274\321\203\321\211\320\265\321\201\321\202\320\262\320\260</span></h3>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\">\n"
"<li style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">\320\235\320\260\320\264\321\221\320\266\320\275\320\276\321\201\321\202\321\214 \320\270 \320\261\320\265\320\267\320\276\320\277\320\260\321\201\320\275\320\276\321\201\321\202\321\214 \320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\320\270</span></li>\n"
"<li style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">\320\237\321\200\320\276\320\267\321\200"
                        "\320\260\321\207\320\275\320\276\321\201\321\202\321\214 \320\262\321\201\320\265\321\205 \320\276\320\277\320\265\321\200\320\260\321\206\320\270\320\271</span></li>\n"
"<li style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">\320\243\321\201\321\202\320\276\320\271\321\207\320\270\320\262\320\276\321\201\321\202\321\214 \320\272 \321\201\320\261\320\276\321\217\320\274 \320\270 \320\276\321\202\320\272\320\260\320\267\320\260\320\274 \321\203\320\267\320\273\320\276\320\262</span></li>\n"
"<li style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">\320\255\321\204\321\204\320\265\320\272\321\202\320\270\320\262\320\275\320\276\320\265 \321\203\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\270 \320\274\320\260\321\201\321\210\321\202\320\260\320\261\320\270\321\200\320\276\320\262\320"
                        "\260\320\275\320\270\320\265 \321\201\320\265\321\202\320\270</span></li>\n"
"<li style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">\320\223\320\270\320\261\320\272\320\260\321\217 \320\270\320\275\321\202\320\265\320\263\321\200\320\260\321\206\320\270\321\217 \321\201 \321\201\321\203\321\211\320\265\321\201\321\202\320\262\321\203\321\216\321\211\320\270\320\274\320\270 \321\201\320\270\321\201\321\202\320\265\320\274\320\260\320\274\320\270</span></li></ul>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\237\320\276\320\266\320\260\320\273\321\203\320\271\321\201\321\202\320\260, \320\276\320\277\321\200\320\265\320\264\320\265\320\273\320\270\321\202\320\265 <span style=\" font-weight:700;\">\321\201\320\262\320\276\321\216 \321\200\320\276\320\273\321\214 \320\262 \321\201\320\265\321\202\320\270</span></p>\n"
"<ol styl"
                        "e=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\">\n"
"<li style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">\320\243\321\207\320\260\321\201\321\202\320\275\320\270\320\272 (Node Participant)</span> \342\200\224 \320\277\321\200\320\276\320\262\320\265\321\200\321\217\320\265\321\202 \320\270 \321\205\321\200\320\260\320\275\320\270\321\202 \320\264\320\260\320\275\320\275\321\213\320\265</li>\n"
"<li style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">\320\241\320\276\320\267\320\264\320\260\321\202\320\265\320\273\321\214 \320\275\320\276\320\264\321\213 (Node Creator)</span> \342\200\224 \321\200\320\260\320\267\320\262\321\221\321\200\321\202\321\213\320\262\320\260\320\265\321\202 \320\270 \321\203\320\277\321\200\320\260\320\262\320\273\321\217\320\265"
                        "\321\202 \320\275\320\276\320\264\320\276\320\271</li></ol>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \321\200\320\276\320\273\321\214 \320\264\320\273\321\217 \320\277\321\200\320\276\320\264\320\276\320\273\320\266\320\265\320\275\320\270\321\217 \321\200\320\260\320\261\320\276\321\202\321\213 \321\201 \321\201\320\270\321\201\321\202\320\265\320\274\320\276\320\271</span></p></body></html>", nullptr));
        participant->setText(QCoreApplication::translate("StartWindow", "\320\243\321\207\320\260\321\201\321\202\320\275\320\270\320\272", nullptr));
        miner->setText(QCoreApplication::translate("StartWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\320\265\320\273\321\214 \320\275\320\276\320\264\321\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartWindow: public Ui_StartWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_START_WINDOW_H
