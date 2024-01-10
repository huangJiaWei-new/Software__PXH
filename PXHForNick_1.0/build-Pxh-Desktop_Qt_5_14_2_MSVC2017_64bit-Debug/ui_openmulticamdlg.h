/********************************************************************************
** Form generated from reading UI file 'openmulticamdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENMULTICAMDLG_H
#define UI_OPENMULTICAMDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>
#include <camera/mypicturewidget.h>

QT_BEGIN_NAMESPACE

class Ui_OpenMultiCamDlg
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QComboBox *ComboDevices;
    QWidget *widget;
    QPushButton *bnSetParam;
    QRadioButton *btnContinuesMode;
    QPushButton *btnClose;
    QPushButton *btnStartAqui;
    QPushButton *btnOpenCam;
    QLineEdit *tbExposure_2;
    QPushButton *bnGetParam;
    QPushButton *btnStop;
    QPushButton *btnTriggerExec;
    QLineEdit *tbFrameRate_2;
    QLineEdit *tbGain;
    QLineEdit *tbGain_2;
    QLabel *lExposure;
    QLineEdit *tbExposure;
    QLineEdit *tbFrameRate;
    QLabel *lFrameRate;
    QLabel *lGain;
    QRadioButton *btnTriggerMode;
    QPushButton *btnEnumCam;
    QPushButton *btnSetUpCameraLine;
    QPushButton *btnSetDownCameraLine;
    QPushButton *btnJson;
    QPushButton *btnShowImage;
    MyPictureWidget *widgetPicture1;
    MyPictureWidget *widgetPicture2;
    MyPictureWidget *widgetPicture3;
    MyPictureWidget *widgetPicture4;

    void setupUi(QWidget *OpenMultiCamDlg)
    {
        if (OpenMultiCamDlg->objectName().isEmpty())
            OpenMultiCamDlg->setObjectName(QString::fromUtf8("OpenMultiCamDlg"));
        OpenMultiCamDlg->resize(1368, 927);
        gridLayout = new QGridLayout(OpenMultiCamDlg);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(OpenMultiCamDlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(16777215, 100));
        ComboDevices = new QComboBox(groupBox);
        ComboDevices->setObjectName(QString::fromUtf8("ComboDevices"));
        ComboDevices->setGeometry(QRect(20, 31, 1311, 41));

        gridLayout->addWidget(groupBox, 0, 0, 1, 3);

        widget = new QWidget(OpenMultiCamDlg);
        widget->setObjectName(QString::fromUtf8("widget"));
        bnSetParam = new QPushButton(widget);
        bnSetParam->setObjectName(QString::fromUtf8("bnSetParam"));
        bnSetParam->setEnabled(false);
        bnSetParam->setGeometry(QRect(140, 640, 101, 41));
        btnContinuesMode = new QRadioButton(widget);
        btnContinuesMode->setObjectName(QString::fromUtf8("btnContinuesMode"));
        btnContinuesMode->setEnabled(false);
        btnContinuesMode->setGeometry(QRect(20, 130, 111, 21));
        btnClose = new QPushButton(widget);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setEnabled(false);
        btnClose->setGeometry(QRect(140, 70, 101, 41));
        btnStartAqui = new QPushButton(widget);
        btnStartAqui->setObjectName(QString::fromUtf8("btnStartAqui"));
        btnStartAqui->setEnabled(false);
        btnStartAqui->setGeometry(QRect(20, 170, 101, 41));
        btnOpenCam = new QPushButton(widget);
        btnOpenCam->setObjectName(QString::fromUtf8("btnOpenCam"));
        btnOpenCam->setGeometry(QRect(20, 70, 101, 41));
        tbExposure_2 = new QLineEdit(widget);
        tbExposure_2->setObjectName(QString::fromUtf8("tbExposure_2"));
        tbExposure_2->setEnabled(false);
        tbExposure_2->setGeometry(QRect(160, 470, 71, 31));
        bnGetParam = new QPushButton(widget);
        bnGetParam->setObjectName(QString::fromUtf8("bnGetParam"));
        bnGetParam->setEnabled(false);
        bnGetParam->setGeometry(QRect(20, 640, 101, 41));
        btnStop = new QPushButton(widget);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setEnabled(false);
        btnStop->setGeometry(QRect(140, 170, 101, 41));
        btnTriggerExec = new QPushButton(widget);
        btnTriggerExec->setObjectName(QString::fromUtf8("btnTriggerExec"));
        btnTriggerExec->setEnabled(false);
        btnTriggerExec->setGeometry(QRect(20, 220, 221, 41));
        tbFrameRate_2 = new QLineEdit(widget);
        tbFrameRate_2->setObjectName(QString::fromUtf8("tbFrameRate_2"));
        tbFrameRate_2->setEnabled(false);
        tbFrameRate_2->setGeometry(QRect(160, 570, 71, 31));
        tbGain = new QLineEdit(widget);
        tbGain->setObjectName(QString::fromUtf8("tbGain"));
        tbGain->setEnabled(false);
        tbGain->setGeometry(QRect(70, 520, 71, 31));
        tbGain_2 = new QLineEdit(widget);
        tbGain_2->setObjectName(QString::fromUtf8("tbGain_2"));
        tbGain_2->setEnabled(false);
        tbGain_2->setGeometry(QRect(160, 520, 71, 31));
        lExposure = new QLabel(widget);
        lExposure->setObjectName(QString::fromUtf8("lExposure"));
        lExposure->setGeometry(QRect(20, 469, 54, 31));
        tbExposure = new QLineEdit(widget);
        tbExposure->setObjectName(QString::fromUtf8("tbExposure"));
        tbExposure->setEnabled(false);
        tbExposure->setGeometry(QRect(70, 470, 71, 31));
        tbFrameRate = new QLineEdit(widget);
        tbFrameRate->setObjectName(QString::fromUtf8("tbFrameRate"));
        tbFrameRate->setEnabled(false);
        tbFrameRate->setGeometry(QRect(70, 570, 71, 31));
        lFrameRate = new QLabel(widget);
        lFrameRate->setObjectName(QString::fromUtf8("lFrameRate"));
        lFrameRate->setGeometry(QRect(20, 570, 54, 31));
        lGain = new QLabel(widget);
        lGain->setObjectName(QString::fromUtf8("lGain"));
        lGain->setGeometry(QRect(20, 520, 54, 31));
        btnTriggerMode = new QRadioButton(widget);
        btnTriggerMode->setObjectName(QString::fromUtf8("btnTriggerMode"));
        btnTriggerMode->setEnabled(false);
        btnTriggerMode->setGeometry(QRect(150, 130, 111, 21));
        btnEnumCam = new QPushButton(widget);
        btnEnumCam->setObjectName(QString::fromUtf8("btnEnumCam"));
        btnEnumCam->setGeometry(QRect(20, 10, 221, 41));
        btnSetUpCameraLine = new QPushButton(widget);
        btnSetUpCameraLine->setObjectName(QString::fromUtf8("btnSetUpCameraLine"));
        btnSetUpCameraLine->setEnabled(false);
        btnSetUpCameraLine->setGeometry(QRect(20, 270, 221, 41));
        btnSetDownCameraLine = new QPushButton(widget);
        btnSetDownCameraLine->setObjectName(QString::fromUtf8("btnSetDownCameraLine"));
        btnSetDownCameraLine->setEnabled(false);
        btnSetDownCameraLine->setGeometry(QRect(20, 320, 221, 41));
        btnJson = new QPushButton(widget);
        btnJson->setObjectName(QString::fromUtf8("btnJson"));
        btnJson->setEnabled(false);
        btnJson->setGeometry(QRect(20, 370, 221, 41));
        btnShowImage = new QPushButton(widget);
        btnShowImage->setObjectName(QString::fromUtf8("btnShowImage"));
        btnShowImage->setEnabled(false);
        btnShowImage->setGeometry(QRect(20, 420, 221, 41));

        gridLayout->addWidget(widget, 1, 2, 2, 1);

        widgetPicture1 = new MyPictureWidget(OpenMultiCamDlg);
        widgetPicture1->setObjectName(QString::fromUtf8("widgetPicture1"));
        widgetPicture1->setMaximumSize(QSize(800, 16777215));

        gridLayout->addWidget(widgetPicture1, 1, 0, 1, 1);

        widgetPicture2 = new MyPictureWidget(OpenMultiCamDlg);
        widgetPicture2->setObjectName(QString::fromUtf8("widgetPicture2"));
        widgetPicture2->setMaximumSize(QSize(800, 16777215));

        gridLayout->addWidget(widgetPicture2, 1, 1, 1, 1);

        widgetPicture3 = new MyPictureWidget(OpenMultiCamDlg);
        widgetPicture3->setObjectName(QString::fromUtf8("widgetPicture3"));
        widgetPicture3->setMaximumSize(QSize(800, 16777215));

        gridLayout->addWidget(widgetPicture3, 2, 0, 1, 1);

        widgetPicture4 = new MyPictureWidget(OpenMultiCamDlg);
        widgetPicture4->setObjectName(QString::fromUtf8("widgetPicture4"));
        widgetPicture4->setMaximumSize(QSize(800, 16777215));

        gridLayout->addWidget(widgetPicture4, 2, 1, 1, 1);


        retranslateUi(OpenMultiCamDlg);

        QMetaObject::connectSlotsByName(OpenMultiCamDlg);
    } // setupUi

    void retranslateUi(QWidget *OpenMultiCamDlg)
    {
        OpenMultiCamDlg->setWindowTitle(QCoreApplication::translate("OpenMultiCamDlg", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("OpenMultiCamDlg", "\347\233\270\346\234\272\345\210\227\350\241\250", nullptr));
        bnSetParam->setText(QCoreApplication::translate("OpenMultiCamDlg", "\350\256\276\347\275\256\345\217\202\346\225\260", nullptr));
        btnContinuesMode->setText(QCoreApplication::translate("OpenMultiCamDlg", "\350\277\236\347\273\255\346\250\241\345\274\217", nullptr));
        btnClose->setText(QCoreApplication::translate("OpenMultiCamDlg", "\345\205\263\351\227\255\350\256\276\345\244\207", nullptr));
        btnStartAqui->setText(QCoreApplication::translate("OpenMultiCamDlg", "\345\274\200\345\247\213\351\207\207\351\233\206", nullptr));
        btnOpenCam->setText(QCoreApplication::translate("OpenMultiCamDlg", "\346\211\223\345\274\200\350\256\276\345\244\207", nullptr));
        bnGetParam->setText(QCoreApplication::translate("OpenMultiCamDlg", "\350\216\267\345\217\226\345\217\202\346\225\260", nullptr));
        btnStop->setText(QCoreApplication::translate("OpenMultiCamDlg", "\345\201\234\346\255\242\351\207\207\351\233\206", nullptr));
        btnTriggerExec->setText(QCoreApplication::translate("OpenMultiCamDlg", "\350\275\257\350\247\246\345\217\221\344\270\200\346\254\241", nullptr));
        lExposure->setText(QCoreApplication::translate("OpenMultiCamDlg", "\346\233\235\345\205\211", nullptr));
        lFrameRate->setText(QCoreApplication::translate("OpenMultiCamDlg", "\345\270\247\347\216\207", nullptr));
        lGain->setText(QCoreApplication::translate("OpenMultiCamDlg", "\345\242\236\347\233\212", nullptr));
        btnTriggerMode->setText(QCoreApplication::translate("OpenMultiCamDlg", "\350\247\246\345\217\221\346\250\241\345\274\217", nullptr));
        btnEnumCam->setText(QCoreApplication::translate("OpenMultiCamDlg", "\346\237\245\346\211\276\350\256\276\345\244\207", nullptr));
        btnSetUpCameraLine->setText(QCoreApplication::translate("OpenMultiCamDlg", "\350\256\276\347\275\256\344\273\260\346\234\233\347\233\270\346\234\272\346\240\241\346\255\243\345\217\202\346\225\260", nullptr));
        btnSetDownCameraLine->setText(QCoreApplication::translate("OpenMultiCamDlg", "\350\256\276\347\275\256\344\277\257\350\247\206\347\233\270\346\234\272\346\240\241\346\255\243\345\217\202\346\225\260", nullptr));
        btnJson->setText(QCoreApplication::translate("OpenMultiCamDlg", "\350\247\243\346\236\220json", nullptr));
        btnShowImage->setText(QCoreApplication::translate("OpenMultiCamDlg", "\345\256\236\346\227\266\346\230\276\347\244\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OpenMultiCamDlg: public Ui_OpenMultiCamDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENMULTICAMDLG_H
