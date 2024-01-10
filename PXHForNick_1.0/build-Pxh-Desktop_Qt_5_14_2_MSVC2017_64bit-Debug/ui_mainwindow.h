/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *widget;
    QPushButton *btnCamPara;
    QPushButton *btnFindCenter;
    QPushButton *btnSerialPort;
    QPushButton *btnCalibration;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        action = new QAction(MainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        QFont font;
        font.setPointSize(12);
        action->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(1, 1, 1, 1);
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setMinimumSize(QSize(0, 200));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        stackedWidget->addWidget(page);

        gridLayout->addWidget(stackedWidget, 1, 0, 1, 1);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 105));
        btnCamPara = new QPushButton(widget);
        btnCamPara->setObjectName(QString::fromUtf8("btnCamPara"));
        btnCamPara->setGeometry(QRect(10, 0, 100, 100));
        btnCamPara->setMinimumSize(QSize(0, 0));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Agency FB"));
        font1.setPointSize(12);
        btnCamPara->setFont(font1);
        btnFindCenter = new QPushButton(widget);
        btnFindCenter->setObjectName(QString::fromUtf8("btnFindCenter"));
        btnFindCenter->setGeometry(QRect(120, 0, 100, 100));
        btnFindCenter->setMinimumSize(QSize(100, 100));
        btnFindCenter->setFont(font1);
        btnSerialPort = new QPushButton(widget);
        btnSerialPort->setObjectName(QString::fromUtf8("btnSerialPort"));
        btnSerialPort->setGeometry(QRect(230, 0, 100, 100));
        btnSerialPort->setMinimumSize(QSize(100, 100));
        btnSerialPort->setFont(font1);
        btnCalibration = new QPushButton(widget);
        btnCalibration->setObjectName(QString::fromUtf8("btnCalibration"));
        btnCalibration->setGeometry(QRect(340, 0, 100, 100));
        btnCalibration->setMinimumSize(QSize(100, 100));
        btnCalibration->setFont(font1);

        gridLayout->addWidget(widget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(action);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\346\231\272\350\203\275\347\233\270\346\234\272", nullptr));
        action->setText(QCoreApplication::translate("MainWindow", "\347\263\273\347\273\237\346\216\250\345\207\272", nullptr));
        btnCamPara->setText(QString());
        btnFindCenter->setText(QString());
        btnSerialPort->setText(QString());
        btnCalibration->setText(QString());
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
