#ifndef FINDRECTCENTERDLG_H
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

// 定义一个直线结构体
struct RectLine
{
    double k; // 斜率
    double b; // 截距
    RectLine(double k, double b) : k(k), b(b) {}
};

//定义结构体，包含直线的起始点和交点
struct LineResult
{
    cv::Point LineStart;
    cv::Point LineEnd;
    cv::Point intersection;
};

//矩形结构体，左上角为矩形起点，右下角为矩形终点
struct RectangleInfo
{
    cv::Point rectStartPoint;
    cv::Point rectEndPoint;
    cv::Point rectCenterPoint;
};

//定义结构体，包含矩形的起始点
//struct RectLineResult
//{
//    RectResult RectLineResult_Rect;
//    LineResult RectLineResult_Line;
//};

//定义结构体，包含矩形区域、结果
/*struct SelectRect
{
    //选择区域
    std::vector<RectResult> xzRect;
    std::vector<RectResult> xzRect_left;
    std::vector<RectResult> xzRect_up;
    std::vector<RectResult> xzRect_right;
    std::vector<RectResult> xzRect_bottom;
    //筛选区域
    std::vector<RectResult> sxRect;
    std::vector<LineResult> lineResult;
    std::vector<LineResult> lineResult_LV;
    std::vector<LineResult> lineResult_RV;
    std::vector<LineResult> lineResult_UL;
    std::vector<LineResult> lineResult_DL;
    //选择区域和对应直线
    std::vector<RectLineResult> RectAddLine_LV;
    std::vector<RectLineResult> RectAddLine_UL;
    std::vector<RectLineResult> RectAddLine_RV;
    std::vector<RectLineResult> RectAddLine_DL;


    //选择区域
    std::vector<RectResult> xzRect_2;
    std::vector<RectResult> xzRect_left_2;
    std::vector<RectResult> xzRect_up_2;
    std::vector<RectResult> xzRect_right_2;
    std::vector<RectResult> xzRect_bottom_2;
    //筛选区域
    std::vector<RectResult> sxRect_2;
    std::vector<LineResult> lineResult_2;
    std::vector<LineResult> lineResult_LV_2;
    std::vector<LineResult> lineResult_RV_2;
    std::vector<LineResult> lineResult_UL_2;
    std::vector<LineResult> lineResult_DL_2;
    //选择区域和对应直线
    std::vector<RectLineResult> RectAddLine_LV_2;
    std::vector<RectLineResult> RectAddLine_UL_2;
    std::vector<RectLineResult> RectAddLine_RV_2;
    std::vector<RectLineResult> RectAddLine_DL_2;
};*/


namespace Ui {
class FindRectCenterDlg;
}

class FindRectCenterDlg : public QWidget
{
    Q_OBJECT

public:
    explicit FindRectCenterDlg(QWidget *parent = nullptr);
    ~FindRectCenterDlg();

    static void setScaleImg(cv::Mat inputImg);
    static cv::Mat getScaleImg();
    static std::string getWinName();

    static void setExclusionCount(int exclusionCount);
    static void setStartPoint_Mouse(cv::Point startPointMouse);
    static void setEndPonint_Mouse(cv::Point endPointMouse);

    static int getExclusionCount();
    static cv::Point getstartPoint_Mouse();
    static cv::Point getendPonint_Mouse();

    static void setRectStartPoint(cv::Point startPoint); //设置矩形的起点、终点、中心点坐标
    static void setRectEndPoint(cv::Point endPoint);
    static void setRectCenterPoint(cv::Point centerPoint);

    static cv::Point getRectStartPoint(); //获取设置矩形的起点、终点、中心点坐标
    static cv::Point getRectEndPoint();
    static cv::Point getRectCenterPoint();


public:

private:
    bool mySobel(cv::Mat &inputImg); //sobel函数
    bool binImageFunc(); //二值化函数
    void namedWindowToWidget(std::string namedWindowTitle, QWidget * widget);

    //static void OpenCVMouse(int event, int x, int y, int flags, void* userdata);

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
    cv::Mat m_sobelEdges; //sobel图像
    cv::Mat m_binImg;     //二值化图像
    static cv::Mat m_scaleImg;   //比例图像
    //cv::Mat m_sobelBGREdges;
    int iThreshold = 40;  //二值化阈值
    int iBinThreshNum = 40;

    cv::Mat m_UpImage;    //仰望相机图像
    cv::Mat m_DownImage;  //俯视相机图像
    static std::string winName;
    int isUpImgorDownImg; //0为仰望，1为俯视
    static int exclusionCount;
    static cv::Point startPoint_Mouse; //鼠标起始位置
    static cv::Point endPoint_Mouse;   //鼠标结束位置
    static RectangleInfo m_rectInfo;   //声明'RectangleInfo'变量
    bool isSwitch;


signals:

private slots:
    void receiveUpImg(cv::Mat UpImg, int index_Img);

    void on_btnPreProcess_clicked();        //图像预处理
    void on_btnExcludeProcess_clicked();    //添加排除区域
    void on_btnSelectProcess_clicked();     //添加选择区域
//    void on_btnDrawLeftProcess_clicked();   //绘制左边缘线
//    void on_btnDrawRightProcess_clicked();  //绘制右边缘线
//    void on_btnDrawUpProcess_clicked();     //绘制上边缘线
//    void on_btnDrawBottomProcess_clicked(); //绘制下边缘线
//    void on_btnFitLeftProcess_clicked();    //拟合左边缘线
//    void on_btnFitRightProcess_clicked();   //拟合右边缘线
//    void on_btnFitUpProcess_clicked();      //拟合上边缘线
//    void on_btnFitBottomProcess_clicked();  //拟合下边缘线
//    void on_btnCenterProcess_clicked();     //拟合中心点
//    void on_btnJsonProcess_clicked();       //生成Json文件

    //void on_switch1_clicked();
};




















#endif // FINDRECTCENTERDLG_H
