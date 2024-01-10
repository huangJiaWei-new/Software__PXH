﻿#ifndef FINDRECTCENTERDLG_H
#define FINDRECTCENTERDLG_H

#include <QWidget>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#pragma execution_character_set("utf-8") //防止中文乱码
using namespace std;
// 定义一个直线结构体
struct Line
{
    cv::Point p1, p2;
};

//拟合直线结构体，包含拟合直线的斜率、截距
struct FitLineInfo
{
    double k; // 斜率
    double b; // 截距
    FitLineInfo(double k, double b) : k(k), b(b) {}
};


//直线结构体，包含直线的起点、终点、交点
struct LineInfo
{
    cv::Point lineStartPoint;
    cv::Point lineEndPoint;
    cv::Point intersectionPoint;
};

//矩形结构体，左上角为矩形起点，右下角为矩形终点
struct RectangleInfo
{
    cv::Point rectStartPoint;
    cv::Point rectEndPoint;
    cv::Point rectCenterPoint;
};

//将符合要求的绘制的直线与选取区域绑定在一起
struct BindLineAndRect
{
    RectangleInfo rectangleInfo;
    LineInfo      lineInfo;
};

//所有结构体的容器
struct AllInfoCollection
{
    std::vector<RectangleInfo> vec_SelectArea;   //选择区域容器
    std::vector<RectangleInfo> vec_EclusionArea; //排除区域容器

    std::vector<LineInfo> vec_LeftLine;  //左边缘线容器
    std::vector<LineInfo> vec_RightLine; //右边缘线容器
    std::vector<LineInfo> vec_UpLine;    //上边缘线容器
    std::vector<LineInfo> vec_DownLine;  //下边缘线容器

    std::vector<FitLineInfo> vec_FitLine; //拟合直线容器

    //std::vector<BindLineAndRect> vec_BindLineAndRect; //将绘制的直线与选取区域绑定在一起的容器

    std::vector<BindLineAndRect> vec_leftLine_leftSelectArea;   //左边缘线与左选择区域集合的容器
    std::vector<BindLineAndRect> vec_rightLine_rightSelectArea; //右边缘线与右选择区域集合的容器
    std::vector<BindLineAndRect> vec_upLine_upSelectArea;       //上边缘线与上选择区域集合的容器
    std::vector<BindLineAndRect> vec_downLine_downSelectArea;   //下边缘线与下选择区域集合的容器


};


namespace Ui {
class FindRectCenterDlg;
}

class FindRectCenterDlg : public QWidget
{
    Q_OBJECT

public:
    explicit FindRectCenterDlg(QWidget *parent = nullptr);
    ~FindRectCenterDlg();

    //设置、获取平移图像
    static void setScaleImg(cv::Mat inputImg);
    static cv::Mat getScaleImg();

    //设置、获取sobel图像
    static void setsobelEdgesImg(cv::Mat inputImg);
    static cv::Mat getsobelEdgesImg();

    static std::string getWinName();

    static void setExclusionCount(int exclusionCount);
    static void setStartPoint_Mouse(cv::Point startPointMouse);
    static void setEndPonint_Mouse(cv::Point endPointMouse);
    static void setSelectAreaCount(int count);

    static int getExclusionCount();
    static cv::Point getstartPoint_Mouse();
    static cv::Point getendPonint_Mouse();
    static int getSelectAreaCount();

    //设置矩形的起点、终点、中心点坐标
    static void setRectStartPoint(cv::Point startPoint);
    static void setRectEndPoint(cv::Point endPoint);
    static void setRectCenterPoint(cv::Point centerPoint);

    //获取矩形的起点、终点、中心点坐标及矩形整体
    static cv::Point getRectStartPoint();
    static cv::Point getRectEndPoint();
    static cv::Point getRectCenterPoint();
    static RectangleInfo getRectInfo();

    //设置直线的起点、终点、交点坐标
    static void setLineStartPoint(cv::Point startPoint);
    static void setLineEndPoint(cv::Point endPoint);
    static void setLineIntersectionPoint(cv::Point intersectionPoint);

    //获取直线的起点、终点、交点坐标及直线整体
    static cv::Point getLineStartPoint();
    static cv::Point getLineEndPoint();
    static cv::Point getLineIntersectionPoint();
    static LineInfo  getLineInfo();

    //设置选择、筛选区域的容器
    static void setSelectAreaVec(RectangleInfo selectArea);
    static void setEclusionAreaVec(RectangleInfo eclusionArea);

    //获取选择、筛选区域的容器
    static std::vector<RectangleInfo> getSelectAreaVec();
    static std::vector<RectangleInfo> getEclusionAreaVec();

    //设置、获取左、右、上、下边缘线的容器
    static void setLeftLineVec(LineInfo leftLineVec);
    static void setRightLineVec(LineInfo rightLineVec);
    static void setUpLineVec(LineInfo upLineVec);
    static void setDownLineVec(LineInfo downLineVec);

    static std::vector<LineInfo> getLeftLineVec();   
    static std::vector<LineInfo> getRightLineVec();
    static std::vector<LineInfo> getUpLineVec();
    static std::vector<LineInfo> getDownLineVec();

    //设置、获取拟合直线的容器
    static void setFitLineVec(FitLineInfo fitLineVec);
    static std::vector<FitLineInfo> getFitLineVec();

    //设置、获取绘制的直线与选取区域绑定在一起的集合
    static void setBindLineAndRect(LineInfo lineInfo, RectangleInfo rectangleInfo);
    static BindLineAndRect getBindLineAndRect();


    //设置、获取绘制的左、右、上、下直线与选取区域绑定在一起的容器
    static void set_leftLineAddleftSelectAreaVec(BindLineAndRect leftLineAddleftSelectAreaVec);
    static void set_rightLineAddrightSelectAreaVec(BindLineAndRect rightLineAddrightSelectAreaVec);
    static void set_upLineAddupSelectAreaVec(BindLineAndRect upLineAddupSelectAreaVec);
    static void set_downLineAdddownSelectAreaVec(BindLineAndRect downLineAdddownSelectAreaVec);

    static std::vector<BindLineAndRect> get_leftLineAddleftSelectAreaVec();
    static std::vector<BindLineAndRect> get_rightLineAddrightSelectAreaVec();
    static std::vector<BindLineAndRect> get_upLineAddupSelectAreaVec();
    static std::vector<BindLineAndRect> get_downLineAdddownSelectAreaVec();

    //获取'AllInfoCollection'信息
    static AllInfoCollection& getAllInfoCollection();

    //static void setBindLineAndRectVec(BindLineAndRect bindLineAndRect); //?
    //static std::vector<BindLineAndRect> getBindLineAndRectVec(); //?函数是否有使用

    //寻找直线与边缘的交点
    static cv::Point findIntersections(cv::Mat& grayImg, cv::Mat& zerosImg, cv::Rect& selectArea);

    //static double findNearestLineIndex(cv::Point inputPoint); //寻找距离最近的直线

public:

private:
    bool mySobel(cv::Mat &inputImg); //sobel函数
    bool binImageFunc(); //二值化函数
    void namedWindowToWidget(std::string namedWindowTitle, QWidget * widget);

    FitLineInfo fitLine(vector<cv::Point> &pointsFp); //拟合直线
    cv::Point getLineIntersection(FitLineInfo &fp1, FitLineInfo &fp2); //获取两条直线的交点
    cv::Point findCenter(Line &fp1, Line &fp2);

    QJsonObject pointToJson(const cv::Point& point);

    QJsonObject eclusionAreaToJson(const RectangleInfo &item);

    QJsonObject bindLineAndRectToJson(const BindLineAndRect &item);

    void saveToJson(const std::vector<RectangleInfo> &RectVector, const std::vector<std::vector<BindLineAndRect>> &RectLineVectors, const QString &fileName);

    //size_t findClosestLineIndex(int x, int y);
    void loadJsonFile(const QString& filePath);



//    void excludeMouseDrawing(cv::Mat& image);   //绘制排除区域
//    void excludeMouseDrawing_2(cv::Mat& image); //存在意义？
//    void selectMouseDrawing(cv::Mat& image);    //绘制选择区域
//    void selectMouseDrawing_2(cv::Mat& image);  //存在意义？
//    void mouseDrawingLeft(cv::Mat& image);      //绘制左边缘线
//    void mouseDrawingLeft_2(cv::Mat& image);
//    void mouseDrawingRight(cv::Mat& image);     //绘制右边缘线
//    void mouseDrawingRight_2(cv::Mat& image);
//    void mouseDrawingUp(cv::Mat& image);        //绘制上边缘线
//    void mouseDrawingUp_2(cv::Mat& image);
//    void mouseDrawingBottom(cv::Mat& image);    //绘制下边缘线
//    void mouseDrawingBottom_2(cv::Mat& image);
//    RectLine fit_line(vector<cv::Point> &pointsFp); //拟合线
//    cv::Point getIntersection(RectLine &fp1, RectLine &fp2); //两条直线交点
//    cv::Point intersection(Line &fp1, Line &fp2);


private:
    Ui::FindRectCenterDlg *ui;
    static cv::Mat m_sobelEdges; //sobel图像
    cv::Mat m_binImg;     //二值化图像
    //cv::Mat
    static cv::Mat m_scaleImg;   //比例图像
    //cv::Mat m_sobelBGREdges;
    int iThreshold = 40;  //二值化阈值
    int iBinThreshNum = 40;

    cv::Mat m_UpImage;    //仰望相机图像
    cv::Mat m_DownImage;  //俯视相机图像
    static std::string winName;
    int isUpImgorDownImg; //0为仰望，1为俯视
    static int exclusionCount;
    static int count_SelectArea;
    static cv::Point startPoint_Mouse; //鼠标起始位置
    static cv::Point endPoint_Mouse;   //鼠标结束位置
    static RectangleInfo m_rectInfo;   //声明'RectangleInfo'变量
    static LineInfo m_lineInfo;        //声明'LineInfo'变量
    static AllInfoCollection m_allInfoCollection; //声明'AllInfoCollection'变量
    static FitLineInfo m_fitLine; //声明'FitLine'变量
    static BindLineAndRect m_BindLineAndRect; //声明'BindLineAndRect'变量
    bool isSwitch;


signals:

private slots:
    void receiveUpImg(cv::Mat UpImg, int index_Img);

    void on_btnPreProcess_clicked();        //图像预处理
    void on_btnExcludeProcess_clicked();    //添加排除区域
    void on_btnSelectProcess_clicked();     //添加选择区域
    void on_btnDrawLeftProcess_clicked();   //绘制左边缘线
    void on_btnDrawRightProcess_clicked();  //绘制右边缘线
    void on_btnDrawUpProcess_clicked();     //绘制上边缘线
    void on_btnDrawBottomProcess_clicked(); //绘制下边缘线
    void on_btnFitLeftProcess_clicked();    //拟合左边缘线
    void on_btnFitRightProcess_clicked();   //拟合右边缘线
    void on_btnFitUpProcess_clicked();      //拟合上边缘线
    void on_btnFitBottomProcess_clicked();  //拟合下边缘线
    void on_btnCenterProcess_clicked();     //拟合中心点
    void on_btnJsonProcess_clicked();       //生成Json文件
    void on_btnUndo_clicked();              //撤销直线

    //void on_switch1_clicked();
};




















#endif // FINDRECTCENTERDLG_H
