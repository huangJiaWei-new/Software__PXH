#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cmd_def.h"

#include <QResizeEvent>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->setStyleSheet("QWidget#widget{border-bottom:2px solid grey;}");
    this->showMaximized();

    //清除'listCMvCamera'列表
    if(listCMvCamera.count()>0)
        listCMvCamera.clear();

    //'listCMvCamera'包含'MAX_DEVICE_NUM'个'CMvCamera'类的实例
    for (int i = 0; i < MAX_DEVICE_NUM; i++)
    {       
        listCMvCamera.append(new CMvCamera);
        if (NULL == listCMvCamera[i])
        {
            QMessageBox::information(this,"warnning","camera initial error!");
            return;
        }
    }

    //将'CMvCamera'的实例传给'cameradialog'界面
    m_openMultiCamDlg = new OpenMultiCamDlg(this,listCMvCamera);
    ui->stackedWidget->addWidget(m_openMultiCamDlg); //序号1

    //配置'findrectcenterdlg'界面
    m_FindCenterDlg = new FindRectCenterDlg(this); //查找直线与中心
    ui->stackedWidget->addWidget(m_FindCenterDlg); //序号2

    //切换到'findrectcenterdlg'界面
    connect(m_openMultiCamDlg, SIGNAL(activateFindCenter()),
            this, SLOT(on_btnFindCenter_clicked()));

    //将仰望相机图像传入'findrectcenterdlg'界面
    connect(m_openMultiCamDlg, SIGNAL(sigSendUpImg(cv::Mat,int)),
            m_FindCenterDlg, SLOT(receiveUpImg(cv::Mat,int)));

    //将俯视相机图像传入'findrectcenterdlg'界面
    connect(m_openMultiCamDlg, SIGNAL(sigSendDownImg(cv::Mat,int)),
            m_FindCenterDlg, SLOT(receiveDownImg(cv::Mat,int)));

    setBtnIcon();
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*--------------@brief：为'mainwindow'四个按钮设置图标-------------*/
/*--------------@note： -------------*/
void MainWindow::setBtnIcon()
{
    this->setStyleSheet(
                "QPushButton#btnCamPara"
                "{"
                "border-image: url(:/reImg/cam.jpg);"
                "color:rgb(128,255,255);"
                "}"

                "QPushButton#btnFindCenter"
                "{"
                "border-image: url(:/reImg/kaiguanshezhi.png);"
                "color:rgb(128,255,255);"
                "}"

                "QPushButton#btnSerialPort"
                "{"
                "border-image: url(:/reImg/line_edge.jpg);"
                "color:rgb(128,255,255);"
                "}"

                "QPushButton#btnCalibration"
                "{"
                "border-image: url(:/reImg/set.png);"
                "color:rgb(128,255,255);"
                "}"
                );
}


/*--------------@brief：-------------*/
/*--------------@note： -------------*/
void MainWindow::resizeEvent(QResizeEvent *event)
{


}


/*--------------@brief：点击按钮，打开相机界面-------------*/
/*--------------@note： -------------*/
void MainWindow::on_btnCamPara_clicked()
{
    ui->stackedWidget->setCurrentIndex(INDEX_CAMPARA_SHOW);
}


/*--------------@brief：点击按钮，打开寻找中心点界面-------------*/
/*--------------@note： -------------*/
void MainWindow::on_btnFindCenter_clicked()
{
    ui->stackedWidget->setCurrentIndex(INDEX_FINDCENTER_SHOW);
}


