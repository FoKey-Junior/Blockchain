/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabs;
    QWidget *tab_1;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QTextBrowser *line_sender_address;
    QSpacerItem *verticalSpacer_2;
    QLineEdit *line_receiver_address;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *file_selection;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label;
    QSpacerItem *horizontalSpacer_6;
    QFormLayout *formLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer;
    QPushButton *sending_files;
    QSpacerItem *horizontalSpacer_2;
    QWidget *tab_2;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QTextBrowser *blockchain_viewing_1;
    QWidget *tab_3;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_4;
    QTextBrowser *blockchain_viewing_2;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_8;
    QWidget *tab_4;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 500);
        MainWindow->setMinimumSize(QSize(800, 500));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(14);
        MainWindow->setFont(font);
        verticalLayoutWidget = new QWidget(MainWindow);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 0, 801, 501));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(15, 15, 15, 15);
        tabs = new QTabWidget(verticalLayoutWidget);
        tabs->setObjectName("tabs");
        tabs->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        tab_1 = new QWidget();
        tab_1->setObjectName("tab_1");
        verticalLayoutWidget_2 = new QWidget(tab_1);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(0, -10, 771, 461));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(15, 25, 15, 15);
        line_sender_address = new QTextBrowser(verticalLayoutWidget_2);
        line_sender_address->setObjectName("line_sender_address");
        line_sender_address->setMaximumSize(QSize(16777215, 30));

        verticalLayout_2->addWidget(line_sender_address);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);

        line_receiver_address = new QLineEdit(verticalLayoutWidget_2);
        line_receiver_address->setObjectName("line_receiver_address");
        line_receiver_address->setMinimumSize(QSize(0, 45));
        line_receiver_address->setMaximumSize(QSize(16777215, 50));
        line_receiver_address->setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu);
        line_receiver_address->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(line_receiver_address);

        verticalSpacer_3 = new QSpacerItem(20, 25, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_3);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);

        file_selection = new QPushButton(verticalLayoutWidget_2);
        file_selection->setObjectName("file_selection");

        horizontalLayout_8->addWidget(file_selection);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_5);

        label = new QLabel(verticalLayoutWidget_2);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_9->addWidget(label);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_6);


        verticalLayout_2->addLayout(horizontalLayout_9);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");

        verticalLayout_2->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 100, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        sending_files = new QPushButton(verticalLayoutWidget_2);
        sending_files->setObjectName("sending_files");

        horizontalLayout_6->addWidget(sending_files);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_6);

        tabs->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        verticalLayoutWidget_3 = new QWidget(tab_2);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(0, 0, 771, 451));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(15, 15, 20, 15);
        blockchain_viewing_1 = new QTextBrowser(verticalLayoutWidget_3);
        blockchain_viewing_1->setObjectName("blockchain_viewing_1");

        verticalLayout_3->addWidget(blockchain_viewing_1);

        tabs->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        verticalLayoutWidget_4 = new QWidget(tab_3);
        verticalLayoutWidget_4->setObjectName("verticalLayoutWidget_4");
        verticalLayoutWidget_4->setGeometry(QRect(0, 0, 773, 451));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(15, 15, 25, 15);
        blockchain_viewing_2 = new QTextBrowser(verticalLayoutWidget_4);
        blockchain_viewing_2->setObjectName("blockchain_viewing_2");

        verticalLayout_4->addWidget(blockchain_viewing_2);

        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_4);

        label_2 = new QLabel(verticalLayoutWidget_4);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(label_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);

        pushButton_2 = new QPushButton(verticalLayoutWidget_4);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout_2->addWidget(pushButton_2);

        horizontalSpacer_9 = new QSpacerItem(20, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_9);

        pushButton = new QPushButton(verticalLayoutWidget_4);
        pushButton->setObjectName("pushButton");

        horizontalLayout_2->addWidget(pushButton);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_8);


        verticalLayout_4->addLayout(horizontalLayout_2);

        tabs->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        tabs->addTab(tab_4, QString());

        verticalLayout->addWidget(tabs);


        retranslateUi(MainWindow);

        tabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Form", nullptr));
        line_sender_address->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Arial'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'.AppleSystemUIFont'; font-size:13pt;\">\320\222\320\260\321\210 \320\260\320\264\321\200\320\265\321\201: 1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa</span></p></body></html>", nullptr));
        line_receiver_address->setText(QString());
        line_receiver_address->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\260\320\264\321\200\320\265\321\201 \320\277\320\276\320\273\321\203\321\207\320\260\321\202\320\265\320\273\321\217", nullptr));
        file_selection->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \320\262\321\201\320\265 \321\204\320\260\320\271\320\273\321\213, \320\272\320\276\321\202\320\276\321\200\321\213\320\265 \320\262\321\213 \321\205\320\276\321\202\320\270\321\202\320\265 \320\276\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
        label->setText(QString());
        sending_files->setText(QCoreApplication::translate("MainWindow", "\320\276\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
        tabs->setTabText(tabs->indexOf(tab_1), QCoreApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\272\320\260 \321\204\320\260\320\271\320\273\320\260", nullptr));
        blockchain_viewing_1->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Arial'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px;"
                        " margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a"
                        "7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0p"
                        "x; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c"
                        "7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1."
                        "2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -q"
                        "t-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da8"
                        "7ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px;"
                        " margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae823715"
                        "4834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style"
                        "=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; tex"
                        "t-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e"
                        "8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; mar"
                        "gin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   "
                        "-   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; m"
                        "argin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc"
                        "2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026"
                        "</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-bl"
                        "ock-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p></body></html>", nullptr));
        tabs->setTabText(tabs->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\320\225\320\264\320\270\320\275\321\213\320\271 \321\200\320\265\320\265\321\201\321\202\321\200 \321\204\320\260\320\271\320\273\320\276\320\262", nullptr));
        blockchain_viewing_2->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Arial'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px;"
                        " margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a"
                        "7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0p"
                        "x; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c"
                        "7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1."
                        "2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -q"
                        "t-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da8"
                        "7ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px;"
                        " margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae823715"
                        "4834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style"
                        "=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; tex"
                        "t-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e"
                        "8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; mar"
                        "gin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   "
                        "-   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; m"
                        "argin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc"
                        "2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026"
                        "</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-bl"
                        "ock-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">c7efc2ffa6da87ae8237154834d402865e8b60a7   -   c7efc2ffa6da87ae8237154834d402865e8b60a7 00:00 1.1.2026</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        label_2->setText(QString());
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \321\204\320\260\320\271\320\273\321\213 \320\264\320\273\321\217 \320\277\321\200\320\276\320\262\320\265\321\200\320\272\320\270", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214 \320\275\320\260 \320\277\321\200\320\276\320\262\320\265\321\200\320\272\321\203", nullptr));
        tabs->setTabText(tabs->indexOf(tab_3), QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\262\320\265\321\200\320\272\320\260 \320\277\320\276\320\264\320\273\320\270\320\275\320\275\320\276\321\201\321\202\320\270 \321\204\320\260\320\271\320\273\320\260", nullptr));
        tabs->setTabText(tabs->indexOf(tab_4), QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
