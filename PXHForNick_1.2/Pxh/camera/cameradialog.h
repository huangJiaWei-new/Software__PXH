#ifndef OPENMULTICAMDLG_H
#define OPENMULTICAMDLG_H

#include <QWidget>
#include "cmvcamera.h"
#include "cmd_def.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <QThread>
#include <QTimer>
#include <vector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <qmutex.h>

#pragma execution_character_set("utf-8") //防止中文乱码
//定义一个直线结构体
struct S_Line {
    cv::Point p1, p2;
};
// 定义一个直线结构体
struct S_RectLine {
    double k; // 斜率
    double b; // 截距
    S_RectLine(double k, double b) : k(k), b(b) {}
};
//定义结构体，包含直线的起始点和交点
struct S_LineResult{
    cv::Point LineStart;
    cv::Point LineEnd;
    cv::Point intersection;
};
//定义结构体，包含矩形的起始点
struct S_RectResult{
    cv::Point RectStart;
    cv::Point RectEnd;
    cv::Point RectCenter;
};
//定义结构体，包含矩形的起始点
struct S_RectLineResult{
    S_RectResult RectLineResult_Rect;
    S_LineResult RectLineResult_Line;
};
//定义结构体，包含矩形区域、结果
struct S_SelectRect{
    //选择区域
    std::vector<S_RectResult> xzRect;
    std::vector<S_RectResult> xzRect_left;
    std::vector<S_RectResult> xzRect_up;
    std::vector<S_RectResult> xzRect_right;
    std::vector<S_RectResult> xzRect_bottom;
    //筛选区域
    std::vector<S_RectResult> sxRect;
    std::vector<S_LineResult> lineResult;
    std::vector<S_LineResult> lineResult_LV;
    std::vector<S_LineResult> lineResult_RV;
    std::vector<S_LineResult> lineResult_UL;
    std::vector<S_LineResult> lineResult_DL;
    //选择区域和对应直线
    std::vector<S_RectLineResult> RectAddLine_LV;
    std::vector<S_RectLineResult> RectAddLine_UL;
    std::vector<S_RectLineResult> RectAddLine_RV;
    std::vector<S_RectLineResult> RectAddLine_DL;


    //选择区域
    std::vector<S_RectResult> xzRect_2;
    std::vector<S_RectResult> xzRect_left_2;
    std::vector<S_RectResult> xzRect_up_2;
    std::vector<S_RectResult> xzRect_right_2;
    std::vector<S_RectResult> xzRect_bottom_2;
    //筛选区域
    std::vector<S_RectResult> sxRect_2;
    std::vector<S_LineResult> lineResult_2;
    std::vector<S_LineResult> lineResult_LV_2;
    std::vector<S_LineResult> lineResult_RV_2;
    std::vector<S_LineResult> lineResult_UL_2;
    std::vector<S_LineResult> lineResult_DL_2;
    //选择区域和对应直线
    std::vector<S_RectLineResult> RectAddLine_LV_2;
    std::vector<S_RectLineResult> RectAddLine_UL_2;
    std::vector<S_RectLineResult> RectAddLine_RV_2;
    std::vector<S_RectLineResult> RectAddLine_DL_2;
};


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
    void doSoftwareOnce();
    void startCamByQThreadCallBack();
    void setTriggerMode(int nTriggerMode);
    void setTriggerSource(int nTriggerSource);
    void showErrorMsg(QString csMessage, long long nErrorNum);
    void camCallBackInner(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo,int camIndex,QString frameCountInfo);
    void loadFromJson(std::vector<S_RectResult> &RectVector, std::vector<std::vector<S_RectLineResult>> &RectLineVectors, const QString &fileName);
    void static __stdcall  camCallBack0(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser);
    void static __stdcall  camCallBack1(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser);
    void static __stdcall  camCallBack2(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser);
    void static __stdcall  camCallBack3(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser);


    bool binImageFunc();// 二值化处理函数
    bool sobel(cv::Mat& imageFp);
    int  RGB2BGR( unsigned char* pRgbData, unsigned int nWidth, unsigned int nHeight );
    bool convert2Mat(MV_FRAME_OUT_INFO_EX* pstImageInfo, unsigned char * pData,cv::Mat* srcImage);

    cv::Mat showUpCameraImage(cv::Mat& UpCameraImage);
    cv::Mat showDownCameraImage(cv::Mat& DownCameraImage);
    cv::Point intersection(S_Line &fp1, S_Line &fp2);
    cv::Point getIntersection(S_RectLine &fp1, S_RectLine &fp2);
    cv::Point S_findIntersections(cv::Mat& BinaryImage, cv::Mat& newBinaryImage, cv::Rect& roi);
    cv::Point S_findIntersections_2(cv::Mat& BinaryImage, cv::Mat& newBinaryImage, cv::Rect& roi);
    cv::Point jsonToPoint(const QJsonObject &jsonObject);

    S_RectResult jsonToRectResult(const QJsonObject &jsonObject);
    S_RectLineResult jsonToRectLineResult(const QJsonObject &jsonObject);
    S_RectLine fit_line(std::vector<cv::Point> &pointsFp);

private:
    Ui::OpenMultiCamDlg *ui;
    MV_CC_DEVICE_INFO_LIST  m_stDevList;
    QString m_curIp; //IP地址字符串
    QMutex  mutex;   //互斥锁
    QList<CMvCamera*> m_listMyCamera;
    QList<CMvCamera*> m_listWorkingCamera;
    QList<void*> m_hGrabThread; //图像采集线程
    QList<QThread*> threadListWorkingCam; //工作中的相机线程   
    QHash<QString, int> m_typeHash = {{"192.168.0.2", 0}, {"192.168.0.4", 1}, {"192.168.0.8", 2}};

    cv::Mat m_sobelEdges;
    cv::Mat m_matBinImage;
    cv::Mat m_sobelEdgesBgr;
    cv::Mat m_sobelEdgesBgrCopy;
    cv::Mat m_matImgUp;
    cv::Mat m_matImgDown;

    int m_threshold = 40;
    int m_iBinThreshNum;
    int i_camIndex;        //相机索引值
    bool m_bStartGrabbing; //图像是否采集标志
    bool m_isRealTimeProcess; //判断是否为实时状态

signals:
    void sigUpdatePicture1();//发送信号触发图像控件的update信号
    void sigUpdatePicture2();
    void sigUpdatePicture3();
    void sigUpdatePicture4();

    void sigSendImg(cv::Mat,int); //传递图像到FindCenter
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
    void on_btnJson_clicked();          //解析Json文件
    void on_btnShowImage_clicked();     //实时显示
};

#endif // OPENMULTICAMDLG_H
