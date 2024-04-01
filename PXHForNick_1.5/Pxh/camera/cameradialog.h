#ifndef OPENMULTICAMDLG_H
#define OPENMULTICAMDLG_H

#include <QWidget>
#include <QThread>
#include <QTimer>
#include <vector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

#include <qmutex.h>
#include "cmvcamera.h"
#include "cmd_def.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include "findcenter/findrectcenterdlg.h"

#pragma execution_character_set("utf-8") //防止中文乱码

namespace Ui {
class OpenMultiCamDlg;
}

class OpenMultiCamDlg : public QWidget
{
    Q_OBJECT

public:
    OpenMultiCamDlg(QWidget *parent, QList<CMvCamera*> listMyCamera);
    ~OpenMultiCamDlg();

public:

private:
    void showErrorMsg(QString csMessage, long long nErrorNum); //显示相机错误信息
    void setTriggerMode(int nTriggerMode); //设置触发模式
    void setTriggerSource(int nTriggerSource); //设置触发源
    void startCamByQThreadCallBack(); //相机采集函数
    //相机采集回调函数
    void static __stdcall  camCallBack0(unsigned char * pData,
                                        MV_FRAME_OUT_INFO_EX* pFrameInfo,
                                        void* pUser);

    void static __stdcall  camCallBack1(unsigned char * pData,
                                        MV_FRAME_OUT_INFO_EX* pFrameInfo,
                                        void* pUser);

    void static __stdcall  camCallBack2(unsigned char * pData,
                                        MV_FRAME_OUT_INFO_EX* pFrameInfo,
                                        void* pUser);

    void static __stdcall  camCallBack3(unsigned char * pData,
                                        MV_FRAME_OUT_INFO_EX* pFrameInfo,
                                        void* pUser);
    //内部回调函数显示图像
    void camCallBackInner(unsigned char * pData,
                          MV_FRAME_OUT_INFO_EX* pFrameInfo,
                          int camIndex,
                          QString frameCountInfo);

    cv::Mat showUpCameraImage(cv::Mat& UpCameraImage); //实时显示仰望相机图像
    cv::Mat showDownCameraImage(cv::Mat& DownCameraImage); //实时显示俯瞰相机图像
    //寻找直线与图像边缘的交点
    cv::Point findIntersections(const cv::Mat &grayImg, const cv::Mat &zerosImg, const cv::Rect &selectArea);
    cv::Point findCenter(Line &fp1, Line &fp2); //寻找器件的中心点
    cv::Point getLineIntersection(FitLineInfo &fp1, FitLineInfo &fp2); //获取两条直线的交点
    FitLineInfo fitLine(std::vector<cv::Point> &pointsFp); //使用最小二乘法拟合直线
    void doSoftwareOnce(); //软触发一次

    //解析Json文件
    void analyzeJson(std::vector<RectangleInfo> &eclusionAreaVec,
                     std::vector<RectangleInfo> &selectAreaVec,
                     std::vector<LineInfo>      &vector_LeftLine,
                     std::vector<LineInfo>      &vector_RightLine,
                     std::vector<LineInfo>      &vector_UpLine,
                     std::vector<LineInfo>      &vector_DownLine,
                     const QString &fileName);

    bool binImageFunc();// 二值化处理函数
    bool sobel(cv::Mat& imageFp); //sobel函数
    int  RGB2BGR( unsigned char* pRgbData, unsigned int nWidth, unsigned int nHeight );
    bool convert2Mat(MV_FRAME_OUT_INFO_EX* pstImageInfo, unsigned char * pData,cv::Mat* srcImage);

    cv::Point jsonToPoint(const QJsonObject &jsonObject);
    RectangleInfo jsonToEclusionArea(const QJsonObject &jsonObject);
    RectangleInfo jsonToSelectArea(const QJsonObject &jsonObject);
    LineInfo jsonToAllLine(const QJsonObject &jsonObject);

private:
    Ui::OpenMultiCamDlg *ui;
    MV_CC_DEVICE_INFO_LIST  m_stDevList; //
    QString m_curIp; //IP地址字符串
    QMutex  mutex;   //互斥锁
    QList<CMvCamera*> m_listMyCamera; //相机列表
    QList<CMvCamera*> m_listWorkingCamera; //工作中的相机列表
    QList<void*> m_hGrabThread; //图像采集线程
    QList<QThread*> threadListWorkingCam; //线程中工作的相机
    QHash<QString, int> m_typeHash = {{"192.168.0.2", 0}, {"192.168.0.4", 1}, {"192.168.0.8", 2}};

    cv::Mat m_sobelEdges; //sobel图像
    cv::Mat m_binImg; //二值化图像
    cv::Mat m_sobelEdgesBgr; //由二值图转为BGR
    cv::Mat m_sobelEdgesBgrCopy;
    cv::Mat m_matImgUp;
    cv::Mat m_matImgDown;
    cv::Mat m_srcSobelEdge; //从二值图像处赋值得到
    cv::Mat formatToMat;

    cv::Mat testImg; //仰望相机使用
    cv::Mat testImg_1;

    cv::Mat testImg_2; //俯视相机使用
    cv::Mat testImg_3;

    //cv::Mat lineImage;

    int m_threshold = 40;
    int m_binThreshNum = 80;
    int i_camIndex;        //相机索引值
    bool m_StartGrabbing; //图像是否在采集标志
    bool m_isRealTimeProcess; //判断是否为实时状态

    std::vector<RectangleInfo> vector_EclusionAreaFromJson; //选择区域
    std::vector<RectangleInfo> vector_SelectAreaFromJson;   //筛选区域
    std::vector<LineInfo>      vector_LeftDrawLineFromJson; //左、右、上、下边缘线集合
    std::vector<LineInfo>      vector_RightDrawLineFromJson;
    std::vector<LineInfo>      vector_UpDrawLineFromJson;
    std::vector<LineInfo>      vector_DownDrawLineFromJson;

    LineInfo m_LineInfo;
    std::vector<LineInfo> vector_LeftLine;
    std::vector<cv::Point> m_Intersections; //直线与图像边缘交点的容器
    std::vector<FitLineInfo> m_fitLine;



signals:
    void sigUpdatePicture1();//发送信号触发图像控件的update信号
    void sigUpdatePicture2();
    void sigUpdatePicture3();
    void sigUpdatePicture4();

    void sigSendUpImg(cv::Mat,int); //传递图像到FindCenter
    void sigSendDownImg(cv::Mat,int); //传递图像到FindCenter
    void activateFindCenter();    //激活主界面的FindCenter

private slots:
    void on_btnEnumCam_clicked(); //查找并枚举相机设备
    void on_btnOpenCam_clicked(); //打开相机设备
    void on_btnClose_clicked();   //关闭相机
    void on_btnContinuesMode_clicked(); //相机工作为连续模式
    void on_btnTriggerMode_clicked();   //相机工作为触发模式
    void on_btnStartAqui_clicked();     //开始采集
    void on_btnStop_clicked();          //停止采集
    void on_btnTriggerExec_clicked();   //软触发一次
    void on_btnSetUpCameraLine_clicked();   //对仰望照片进行处理
    void on_btnSetDownCameraLine_clicked(); //对俯视照片进行处理
    void on_btnShowImage_clicked();     //实时显示
    void on_btnAnalyzeJson_A_clicked();  //解析A类型Json文件
    void on_btnAnalyzeJson_B_clicked();  //解析B类型Json文件
    void on_btnFindCenter_A_clicked(); //标定器件的中心点
    void on_btnFindCenter_B_clicked(); //标定B器件的中心点

};

#endif // OPENMULTICAMDLG_H
