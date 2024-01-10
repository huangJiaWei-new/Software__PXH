/********************************************************************************
** Form generated from reading UI file 'findrectcenterdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDRECTCENTERDLG_H
#define UI_FINDRECTCENTERDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FindRectCenterDlg
{
public:
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *widgetPicture;
    QLabel *labelTitle;
    QWidget *widget_2;
    QPushButton *btnPreProcess;
    QPushButton *btnExcludeProcess;
    QPushButton *btnSelectProcess;
    QPushButton *btnDrawLeftProcess;
    QPushButton *btnDrawUpProcess;
    QPushButton *btnDrawRightProcess;
    QPushButton *btnDrawBottomProcess;
    QPushButton *btnFitLeftProcess;
    QPushButton *btnFitUpProcess;
    QPushButton *btnFitRightProcess;
    QPushButton *btnFitBottomProcess;
    QPushButton *btnCenterProcess;
    QPushButton *btnJsonProcess;
    QComboBox *comboBox;
    QPushButton *switch1;
    QPushButton *btnUndo;

    void setupUi(QWidget *FindRectCenterDlg)
    {
        if (FindRectCenterDlg->objectName().isEmpty())
            FindRectCenterDlg->setObjectName(QString::fromUtf8("FindRectCenterDlg"));
        FindRectCenterDlg->resize(1117, 520);
        gridLayout = new QGridLayout(FindRectCenterDlg);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        scrollArea = new QScrollArea(FindRectCenterDlg);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1097, 338));
        widgetPicture = new QWidget(scrollAreaWidgetContents);
        widgetPicture->setObjectName(QString::fromUtf8("widgetPicture"));
        widgetPicture->setGeometry(QRect(10, 10, 461, 311));
        widgetPicture->setMinimumSize(QSize(200, 200));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 1, 0, 1, 1);

        labelTitle = new QLabel(FindRectCenterDlg);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        labelTitle->setMinimumSize(QSize(0, 30));
        labelTitle->setMaximumSize(QSize(16777215, 50));

        gridLayout->addWidget(labelTitle, 0, 0, 1, 1);

        widget_2 = new QWidget(FindRectCenterDlg);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setEnabled(true);
        widget_2->setMinimumSize(QSize(1000, 120));
        widget_2->setMaximumSize(QSize(16777215, 100));
        btnPreProcess = new QPushButton(widget_2);
        btnPreProcess->setObjectName(QString::fromUtf8("btnPreProcess"));
        btnPreProcess->setGeometry(QRect(20, 10, 111, 41));
        btnExcludeProcess = new QPushButton(widget_2);
        btnExcludeProcess->setObjectName(QString::fromUtf8("btnExcludeProcess"));
        btnExcludeProcess->setGeometry(QRect(20, 60, 111, 41));
        btnSelectProcess = new QPushButton(widget_2);
        btnSelectProcess->setObjectName(QString::fromUtf8("btnSelectProcess"));
        btnSelectProcess->setGeometry(QRect(160, 10, 111, 41));
        btnDrawLeftProcess = new QPushButton(widget_2);
        btnDrawLeftProcess->setObjectName(QString::fromUtf8("btnDrawLeftProcess"));
        btnDrawLeftProcess->setGeometry(QRect(160, 60, 111, 41));
        btnDrawUpProcess = new QPushButton(widget_2);
        btnDrawUpProcess->setObjectName(QString::fromUtf8("btnDrawUpProcess"));
        btnDrawUpProcess->setGeometry(QRect(290, 60, 111, 41));
        btnDrawRightProcess = new QPushButton(widget_2);
        btnDrawRightProcess->setObjectName(QString::fromUtf8("btnDrawRightProcess"));
        btnDrawRightProcess->setGeometry(QRect(290, 10, 111, 41));
        btnDrawBottomProcess = new QPushButton(widget_2);
        btnDrawBottomProcess->setObjectName(QString::fromUtf8("btnDrawBottomProcess"));
        btnDrawBottomProcess->setGeometry(QRect(430, 10, 111, 41));
        btnFitLeftProcess = new QPushButton(widget_2);
        btnFitLeftProcess->setObjectName(QString::fromUtf8("btnFitLeftProcess"));
        btnFitLeftProcess->setGeometry(QRect(430, 60, 111, 41));
        btnFitUpProcess = new QPushButton(widget_2);
        btnFitUpProcess->setObjectName(QString::fromUtf8("btnFitUpProcess"));
        btnFitUpProcess->setGeometry(QRect(560, 60, 111, 41));
        btnFitRightProcess = new QPushButton(widget_2);
        btnFitRightProcess->setObjectName(QString::fromUtf8("btnFitRightProcess"));
        btnFitRightProcess->setGeometry(QRect(560, 10, 111, 41));
        btnFitBottomProcess = new QPushButton(widget_2);
        btnFitBottomProcess->setObjectName(QString::fromUtf8("btnFitBottomProcess"));
        btnFitBottomProcess->setGeometry(QRect(700, 10, 111, 41));
        btnCenterProcess = new QPushButton(widget_2);
        btnCenterProcess->setObjectName(QString::fromUtf8("btnCenterProcess"));
        btnCenterProcess->setGeometry(QRect(700, 60, 111, 41));
        btnJsonProcess = new QPushButton(widget_2);
        btnJsonProcess->setObjectName(QString::fromUtf8("btnJsonProcess"));
        btnJsonProcess->setGeometry(QRect(830, 10, 111, 41));
        comboBox = new QComboBox(widget_2);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(830, 60, 111, 31));
        switch1 = new QPushButton(widget_2);
        switch1->setObjectName(QString::fromUtf8("switch1"));
        switch1->setGeometry(QRect(960, 10, 111, 41));
        btnUndo = new QPushButton(widget_2);
        btnUndo->setObjectName(QString::fromUtf8("btnUndo"));
        btnUndo->setGeometry(QRect(960, 60, 111, 41));

        gridLayout->addWidget(widget_2, 2, 0, 1, 1);


        retranslateUi(FindRectCenterDlg);

        QMetaObject::connectSlotsByName(FindRectCenterDlg);
    } // setupUi

    void retranslateUi(QWidget *FindRectCenterDlg)
    {
        FindRectCenterDlg->setWindowTitle(QCoreApplication::translate("FindRectCenterDlg", "Form", nullptr));
        labelTitle->setText(QCoreApplication::translate("FindRectCenterDlg", "TextLabel", nullptr));
        btnPreProcess->setText(QCoreApplication::translate("FindRectCenterDlg", "\345\233\276\345\203\217\351\242\204\345\244\204\347\220\206", nullptr));
        btnExcludeProcess->setText(QCoreApplication::translate("FindRectCenterDlg", "\346\267\273\345\212\240\346\216\222\351\231\244\345\214\272\345\237\237", nullptr));
        btnSelectProcess->setText(QCoreApplication::translate("FindRectCenterDlg", "\346\267\273\345\212\240\351\200\211\346\213\251\345\214\272\345\237\237", nullptr));
        btnDrawLeftProcess->setText(QCoreApplication::translate("FindRectCenterDlg", "\347\273\230\345\210\266\345\267\246\350\276\271\347\274\230\347\272\277", nullptr));
        btnDrawUpProcess->setText(QCoreApplication::translate("FindRectCenterDlg", "\347\273\230\345\210\266\344\270\212\350\276\271\347\274\230\347\272\277", nullptr));
        btnDrawRightProcess->setText(QCoreApplication::translate("FindRectCenterDlg", "\347\273\230\345\210\266\345\217\263\350\276\271\347\274\230\347\272\277", nullptr));
        btnDrawBottomProcess->setText(QCoreApplication::translate("FindRectCenterDlg", "\347\273\230\345\210\266\344\270\213\350\276\271\347\274\230\347\272\277", nullptr));
        btnFitLeftProcess->setText(QCoreApplication::translate("FindRectCenterDlg", "\346\213\237\345\220\210\345\267\246\350\276\271\347\274\230\347\272\277", nullptr));
        btnFitUpProcess->setText(QCoreApplication::translate("FindRectCenterDlg", "\346\213\237\345\220\210\344\270\212\350\276\271\347\274\230\347\272\277", nullptr));
        btnFitRightProcess->setText(QCoreApplication::translate("FindRectCenterDlg", "\346\213\237\345\220\210\345\217\263\350\276\271\347\274\230\347\272\277", nullptr));
        btnFitBottomProcess->setText(QCoreApplication::translate("FindRectCenterDlg", "\346\213\237\345\220\210\344\270\213\350\276\271\347\274\230\347\272\277", nullptr));
        btnCenterProcess->setText(QCoreApplication::translate("FindRectCenterDlg", "\344\270\255\345\277\203\347\202\271", nullptr));
        btnJsonProcess->setText(QCoreApplication::translate("FindRectCenterDlg", "\347\224\237\346\210\220json\346\226\207\344\273\266", nullptr));
        switch1->setText(QCoreApplication::translate("FindRectCenterDlg", "\345\210\207\346\215\242", nullptr));
        btnUndo->setText(QCoreApplication::translate("FindRectCenterDlg", "\346\222\244\346\266\210\347\233\264\347\272\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FindRectCenterDlg: public Ui_FindRectCenterDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDRECTCENTERDLG_H
