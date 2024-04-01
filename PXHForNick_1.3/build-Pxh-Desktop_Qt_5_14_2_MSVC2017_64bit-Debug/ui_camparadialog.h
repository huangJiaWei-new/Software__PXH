/********************************************************************************
** Form generated from reading UI file 'camparadialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMPARADIALOG_H
#define UI_CAMPARADIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_CamParaDialog
{
public:
    QLabel *lExposure;
    QCheckBox *cbSoftTrigger;
    QPushButton *bnClose;
    QRadioButton *bnTriggerMode;
    QLabel *lGain;
    QLabel *lFrameRate;
    QComboBox *ComboDevices;
    QPushButton *bnGetParam;
    QPushButton *bnStart;
    QLineEdit *tbGain;
    QPushButton *bnTriggerExec;
    QLineEdit *tbExposure;
    QPushButton *bnStop;
    QPushButton *bnSetParam;
    QPushButton *bnEnum;
    QRadioButton *bnContinuesMode;
    QLineEdit *tbFrameRate;
    QPushButton *bnOpen;
    QLineEdit *tbExposure_2;
    QLineEdit *tbGain_2;
    QLineEdit *tbFrameRate_2;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *CamParaDialog)
    {
        if (CamParaDialog->objectName().isEmpty())
            CamParaDialog->setObjectName(QString::fromUtf8("CamParaDialog"));
        CamParaDialog->resize(1441, 1018);
        lExposure = new QLabel(CamParaDialog);
        lExposure->setObjectName(QString::fromUtf8("lExposure"));
        lExposure->setGeometry(QRect(1080, 399, 54, 31));
        cbSoftTrigger = new QCheckBox(CamParaDialog);
        cbSoftTrigger->setObjectName(QString::fromUtf8("cbSoftTrigger"));
        cbSoftTrigger->setEnabled(false);
        cbSoftTrigger->setGeometry(QRect(1080, 330, 111, 21));
        bnClose = new QPushButton(CamParaDialog);
        bnClose->setObjectName(QString::fromUtf8("bnClose"));
        bnClose->setEnabled(false);
        bnClose->setGeometry(QRect(1200, 150, 101, 41));
        bnTriggerMode = new QRadioButton(CamParaDialog);
        bnTriggerMode->setObjectName(QString::fromUtf8("bnTriggerMode"));
        bnTriggerMode->setEnabled(false);
        bnTriggerMode->setGeometry(QRect(1210, 210, 111, 21));
        lGain = new QLabel(CamParaDialog);
        lGain->setObjectName(QString::fromUtf8("lGain"));
        lGain->setGeometry(QRect(1080, 450, 54, 31));
        lFrameRate = new QLabel(CamParaDialog);
        lFrameRate->setObjectName(QString::fromUtf8("lFrameRate"));
        lFrameRate->setGeometry(QRect(1080, 500, 54, 31));
        ComboDevices = new QComboBox(CamParaDialog);
        ComboDevices->setObjectName(QString::fromUtf8("ComboDevices"));
        ComboDevices->setGeometry(QRect(30, 61, 1031, 41));
        bnGetParam = new QPushButton(CamParaDialog);
        bnGetParam->setObjectName(QString::fromUtf8("bnGetParam"));
        bnGetParam->setEnabled(false);
        bnGetParam->setGeometry(QRect(1080, 570, 101, 41));
        bnStart = new QPushButton(CamParaDialog);
        bnStart->setObjectName(QString::fromUtf8("bnStart"));
        bnStart->setEnabled(false);
        bnStart->setGeometry(QRect(1080, 250, 101, 41));
        tbGain = new QLineEdit(CamParaDialog);
        tbGain->setObjectName(QString::fromUtf8("tbGain"));
        tbGain->setEnabled(false);
        tbGain->setGeometry(QRect(1130, 450, 71, 31));
        bnTriggerExec = new QPushButton(CamParaDialog);
        bnTriggerExec->setObjectName(QString::fromUtf8("bnTriggerExec"));
        bnTriggerExec->setEnabled(false);
        bnTriggerExec->setGeometry(QRect(1200, 320, 101, 41));
        tbExposure = new QLineEdit(CamParaDialog);
        tbExposure->setObjectName(QString::fromUtf8("tbExposure"));
        tbExposure->setEnabled(false);
        tbExposure->setGeometry(QRect(1130, 400, 71, 31));
        bnStop = new QPushButton(CamParaDialog);
        bnStop->setObjectName(QString::fromUtf8("bnStop"));
        bnStop->setEnabled(false);
        bnStop->setGeometry(QRect(1200, 250, 101, 41));
        bnSetParam = new QPushButton(CamParaDialog);
        bnSetParam->setObjectName(QString::fromUtf8("bnSetParam"));
        bnSetParam->setEnabled(false);
        bnSetParam->setGeometry(QRect(1200, 570, 101, 41));
        bnEnum = new QPushButton(CamParaDialog);
        bnEnum->setObjectName(QString::fromUtf8("bnEnum"));
        bnEnum->setGeometry(QRect(1080, 60, 221, 41));
        bnContinuesMode = new QRadioButton(CamParaDialog);
        bnContinuesMode->setObjectName(QString::fromUtf8("bnContinuesMode"));
        bnContinuesMode->setEnabled(false);
        bnContinuesMode->setGeometry(QRect(1080, 210, 111, 21));
        tbFrameRate = new QLineEdit(CamParaDialog);
        tbFrameRate->setObjectName(QString::fromUtf8("tbFrameRate"));
        tbFrameRate->setEnabled(false);
        tbFrameRate->setGeometry(QRect(1130, 500, 71, 31));
        bnOpen = new QPushButton(CamParaDialog);
        bnOpen->setObjectName(QString::fromUtf8("bnOpen"));
        bnOpen->setGeometry(QRect(1080, 150, 101, 41));
        tbExposure_2 = new QLineEdit(CamParaDialog);
        tbExposure_2->setObjectName(QString::fromUtf8("tbExposure_2"));
        tbExposure_2->setEnabled(false);
        tbExposure_2->setGeometry(QRect(1220, 400, 71, 31));
        tbGain_2 = new QLineEdit(CamParaDialog);
        tbGain_2->setObjectName(QString::fromUtf8("tbGain_2"));
        tbGain_2->setEnabled(false);
        tbGain_2->setGeometry(QRect(1220, 450, 71, 31));
        tbFrameRate_2 = new QLineEdit(CamParaDialog);
        tbFrameRate_2->setObjectName(QString::fromUtf8("tbFrameRate_2"));
        tbFrameRate_2->setEnabled(false);
        tbFrameRate_2->setGeometry(QRect(1220, 500, 71, 31));
        label = new QLabel(CamParaDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(160, 200, 350, 350));
        label_2 = new QLabel(CamParaDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(599, 199, 350, 350));

        retranslateUi(CamParaDialog);

        QMetaObject::connectSlotsByName(CamParaDialog);
    } // setupUi

    void retranslateUi(QDialog *CamParaDialog)
    {
        CamParaDialog->setWindowTitle(QCoreApplication::translate("CamParaDialog", "Dialog", nullptr));
        lExposure->setText(QCoreApplication::translate("CamParaDialog", "\346\233\235\345\205\211", nullptr));
        cbSoftTrigger->setText(QCoreApplication::translate("CamParaDialog", "\350\275\257\350\247\246\345\217\221", nullptr));
        bnClose->setText(QCoreApplication::translate("CamParaDialog", "\345\205\263\351\227\255\350\256\276\345\244\207", nullptr));
        bnTriggerMode->setText(QCoreApplication::translate("CamParaDialog", "\350\247\246\345\217\221\346\250\241\345\274\217", nullptr));
        lGain->setText(QCoreApplication::translate("CamParaDialog", "\345\242\236\347\233\212", nullptr));
        lFrameRate->setText(QCoreApplication::translate("CamParaDialog", "\345\270\247\347\216\207", nullptr));
        bnGetParam->setText(QCoreApplication::translate("CamParaDialog", "\350\216\267\345\217\226\345\217\202\346\225\260", nullptr));
        bnStart->setText(QCoreApplication::translate("CamParaDialog", "\345\274\200\345\247\213\351\207\207\351\233\206", nullptr));
        bnTriggerExec->setText(QCoreApplication::translate("CamParaDialog", "\350\275\257\350\247\246\345\217\221\344\270\200\346\254\241", nullptr));
        bnStop->setText(QCoreApplication::translate("CamParaDialog", "\345\201\234\346\255\242\351\207\207\351\233\206", nullptr));
        bnSetParam->setText(QCoreApplication::translate("CamParaDialog", "\350\256\276\347\275\256\345\217\202\346\225\260", nullptr));
        bnEnum->setText(QCoreApplication::translate("CamParaDialog", "\346\237\245\346\211\276\350\256\276\345\244\207", nullptr));
        bnContinuesMode->setText(QCoreApplication::translate("CamParaDialog", "\350\277\236\347\273\255\346\250\241\345\274\217", nullptr));
        bnOpen->setText(QCoreApplication::translate("CamParaDialog", "\346\211\223\345\274\200\350\256\276\345\244\207", nullptr));
        label->setText(QString());
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CamParaDialog: public Ui_CamParaDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMPARADIALOG_H
