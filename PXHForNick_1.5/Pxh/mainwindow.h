#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cmd_def.h"
#include "camera/cmvcamera.h"
#include "camera/cameradialog.h"
#include "findcenter/findrectcenterdlg.h"

#pragma execution_character_set("utf-8") //防止中文乱码

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void resizeEvent(QResizeEvent *event);

private:
    void setBtnIcon();

private slots:
    void on_btnCamPara_clicked();    //打开相机界面
    void on_btnFindCenter_clicked(); //打开寻找中心点界面

private:
    Ui::MainWindow *ui;
    QList<CMvCamera*> listCMvCamera;    //相机变量,传入各个界面
    OpenMultiCamDlg *m_openMultiCamDlg; //相机参数设置界面
    QStringList cmd_list;
    FindRectCenterDlg *m_FindCenterDlg;  //寻找中心点界面
};
#endif // MAINWINDOW_H
