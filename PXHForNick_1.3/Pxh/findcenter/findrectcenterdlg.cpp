#include "findrectcenterdlg.h"
#include "ui_findrectcenterdlg.h"
#include <windows.h>
#include <opencv2/highgui/highgui_c.h>
#include <QMessageBox>
#include <QDebug>
#include <QWheelEvent>
#include <QJsonArray>
#include <QtMath>
#include "cmd_def.h"

//初始化静态变量
std::string FindRectCenterDlg::winName = "test";
cv::Mat FindRectCenterDlg::m_scaleImg  = cv::Mat::zeros(3, 3, CV_8UC1);
cv::Mat FindRectCenterDlg::m_sobelEdges = cv::Mat::zeros(3, 3, CV_8UC1);
//cv::Mat FindRectCenterDlg::m_
int FindRectCenterDlg::exclusionCount   = 0;
int FindRectCenterDlg::count_SelectArea = 0;
cv::Point FindRectCenterDlg::startPoint_Mouse = (-1, -1);
cv::Point FindRectCenterDlg::endPoint_Mouse   = (-1, -1);
RectangleInfo FindRectCenterDlg::m_rectInfo;
LineInfo FindRectCenterDlg::m_lineInfo;
AllInfoCollection FindRectCenterDlg::m_allInfoCollection;
BindLineAndRect FindRectCenterDlg::m_BindLineAndRect;

static int move_X  = 0;
static int move_Y  = 0;


FindRectCenterDlg::FindRectCenterDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindRectCenterDlg)
{
    ui->setupUi(this);

    cv::Mat matSrcImg;
    //isSwitch = false;
    matSrcImg = cv::imread("D:/QT_Training/PXHForNick/Test.jpg");//1:多通道   0：单通道
    receiveUpImg(matSrcImg, 0);
}


FindRectCenterDlg::~FindRectCenterDlg()
{
    delete ui;
}


/*--------------@brief：图像平移回调函数-------------*/
/*--------------@note： -------------*/
static void moveImg(int event, int x, int y, int flags, void *userdata)
{
    static int mouse_X = 0;
    static int mouse_Y = 0;

    if (event == cv::EVENT_MOUSEWHEEL)//鼠标滚轮
    {


    }
    else if (event == cv::EVENT_RBUTTONDOWN) //鼠标右键down
    {
        //qDebug()<<("EVENT_RBUTTONDOWN\n");
        mouse_X=x;
        mouse_Y=y;
        qDebug()<<"x:"<<x;
        qDebug()<<"y:"<<y;

    }
    else if (event == cv::EVENT_RBUTTONDBLCLK) //鼠标右键clicked
    {

    }
    else if (event == cv::EVENT_RBUTTONUP)     //鼠标右键up
    {
        static cv::Mat scaleImg;
        static cv::Mat outputImg;

        scaleImg = FindRectCenterDlg::getScaleImg();
        cv::Size outputSize = scaleImg.size();
        //定义变换矩阵，进行平移操作
        cv::Mat transMatrix = (cv::Mat_<double>(2, 3) << 1, 0, x-mouse_X+move_X,
                                                         0, 1, y-mouse_Y+move_Y);

        cv::warpAffine(scaleImg, outputImg, transMatrix, outputSize); //根据平移矩阵进行仿射变换
        cv::imshow("test",outputImg);
        //FindRectCenterDlg::setScaleImg(outputImg);
        move_X=x-mouse_X; //前一次位移
        move_Y=y-mouse_Y;
    }
    else if(event == cv::EVENT_LBUTTONDOWN) //鼠标左键点击
    {

    }
    else
    {


    }

}


/*--------------@brief：添加排除区域回调函数-------------*/
/*--------------@note： -------------*/
static void addExclusionArea(int event,int x,int y,int flags,void *userdata)
{
    cv::Mat image = *((cv::Mat*)userdata);

    static int exclusionCount = FindRectCenterDlg::getExclusionCount();
    static cv::Point startPoint_rect;
    static cv::Point endPoint_rect;
    static cv::Point centerPoint_rect;
    static RectangleInfo info_ExclusionRect;
    //static std::vector<RectangleInfo> ExclusionRect;
    //ExclusionRect = FindRectCenterDlg::getEclusionAreaVec();
    //qDebug() << "大小为" <<ExclusionRect.size();

    //绘制筛选区域
    if (event == cv::EVENT_LBUTTONDOWN)
    {
        if (exclusionCount == 0)
        {
            FindRectCenterDlg::setRectStartPoint(cv::Point(x, y));    //设置矩形起始点坐标
            //startPoint_rect = FindRectCenterDlg::getRectStartPoint(); //获取矩形起始点的坐标
            //qDebug() << "x的坐标" <<startPoint_rect.x<< "Y的坐标" <<startPoint_rect.y;
            exclusionCount++;
            FindRectCenterDlg::setExclusionCount(exclusionCount); //更新'exclusionCount'的值
        }
        else if (exclusionCount == 1)
        {         
            FindRectCenterDlg::setRectEndPoint(cv::Point(x, y));  //设置矩形终点坐标
            startPoint_rect = FindRectCenterDlg::getRectStartPoint(); //获取矩形起始点的坐标
            endPoint_rect   = FindRectCenterDlg::getRectEndPoint(); //获取矩形终点坐标

            //记录矩形的中心点坐标
            qDebug() << "排除区域x的坐标" <<startPoint_rect.x<< "Y的坐标" <<startPoint_rect.y;
            qDebug() << "排除区域的坐标" <<endPoint_rect.x<< "Y的坐标" <<endPoint_rect.y;

            centerPoint_rect = cv::Point( (startPoint_rect.x + endPoint_rect.x) / 2,
                                          (startPoint_rect.y + endPoint_rect.y) / 2 );
            FindRectCenterDlg::setRectCenterPoint(centerPoint_rect); //设置矩形的中心点坐标

            //将排除区域矩形放到容器里
            info_ExclusionRect = FindRectCenterDlg::getRectInfo(); //'m_rectInfo'是否有数据？有
            FindRectCenterDlg::setEclusionAreaVec(info_ExclusionRect); //筛选区域容器
            FindRectCenterDlg::setAllAreaVec(info_ExclusionRect); //包含所有矩形的容器

            //绘制矩形
            cv::rectangle(image, startPoint_rect, endPoint_rect, cv::Scalar(0, 0, 255), 2);
            cv::imshow("test", image);
            QMessageBox::information(NULL, "PROMPT(提示)", "请一次性绘制完排除区域");
            exclusionCount = 0;
            FindRectCenterDlg::setExclusionCount(exclusionCount); //更新'exclusionCount'的值
        }
    }
}


/** --------------@brief：添加选择区域回调函数------------- **/
/** --------------@note： ------------- **/
static void addSelectArea(int event,int x,int y,int flags,void *userdata)
{
    cv::Mat image = *((cv::Mat*)userdata);

    static int selectAreaCount = FindRectCenterDlg::getSelectAreaCount();
    static cv::Point startPoint_rect;
    static cv::Point endPoint_rect;
    static cv::Point centerPoint_rect;
    static RectangleInfo info_SelectRect;

    //绘制筛选区域
    if (event == cv::EVENT_LBUTTONDOWN)
    {
        if (selectAreaCount == 0)
        {
            FindRectCenterDlg::setRectStartPoint(cv::Point(x, y));    //设置矩形起始点坐标
            //startPoint_rect = FindRectCenterDlg::getRectStartPoint();
            //qDebug() << "x的坐标" <<startPoint_rect.x<< "Y的坐标" <<startPoint_rect.y;
            selectAreaCount++;
            FindRectCenterDlg::setSelectAreaCount(selectAreaCount); //更新'count_SelectArea'的值
        }
        else if (selectAreaCount == 1)
        {
            FindRectCenterDlg::setRectEndPoint(cv::Point(x, y)); //设置矩形终点坐标
            startPoint_rect = FindRectCenterDlg::getRectStartPoint(); //获取矩形起始点的坐标
            endPoint_rect   = FindRectCenterDlg::getRectEndPoint(); //获取矩形终点坐标

            //记录矩形的中心点坐标
            qDebug() << "选择区域x的坐标" <<startPoint_rect.x<< "Y的坐标" <<startPoint_rect.y;
            qDebug() << "选择区域x的坐标" <<endPoint_rect.x<< "Y的坐标" <<endPoint_rect.y;

            centerPoint_rect = cv::Point( (startPoint_rect.x + endPoint_rect.x) / 2,
                                          (startPoint_rect.y + endPoint_rect.y) / 2 );
            FindRectCenterDlg::setRectCenterPoint(centerPoint_rect); //设置矩形的中心点坐标

            //将选择区域矩形放到容器里
            info_SelectRect = FindRectCenterDlg::getRectInfo(); //'m_rectInfo'是否有数据？有
            //qDebug() << "x的坐标" <<info_SelectRect.rectStartPoint.x<< "Y的坐标" <<info_SelectRect.rectStartPoint.y;
            //info_SelectRect.rectCenterPoint
            FindRectCenterDlg::setSelectAreaVec(info_SelectRect); //选择区域容器
            FindRectCenterDlg::setAllAreaVec(info_SelectRect); //包含所有矩形的容器

            //绘制矩形
            cv::rectangle(image, startPoint_rect, endPoint_rect, cv::Scalar(0, 255, 0), 2);
            cv::imshow("test", image);
            QMessageBox::information(NULL, "PROMPT(提示)", "请绘制对应的边缘交线");
            selectAreaCount = 0;
            FindRectCenterDlg::setSelectAreaCount(selectAreaCount); //更新'count_SelectArea'的值
        }
    }
}


/** --------------@brief：绘制左边缘线回调函数------------- **/
/** --------------@note： ------------- **/
static void drawLeftLine(int event,int x,int y,int flags,void *userdata)
{
    cv::Mat image = *((cv::Mat*)userdata);

    static int selectAreaCount = FindRectCenterDlg::getSelectAreaCount();
    //qDebug()<<"selectAreaCount" << selectAreaCount;
    static cv::Point startPoint_line;
    static cv::Point endPoint_line;
    static cv::Mat lineImage;
    static cv::Mat sobelImg;
    static cv::Mat gray_SobelImg;

    static cv::Point intersectionPoint_Line;
    static cv::Point intersectionPoint;
    static std::vector<RectangleInfo> vector_rect;
    static LineInfo info_LeftLine;
    static BindLineAndRect bindLineAndRect;

    if (event == cv::EVENT_LBUTTONDOWN)
    {
        if (selectAreaCount == 0)
        {
            FindRectCenterDlg::setLineStartPoint(cv::Point(x, y));    //设置直线起始点坐标
            //startPoint_line = FindRectCenterDlg::getLineStartPoint(); //获取直线起始点的坐标
            //qDebug() << "x的坐标" <<startPoint_line.x<< "Y的坐标" <<startPoint_line.y;
            selectAreaCount++;
            FindRectCenterDlg::setSelectAreaCount(selectAreaCount); //更新'count_SelectArea'的值
        }
        else if (selectAreaCount == 1)
        {
            FindRectCenterDlg::setLineEndPoint(cv::Point(x, y));  //设置直线终点坐标
            startPoint_line = FindRectCenterDlg::getLineStartPoint(); //获取直线起始点的坐标
            endPoint_line = FindRectCenterDlg::getLineEndPoint(); //获取直线终点坐标
            qDebug() << "左边缘起点x的坐标" <<startPoint_line.x<< "Y的坐标" <<startPoint_line.y;
            qDebug() << "左边缘终点x的坐标" <<endPoint_line.x<< "Y的坐标" <<endPoint_line.y;

            //cv::line(image, startPoint_line, endPoint_line, cv::Scalar(255, 0, 0), 1);
            //cv::imshow("test", image);

            // ------------↓  寻找直线与图像边缘的交点
            lineImage = cv::Mat::zeros(image.size(), CV_8UC1); //创建一张空白灰度图像
            sobelImg  = FindRectCenterDlg::getsobelEdgesImg(); //获取'sobel'图像
            vector_rect = FindRectCenterDlg::getSelectAreaVec(); //获取选择区域容器

            //得到选择区域容器内最新矩形的宽和高
            int dx = vector_rect.back().rectEndPoint.x - vector_rect.back().rectStartPoint.x;
            int dy = vector_rect.back().rectEndPoint.y - vector_rect.back().rectStartPoint.y;

            //定义一个矩形的位置与尺寸
            cv::Rect box(vector_rect.back().rectStartPoint.x,
                         vector_rect.back().rectStartPoint.y, dx, dy);

            cv::line(lineImage, startPoint_line, endPoint_line, cv::Scalar(255, 255, 255), 1);
            cv::cvtColor(sobelImg, gray_SobelImg, cv::COLOR_BGR2GRAY);

            //寻找交点
            intersectionPoint_Line = FindRectCenterDlg::findIntersections(gray_SobelImg, lineImage, box);
            // ------------↑

            //保证绘制的直线与图像边缘有交点，然后存入左边缘线容器、包含所有直线的容器
            if (intersectionPoint_Line.x != 0 && intersectionPoint_Line.y != 0)
            {
                cv::line(image, startPoint_line, endPoint_line, cv::Scalar(255, 0, 0), 1);
                cv::imshow("test", image);

                FindRectCenterDlg::setLineIntersectionPoint(intersectionPoint_Line);//设置直线的交点坐标
                info_LeftLine = FindRectCenterDlg::getLineInfo(); //'info_LeftLine'是否有数据？ 有
                FindRectCenterDlg::setLeftLineVec(info_LeftLine);
                FindRectCenterDlg::setAllLineVec(info_LeftLine);

                //将绘制的直线与选取区域绑定在一起
                FindRectCenterDlg::setBindLineAndRect(info_LeftLine, vector_rect.back());
                bindLineAndRect = FindRectCenterDlg::getBindLineAndRect();
                //将绘制的直线与选取区域绑定在一起的集合放入容器，左边
                FindRectCenterDlg::set_leftLineAddleftSelectAreaVec(bindLineAndRect);
            }
            else
            {
                QMessageBox::information(NULL, "PROMPT(提示)", "无交点，请重新绘制");
            }

            //qDebug() << "交点坐标为" << intersectionPoint_Line.x <<intersectionPoint_Line.y;

            //将绘制的直线与选取区域绑定在一起
            //FindRectCenterDlg::setBindLineAndRect(info_LeftLine, vector_rect.back());
            //bindLineAndRect = FindRectCenterDlg::getBindLineAndRect();
            //将绘制的直线与选取区域绑定在一起的集合放入容器，左边
            //FindRectCenterDlg::set_leftLineAddleftSelectAreaVec(bindLineAndRect);

            selectAreaCount = 0;
            FindRectCenterDlg::setSelectAreaCount(selectAreaCount); //更新'count_SelectArea'的值
        }
    }
}


/** --------------@brief：绘制右边缘线回调函数------------- **/
/** --------------@note： ------------- **/
static void drawRightLine(int event,int x,int y,int flags,void *userdata)
{
    cv::Mat image = *((cv::Mat*)userdata);

    static int selectAreaCount = FindRectCenterDlg::getSelectAreaCount();
    static cv::Point startPoint_line;
    static cv::Point endPoint_line;
    static cv::Mat lineImage;
    static cv::Mat sobelImg;
    static cv::Mat gray_SobelImg;

    static cv::Point intersectionPoint_Line;
    static std::vector<RectangleInfo> vector_rect;
    static LineInfo info_RightLine;
    static BindLineAndRect bindLineAndRect;

    if (event == cv::EVENT_LBUTTONDOWN)
    {
        if (selectAreaCount == 0)
        {
            FindRectCenterDlg::setLineStartPoint(cv::Point(x, y));    //设置直线起始点坐标
            selectAreaCount++;
            FindRectCenterDlg::setSelectAreaCount(selectAreaCount); //更新'count_SelectArea'的值
        }
        else if (selectAreaCount == 1)
        {
            FindRectCenterDlg::setLineEndPoint(cv::Point(x, y));  //设置直线终点坐标
            startPoint_line = FindRectCenterDlg::getLineStartPoint(); //获取直线起始点的坐标
            endPoint_line = FindRectCenterDlg::getLineEndPoint(); //获取直线终点坐标

            qDebug() << "右边缘起点x的坐标" <<startPoint_line.x<< "Y的坐标" <<startPoint_line.y;
            qDebug() << "右边缘终点x的坐标" <<endPoint_line.x<< "Y的坐标" <<endPoint_line.y;

            // ------------↓  寻找直线与图像边缘的交点
            lineImage = cv::Mat::zeros(image.size(), CV_8UC1); //创建一张空白灰度图像
            sobelImg  = FindRectCenterDlg::getsobelEdgesImg(); //获取'sobel'图像
            vector_rect = FindRectCenterDlg::getSelectAreaVec(); //获取选择区域容器

            //得到选择区域容器内最新矩形的宽和高
            int dx = vector_rect.back().rectEndPoint.x - vector_rect.back().rectStartPoint.x;
            int dy = vector_rect.back().rectEndPoint.y - vector_rect.back().rectStartPoint.y;

            //定义一个矩形的位置与尺寸
            cv::Rect box(vector_rect.back().rectStartPoint.x,
                         vector_rect.back().rectStartPoint.y, dx, dy);

            cv::line(lineImage, startPoint_line, endPoint_line, cv::Scalar(255, 255, 255), 1);
            cv::cvtColor(sobelImg, gray_SobelImg, cv::COLOR_BGR2GRAY);

            //寻找交点
            intersectionPoint_Line = FindRectCenterDlg::findIntersections(gray_SobelImg, lineImage, box);
            // ------------↑

            //保证绘制的直线与图像边缘有交点，然后存入右边缘线容器、包含所有直线的容器
            if (intersectionPoint_Line.x != 0 && intersectionPoint_Line.y != 0)
            {
                cv::line(image, startPoint_line, endPoint_line, cv::Scalar(255, 0, 0), 1);
                cv::imshow("test", image);

                FindRectCenterDlg::setLineIntersectionPoint(intersectionPoint_Line);//设置直线的交点坐标
                info_RightLine = FindRectCenterDlg::getLineInfo(); //'info_LeftLine'是否有数据？有
                FindRectCenterDlg::setRightLineVec(info_RightLine);
                FindRectCenterDlg::setAllLineVec(info_RightLine);

                //将绘制的直线与选取区域绑定在一起
                FindRectCenterDlg::setBindLineAndRect(info_RightLine, vector_rect.back());
                bindLineAndRect = FindRectCenterDlg::getBindLineAndRect();
                //将绘制的直线与选取区域绑定在一起的集合放入容器，右边
                FindRectCenterDlg::set_rightLineAddrightSelectAreaVec(bindLineAndRect);
            }
            else
            {
                QMessageBox::information(NULL, "PROMPT(提示)", "无交点，请重新绘制");
            }

            selectAreaCount = 0;
            FindRectCenterDlg::setSelectAreaCount(selectAreaCount); //更新'count_SelectArea'的值
        }
    }

}


/** --------------@brief：绘制上边缘线回调函数------------- **/
/** --------------@note： ------------- **/
static void drawUpLine(int event,int x,int y,int flags,void *userdata)
{
    cv::Mat image = *((cv::Mat*)userdata);

    static int selectAreaCount = FindRectCenterDlg::getSelectAreaCount();
    static cv::Point startPoint_line;
    static cv::Point endPoint_line;
    static cv::Mat lineImage;
    static cv::Mat sobelImg;
    static cv::Mat gray_SobelImg;

    static cv::Point intersectionPoint_Line;
    static std::vector<RectangleInfo> vector_rect;
    static LineInfo info_UpLine;
    static BindLineAndRect bindLineAndRect;

    if (event == cv::EVENT_LBUTTONDOWN)
    {
        if (selectAreaCount == 0)
        {
            FindRectCenterDlg::setLineStartPoint(cv::Point(x, y));    //设置直线起始点坐标
            selectAreaCount++;
            FindRectCenterDlg::setSelectAreaCount(selectAreaCount); //更新'count_SelectArea'的值
        }
        else if (selectAreaCount == 1)
        {
            FindRectCenterDlg::setLineEndPoint(cv::Point(x, y));  //设置直线终点坐标
            startPoint_line = FindRectCenterDlg::getLineStartPoint(); //获取直线起始点的坐标
            endPoint_line = FindRectCenterDlg::getLineEndPoint(); //获取直线终点坐标

            qDebug() << "上边缘起点x的坐标" <<startPoint_line.x<< "Y的坐标" <<startPoint_line.y;
            qDebug() << "上边缘终点x的坐标" <<endPoint_line.x<< "Y的坐标" <<endPoint_line.y;

            // ------------↓  寻找直线与图像边缘的交点
            lineImage = cv::Mat::zeros(image.size(), CV_8UC1); //创建一张空白灰度图像
            sobelImg  = FindRectCenterDlg::getsobelEdgesImg(); //获取'sobel'图像
            vector_rect = FindRectCenterDlg::getSelectAreaVec(); //获取选择区域容器

            //得到选择区域容器内最新矩形的宽和高
            int dx = vector_rect.back().rectEndPoint.x - vector_rect.back().rectStartPoint.x;
            int dy = vector_rect.back().rectEndPoint.y - vector_rect.back().rectStartPoint.y;

            //定义一个矩形的位置与尺寸
            cv::Rect box(vector_rect.back().rectStartPoint.x,
                         vector_rect.back().rectStartPoint.y, dx, dy);

            cv::line(lineImage, startPoint_line, endPoint_line, cv::Scalar(255, 255, 255), 1);
            cv::cvtColor(sobelImg, gray_SobelImg, cv::COLOR_BGR2GRAY);

            //寻找交点
            intersectionPoint_Line = FindRectCenterDlg::findIntersections(gray_SobelImg, lineImage, box);
            // ------------↑

            //保证绘制的直线与图像边缘有交点，然后存入上边缘线容器、包含所有直线的容器         
            if (intersectionPoint_Line.x != 0 && intersectionPoint_Line.y != 0)
            {
                cv::line(image, startPoint_line, endPoint_line, cv::Scalar(255, 0, 0), 1);
                cv::imshow("test", image);

                FindRectCenterDlg::setLineIntersectionPoint(intersectionPoint_Line);
                info_UpLine = FindRectCenterDlg::getLineInfo(); //'info_LeftLine'是否有数据？有
                FindRectCenterDlg::setUpLineVec(info_UpLine);
                FindRectCenterDlg::setAllLineVec(info_UpLine);

                //将绘制的直线与选取区域绑定在一起
                FindRectCenterDlg::setBindLineAndRect(info_UpLine, vector_rect.back());
                bindLineAndRect = FindRectCenterDlg::getBindLineAndRect();
                //将绘制的直线与选取区域绑定在一起的集合放入容器，上边
                FindRectCenterDlg::set_upLineAddupSelectAreaVec(bindLineAndRect);
            }
            else
            {
                QMessageBox::information(NULL, "PROMPT(提示)", "无交点，请重新绘制");
            }
            selectAreaCount = 0;
            FindRectCenterDlg::setSelectAreaCount(selectAreaCount); //更新'count_SelectArea'的值
        }
    }
}


/** --------------@brief：绘制下边缘线回调函数------------- **/
/** --------------@note： ------------- **/
static void drawDownLine(int event,int x,int y,int flags,void *userdata)
{
    cv::Mat image = *((cv::Mat*)userdata);

    static int selectAreaCount = FindRectCenterDlg::getSelectAreaCount();
    static cv::Point startPoint_line;
    static cv::Point endPoint_line;
    static cv::Mat lineImage;
    static cv::Mat sobelImg;
    static cv::Mat gray_SobelImg;

    static cv::Point intersectionPoint_Line;
    static std::vector<RectangleInfo> vector_rect;
    static LineInfo info_DownLine;
    static BindLineAndRect bindLineAndRect;

    if (event == cv::EVENT_LBUTTONDOWN)
    {
        if (selectAreaCount == 0)
        {
            FindRectCenterDlg::setLineStartPoint(cv::Point(x, y)); //设置直线起始点坐标
            selectAreaCount++;
            FindRectCenterDlg::setSelectAreaCount(selectAreaCount); //更新'count_SelectArea'的值
        }
        else if (selectAreaCount == 1)
        {
            FindRectCenterDlg::setLineEndPoint(cv::Point(x, y));  //设置直线终点坐标
            startPoint_line = FindRectCenterDlg::getLineStartPoint(); //获取直线起始点的坐标
            endPoint_line = FindRectCenterDlg::getLineEndPoint(); //获取直线终点坐标

            qDebug() << "下边缘起点x的坐标" <<startPoint_line.x<< "Y的坐标" <<startPoint_line.y;
            qDebug() << "下边缘终点x的坐标" <<endPoint_line.x<< "Y的坐标" <<endPoint_line.y;

            // ------------↓  寻找直线与图像边缘的交点
            lineImage = cv::Mat::zeros(image.size(), CV_8UC1); //创建一张空白灰度图像
            sobelImg  = FindRectCenterDlg::getsobelEdgesImg(); //获取'sobel'图像
            vector_rect = FindRectCenterDlg::getSelectAreaVec(); //获取选择区域容器

            //得到选择区域容器内最新矩形的宽和高
            int dx = vector_rect.back().rectEndPoint.x - vector_rect.back().rectStartPoint.x;
            int dy = vector_rect.back().rectEndPoint.y - vector_rect.back().rectStartPoint.y;

            //定义一个矩形的位置与尺寸
            cv::Rect box(vector_rect.back().rectStartPoint.x,
                         vector_rect.back().rectStartPoint.y, dx, dy);

            cv::line(lineImage, startPoint_line, endPoint_line, cv::Scalar(255, 255, 255), 1);
            cv::cvtColor(sobelImg, gray_SobelImg, cv::COLOR_BGR2GRAY);

            //寻找交点
            intersectionPoint_Line = FindRectCenterDlg::findIntersections(gray_SobelImg, lineImage, box);
            // ------------↑

            //保证绘制的直线与图像边缘有交点，然后存入下边缘线容器、包含所有直线的容器          
            if (intersectionPoint_Line.x != 0 && intersectionPoint_Line.y != 0)
            {
                cv::line(image, startPoint_line, endPoint_line, cv::Scalar(255, 0, 0), 1);
                cv::imshow("test", image);

                FindRectCenterDlg::setLineIntersectionPoint(intersectionPoint_Line);
                info_DownLine = FindRectCenterDlg::getLineInfo(); //'info_LeftLine'是否有数据？有
                FindRectCenterDlg::setDownLineVec(info_DownLine);
                FindRectCenterDlg::setAllLineVec(info_DownLine);

                //将绘制的直线与选取区域绑定在一起
                FindRectCenterDlg::setBindLineAndRect(info_DownLine, vector_rect.back());
                bindLineAndRect = FindRectCenterDlg::getBindLineAndRect();
                //将绘制的直线与选取区域绑定在一起的集合放入容器，下边
                FindRectCenterDlg::set_downLineAdddownSelectAreaVec(bindLineAndRect);
            }
            else
            {
                QMessageBox::information(NULL, "PROMPT(提示)", "无交点，请重新绘制");
            }
            selectAreaCount = 0;
            FindRectCenterDlg::setSelectAreaCount(selectAreaCount); //更新'count_SelectArea'的值
        }
    }
}


bool compareRect(const RectangleInfo& rect1, const RectangleInfo& rect2)
{
    return rect1.rectStartPoint  == rect2.rectStartPoint &&
           rect1.rectEndPoint    == rect2.rectEndPoint   &&
           rect1.rectCenterPoint == rect2.rectCenterPoint;
}

// 比较两条直线是否相同
bool compareLines(const LineInfo& line1, const LineInfo& line2)
{
    return line1.lineStartPoint    == line2.lineStartPoint &&
           line1.lineEndPoint      == line2.lineEndPoint &&
           line1.intersectionPoint == line2.intersectionPoint;
}


/** --------------@brief：撤销功能回调函数------------- **/
/** --------------@note： ------------- **/
static void unDo(int event,int x,int y,int flags,void *userdata)
{   
    //设置鼠标光标为箭头
    //QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
    cv::Mat *m_binImg  = static_cast<cv::Mat*>(userdata);

    static std::vector<RectangleInfo> vector_AllRect;
    static std::vector<RectangleInfo> vector_SelectArea;
    static std::vector<RectangleInfo> vector_EclusionArea;
    static std::vector<RectangleInfo> vector_ProcessedRect;

    static std::vector<LineInfo>      vector_AllLine;
    static std::vector<LineInfo>      vector_LeftLine;
    static std::vector<LineInfo>      vector_RightLine;
    static std::vector<LineInfo>      vector_UpLine;
    static std::vector<LineInfo>      vector_DownLine;
    static std::vector<LineInfo>      vector_ProcessedLine;

    vector_AllRect       = FindRectCenterDlg::getAllAreaVec();
    vector_SelectArea    = FindRectCenterDlg::getSelectAreaVec();
    vector_EclusionArea  = FindRectCenterDlg::getEclusionAreaVec();

    vector_AllLine    = FindRectCenterDlg::getAllLineVec();
    vector_LeftLine   = FindRectCenterDlg::getLeftLineVec();
    vector_RightLine  = FindRectCenterDlg::getRightLineVec();
    vector_UpLine     = FindRectCenterDlg::getUpLineVec();
    vector_DownLine   = FindRectCenterDlg::getDownLineVec();


    /*qDebug() << "vector_AllRect的容量" << vector_AllRect.size();
    qDebug() << "vector_SelectArea的容量" << vector_SelectArea.size();
    qDebug() << "vec_EclusionArea的容量" << vector_EclusionArea.size();

    qDebug() << "vector_AllLine的容量" << vector_AllLine.size();
    qDebug() << "vector_LeftLine的容量" << vector_LeftLine.size();
    qDebug() << "vector_RightLine的容量" << vector_RightLine.size();
    qDebug() << "vector_UpLine的容量" << vector_UpLine.size();
    qDebug() << "vector_DownLine的容量" << vector_DownLine.size();*/


    int minRectDistanceIndex = -1; //矩形容器编号
    int minLineDistanceIndex = -1; //直线容器编号
    int minRectDistance = 10;
    int minLineDistance = 5;

    if (event == cv::EVENT_LBUTTONDOWN)
    {
        //遍历容器中的每个矩形，在规定情况下'distance < minRectDistance'，找出要被删除的矩形
        for (int i = 0; i < vector_AllRect.size(); ++i)
        {
            //计算鼠标位置与绘制直线起点的距离
            double distance = abs(cv::norm(cv::Point(x, y) - vector_AllRect[i].rectEndPoint));
            //找出最小距离
            if(distance < minRectDistance)
            {
                minRectDistance = distance;
                minRectDistanceIndex = i; //记录当前最小距离的直线索引
                qDebug() << "i的值" << i;
            }
        }
        //遍历容器中的每条直线，在规定情况下'distance < minLineDistance'，找出要被删除的直线
        for (int i = 0; i < vector_AllLine.size(); ++i)
        {
            //计算鼠标位置与绘制直线起点的距离
            double distance = abs(cv::norm(cv::Point(x, y) - vector_AllLine[i].lineStartPoint));
            //找出最小距离
            if(distance < minLineDistance)
            {
                minLineDistance = distance;
                minLineDistanceIndex = i; //记录当前最小距离的直线索引
                //qDebug() << "i的值" << i;
            }
        }

        //'vec_ProcessedRect'为进行删除操作后保存的矩形
        vector_ProcessedRect = FindRectCenterDlg::updataAllRectInfo(minRectDistanceIndex,
                                                                    vector_AllRect,
                                                                    vector_SelectArea,
                                                                    vector_EclusionArea);

        //'vector_ProcessedLine'为进行删除操作后保存的直线
        vector_ProcessedLine = FindRectCenterDlg::updataAllLineInfo(minLineDistanceIndex,
                                                                    vector_AllLine,
                                                                    vector_LeftLine,
                                                                    vector_RightLine,
                                                                    vector_UpLine,
                                                                    vector_DownLine);

        vector_EclusionArea = FindRectCenterDlg::getEclusionAreaVec();

        /*qDebug() << "处理后区域" << vector_ProcessedRect.size();
        qDebug() << "处理后直线" << vector_ProcessedLine.size();
        qDebug() << "排除区域"  << vector_EclusionArea.size();*/

        cv::Mat image = cv::imread("D:/QT_Training/PXHForNick/binImg.jpg");
        //重新绘制矩形区域
        for (const auto& rect : vector_ProcessedRect)
        {
            bool found = false;
            for (const auto& rect1 : vector_EclusionArea)
            {
                if (compareRect(rect, rect1))
                {
                    // 如果在'vector_EclusionArea'中找到相同的矩形，绘制成红色
                    cv::rectangle(image, rect1.rectStartPoint, rect1.rectEndPoint, cv::Scalar(0, 0, 255), 2);
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                // 如果在'vector_EclusionArea'中没有找到相同的矩形，绘制成蓝色
                cv::rectangle(image, rect.rectStartPoint, rect.rectEndPoint, cv::Scalar(0, 255, 0), 2);
            }
        }
        //重新绘制直线
        for(const auto &line : vector_ProcessedLine)
        {
            cv::line(image, line.lineStartPoint, line.lineEndPoint, cv::Scalar(255, 0, 0), 1);
        }

        *m_binImg = image.clone();  // 或者使用 copyTo() 方法
        cv::imshow("test", image);
     }
}


/** --------------@brief：设置比例图像------------- **/
/** --------------@note： ------------- **/
void FindRectCenterDlg::setScaleImg(const cv::Mat &inputImg)
{
   m_scaleImg = inputImg;
}


/*--------------@brief：获取比例图像-------------*/
/*--------------@note： 静态成员函数-------------*/
cv::Mat FindRectCenterDlg::getScaleImg()
{
    return m_scaleImg;
}


/** --------------@brief：设置sobel图像------------- **/
/** --------------@note： 静态成员函数------------- **/
void FindRectCenterDlg::setsobelEdgesImg(const cv::Mat &inputImg)
{
    m_sobelEdges = inputImg;
}


/** --------------@brief：获取sobel图像------------- **/
/** --------------@note： 静态成员函数------------- **/
cv::Mat FindRectCenterDlg::getsobelEdgesImg()
{
    return m_sobelEdges;
}


/*--------------@brief：获取'WinName'-------------*/
/*--------------@note： 静态成员函数-------------*/
std::string FindRectCenterDlg::getWinName()
{
    return winName;
}


/** --------------@brief：设置筛选区域个数变量的值------------- **/
/** --------------@note： 静态成员函数------------- **/
void FindRectCenterDlg::setExclusionCount(int excluCount)
{
    exclusionCount = excluCount;
}


/** --------------@brief：设置鼠标起始点的坐标------------- **/
/** --------------@note： 静态成员函数------------- **/
void FindRectCenterDlg::setStartPoint_Mouse(const cv::Point &startPointMouse)
{
    startPoint_Mouse = startPointMouse;
}


/** --------------@brief：设置鼠标终点的坐标------------- **/
/** --------------@note： 静态成员函数------------- **/
void FindRectCenterDlg::setEndPonint_Mouse(const cv::Point &endPointMouse)
{
    endPoint_Mouse = endPointMouse;
}


/** --------------@brief：设置选择区域个数变量的值------------- **/
/** --------------@note： 静态成员函数------------- **/
void FindRectCenterDlg::setSelectAreaCount(int count)
{
    count_SelectArea = count;
}


/*--------------@brief：获取筛选区域的数量-------------*/
/*--------------@note： 静态成员函数-------------*/
int FindRectCenterDlg::getExclusionCount()
{
    return exclusionCount;
}


/*--------------@brief：获取鼠标起始点坐标-------------*/
/*--------------@note： 静态成员函数-------------*/
cv::Point FindRectCenterDlg::getstartPoint_Mouse()
{
    return startPoint_Mouse;
}


/*--------------@brief：获取鼠标终点坐标-------------*/
/*--------------@note： 静态成员函数-------------*/
cv::Point FindRectCenterDlg::getendPonint_Mouse()
{
    return endPoint_Mouse;
}


/** --------------@brief：获取选择区域的数量------------- **/
/** --------------@note： 静态成员函数------------- **/
int FindRectCenterDlg::getSelectAreaCount()
{
    return count_SelectArea;
}


/*--------------@brief：设置矩形的起点坐标-------------*/
/*--------------@note： 静态成员函数-------------*/
void FindRectCenterDlg::setRectStartPoint(const cv::Point &startPoint)
{
    m_rectInfo.rectStartPoint = startPoint;
}


/*--------------@brief：设置矩形的终点坐标-------------*/
/*--------------@note： 静态成员函数-------------*/
void FindRectCenterDlg::setRectEndPoint(const cv::Point &endPoint)
{
    m_rectInfo.rectEndPoint = endPoint;
}


/*--------------@brief：设置矩形的中心点坐标-------------*/
/*--------------@note： 静态成员函数-------------*/
void FindRectCenterDlg::setRectCenterPoint(const cv::Point &centerPoint)
{
    m_rectInfo.rectCenterPoint = centerPoint;
}


/*--------------@brief：获取矩形的起点坐标-------------*/
/*--------------@note： 静态成员函数-------------*/
cv::Point FindRectCenterDlg::getRectStartPoint()
{
    return m_rectInfo.rectStartPoint;
}


/*--------------@brief：获取矩形的终点坐标-------------*/
/*--------------@note： 静态成员函数-------------*/
cv::Point FindRectCenterDlg::getRectEndPoint()
{
    return m_rectInfo.rectEndPoint;

}


/*--------------@brief：获取矩形的中心点坐标-------------*/
/*--------------@note： 静态成员函数-------------*/
cv::Point FindRectCenterDlg::getRectCenterPoint()
{
    return m_rectInfo.rectCenterPoint;
}


/** --------------@brief：获取矩形------------- **/
/** --------------@note： 静态成员函数------------- **/
RectangleInfo FindRectCenterDlg::getRectInfo()
{
    return m_rectInfo;
}


/** --------------@brief：设置直线的起点坐标------------- **/
/** --------------@note： 静态成员函数------------- **/
void FindRectCenterDlg::setLineStartPoint(const cv::Point &startPoint)
{
    m_lineInfo.lineStartPoint = startPoint;
}


/** --------------@brief：设置直线的终点坐标------------- **/
/** --------------@note： 静态成员函数------------- **/
void FindRectCenterDlg::setLineEndPoint(const cv::Point &endPoint)
{
    m_lineInfo.lineEndPoint = endPoint;
}


/** --------------@brief：设置直线的交点坐标------------- **/
/** --------------@note： 静态成员函数------------- **/
void FindRectCenterDlg::setLineIntersectionPoint(const cv::Point &intersectionPoint)
{
    m_lineInfo.intersectionPoint = intersectionPoint;
}


/** --------------@brief：获取直线的起点坐标------------- **/
/** --------------@note： 静态成员函数------------- **/
cv::Point FindRectCenterDlg::getLineStartPoint()
{
    return m_lineInfo.lineStartPoint;
}


/** --------------@brief：获取直线的终点坐标------------- **/
/** --------------@note： 静态成员函数------------- **/
cv::Point FindRectCenterDlg::getLineEndPoint()
{
    return m_lineInfo.lineEndPoint;
}


/** --------------@brief：获取直线的交点坐标------------- **/
/** --------------@note： 静态成员函数------------- **/
cv::Point FindRectCenterDlg::getLineIntersectionPoint()
{
    return m_lineInfo.intersectionPoint;
}


/** --------------@brief：获取直线------------- **/
/** --------------@note： ------------- **/
LineInfo FindRectCenterDlg::getLineInfo()
{
    return m_lineInfo;
}


/** --------------@brief：设置选择区域的集合------------- **/
/** --------------@note： 静态成员函数------------- **/
void FindRectCenterDlg::setSelectAreaVec(const RectangleInfo &selectArea)
{
    m_allInfoCollection.vec_SelectArea.push_back(selectArea);
}


/** --------------@brief：设置筛选区域的集合------------- **/
/** --------------@note： 静态成员函数------------- **/
void FindRectCenterDlg::setEclusionAreaVec(const RectangleInfo &exclusionArea)
{
    m_allInfoCollection.vec_EclusionArea.push_back(exclusionArea);
}


/** --------------@brief：设置所有矩形的容器------------- **/
/** --------------@note： 静态成员函数------------- **/
void FindRectCenterDlg::setAllAreaVec(const RectangleInfo &allRcet)
{
    m_allInfoCollection.vec_AllRect.push_back(allRcet);
}


/** --------------@brief：获取选择区域的集合------------- **/
/** --------------@note： 静态成员函数------------- **/
std::vector<RectangleInfo> FindRectCenterDlg::getSelectAreaVec()
{
    return m_allInfoCollection.vec_SelectArea;
}


/** --------------@brief：获取筛选区域的集合------------- **/
/** --------------@note： 静态成员函数------------- **/
std::vector<RectangleInfo> FindRectCenterDlg::getEclusionAreaVec()
{
    return m_allInfoCollection.vec_EclusionArea;
}


/** --------------@brief：获取所有矩形的容器------------- **/
/** --------------@note： 静态成员函数------------- **/
std::vector<RectangleInfo> FindRectCenterDlg::getAllAreaVec()
{
    return m_allInfoCollection.vec_AllRect;
}


/** --------------@brief：设置左边缘线的集合------------- **/
/** --------------@note： 静态成员函数------------- **/
void FindRectCenterDlg::setLeftLineVec(const LineInfo &leftLineVec)
{
    m_allInfoCollection.vec_LeftLine.push_back(leftLineVec);
}


/** --------------@brief：设置右边缘线的集合------------- **/
/** --------------@note： 静态成员函数------------- **/
void FindRectCenterDlg::setRightLineVec(const LineInfo &rightLineVec)
{
    m_allInfoCollection.vec_RightLine.push_back(rightLineVec);
}


/** --------------@brief：设置上边缘线的容器------------- **/
/** --------------@note： 静态成员函数------------- **/
void FindRectCenterDlg::setUpLineVec(const LineInfo &upLineVec)
{
    m_allInfoCollection.vec_UpLine.push_back(upLineVec);
}


/** --------------@brief：设置下边缘线的容器------------- **/
/** --------------@note： 静态成员函数------------- **/
void FindRectCenterDlg::setDownLineVec(const LineInfo &downLineVec)
{
    m_allInfoCollection.vec_DownLine.push_back(downLineVec);
}


/** --------------@brief：设置包含所有绘制直线的容器------------- **/
/** --------------@note： 静态成员函数------------- **/
void FindRectCenterDlg::setAllLineVec(const LineInfo &allLineVec)
{
    m_allInfoCollection.vec_AllDrawLine.push_back(allLineVec);
}


/** --------------@brief：获取左边缘线的集合------------- **/
/** --------------@note： 静态成员函数------------- **/
std::vector<LineInfo> FindRectCenterDlg::getLeftLineVec()
{
    return m_allInfoCollection.vec_LeftLine;
}


/** --------------@brief：获取右边缘线的集合------------- **/
/** --------------@note： 静态成员函数------------- **/
std::vector<LineInfo> FindRectCenterDlg::getRightLineVec()
{
    return m_allInfoCollection.vec_RightLine;
}


/** --------------@brief：获取上边缘线的集合------------- **/
/** --------------@note： 静态成员函数------------- **/
std::vector<LineInfo> FindRectCenterDlg::getUpLineVec()
{
    return m_allInfoCollection.vec_UpLine;
}


/** --------------@brief：获取下边缘线的容器------------- **/
/** --------------@note： 静态成员函数------------- **/
std::vector<LineInfo> FindRectCenterDlg::getDownLineVec()
{
    return m_allInfoCollection.vec_DownLine;
}


/** --------------@brief：获取所有绘制直线的容器------------- **/
/** --------------@note： 静态成员函数------------- **/
std::vector<LineInfo> FindRectCenterDlg::getAllLineVec()
{
    return m_allInfoCollection.vec_AllDrawLine;
}


/** --------------@brief：设置拟合直线集合------------- **/
/** --------------@note： 静态成员函数------------- **/
void FindRectCenterDlg::setFitLineVec(const FitLineInfo &fitLineVec)
{
    m_allInfoCollection.vec_FitLine.push_back(fitLineVec);
}


/** --------------@brief：获取拟合直线集合------------- **/
/** --------------@note： 静态成员函数------------- **/
std::vector<FitLineInfo> FindRectCenterDlg::getFitLineVec()
{
    return m_allInfoCollection.vec_FitLine;
}


/** --------------@brief：设置绘制的直线与选取区域绑定在一起的集合------------- **/
/** --------------@note： 静态成员函数------------- **/
void FindRectCenterDlg::setBindLineAndRect(const LineInfo &lineInfo, const RectangleInfo &rectangleInfo)
{
    m_BindLineAndRect.lineInfo      = lineInfo;
    m_BindLineAndRect.rectangleInfo = rectangleInfo;
}


/** --------------@brief：获取绘制的直线与选取区域绑定在一起的集合------------- **/
/** --------------@note： 静态成员函数------------- **/
BindLineAndRect FindRectCenterDlg::getBindLineAndRect()
{
    return m_BindLineAndRect;
}


/** --------------@brief：设置左边缘线与左选择区域集合的容器------------- **/
/** --------------@note： 静态成员函数------------- **/
void FindRectCenterDlg::set_leftLineAddleftSelectAreaVec(const BindLineAndRect &leftLineAddleftSelectAreaVec)
{
    m_allInfoCollection.vec_leftLine_leftSelectArea.push_back(leftLineAddleftSelectAreaVec);
}


/** --------------@brief：设置右边缘线与右选择区域集合的容器------------- **/
/** --------------@note： 静态成员函数------------- **/
void FindRectCenterDlg::set_rightLineAddrightSelectAreaVec(const BindLineAndRect &rightLineAddrightSelectAreaVec)
{
    m_allInfoCollection.vec_rightLine_rightSelectArea.push_back(rightLineAddrightSelectAreaVec);
}


/** --------------@brief：设置上边缘线与上选择区域集合的容器------------- **/
/** --------------@note： 静态成员函数------------- **/
void FindRectCenterDlg::set_upLineAddupSelectAreaVec(const BindLineAndRect &upLineAddupSelectAreaVec)
{
    m_allInfoCollection.vec_upLine_upSelectArea.push_back(upLineAddupSelectAreaVec);
}


/** --------------@brief：设置下边缘线与下选择区域集合的容器------------- **/
/** --------------@note： 静态成员函数------------- **/
void FindRectCenterDlg::set_downLineAdddownSelectAreaVec(const BindLineAndRect &downLineAdddownSelectAreaVec)
{
    m_allInfoCollection.vec_downLine_downSelectArea.push_back(downLineAdddownSelectAreaVec);
}


/** --------------@brief：获取左边缘线与左选择区域集合的容器------------- **/
/** --------------@note： 静态成员函数------------- **/
std::vector<BindLineAndRect> FindRectCenterDlg::get_leftLineAddleftSelectAreaVec()
{
    return m_allInfoCollection.vec_leftLine_leftSelectArea;

}


/** --------------@brief：获取右边缘线与右选择区域集合的容器------------- **/
/** --------------@note： 静态成员函数------------- **/
std::vector<BindLineAndRect> FindRectCenterDlg::get_rightLineAddrightSelectAreaVec()
{
    return m_allInfoCollection.vec_rightLine_rightSelectArea;

}


/** --------------@brief：获取上边缘线与上选择区域集合的容器------------- **/
/** --------------@note： 静态成员函数------------- **/
std::vector<BindLineAndRect> FindRectCenterDlg::get_upLineAddupSelectAreaVec()
{
    return m_allInfoCollection.vec_upLine_upSelectArea;
}


/** --------------@brief：获取下边缘线与下选择区域集合的容器------------- **/
/** --------------@note： 静态成员函数------------- **/
std::vector<BindLineAndRect> FindRectCenterDlg::get_downLineAdddownSelectAreaVec()
{
    return m_allInfoCollection.vec_downLine_downSelectArea;
}


/** --------------@brief：获取'AllInfoCollection'信息------------- **/
/** --------------@note： ------------- **/
AllInfoCollection &FindRectCenterDlg::getAllInfoCollection()
{
    return m_allInfoCollection;
}



/** --------------@brief：寻找直线与图像边缘的交点------------- **/
/** --------------@note： 静态成员函数------------- **/
cv::Point FindRectCenterDlg::findIntersections(const cv::Mat &grayImg, const cv::Mat &zerosImg, const cv::Rect &selectArea)
{
    cv::Mat mask = cv::Mat::zeros(grayImg.size(), CV_8UC1);
    mask(selectArea).setTo(255); //将选择区域设置为白色

    static std::vector<cv::Point> intersectionPoints; //存储非零像素点坐标
    static std::vector<cv::Point> intersections; //

    cv::findNonZero(grayImg & zerosImg & mask, intersectionPoints); //将非零像素点坐标存储在'intersectionPoints'

    if (intersectionPoints.size() == 0)
    {
        return {0, 0};
    }
    else
    {
        for (const auto& intersectionPoint : intersectionPoints)
        {
            intersections.push_back({(int)(intersectionPoint.x), (int)(intersectionPoint.y)});
        }
    }

    cv::Point average = {0, 0};
    int count = 0;
    int count2 = 0;

    static std::vector<RectangleInfo> vector_eclusionArea;
    vector_eclusionArea = FindRectCenterDlg::getEclusionAreaVec(); //获取筛选区域集合

    for (int i = 0; i < (int)intersections.size(); i++)
    {
        if ((int)vector_eclusionArea.size() != 0)
        {
            //判断交点是否在筛选区域内
            for (int j = 0; j < (int)vector_eclusionArea.size(); j++)
            {
                //计算非零像素点坐标与筛选区域中心点坐标的差
                int dx = abs(intersections[i].x - vector_eclusionArea[j].rectCenterPoint.y);
                int dy = abs(intersections[i].y - vector_eclusionArea[j].rectCenterPoint.y);
                //int dx = abs(intersections[i].x - Select_Rect.sxRect[j].RectCenter.x);
                //int dy = abs(intersections[i].y - Select_Rect.sxRect[j].RectCenter.y);
                //计算筛选区域的半宽和半高
                int halfHeight_EclusionArea = abs(vector_eclusionArea[j].rectEndPoint.y - vector_eclusionArea[j].rectStartPoint.y) / 2;
                int halfWidth_EclusionArea  = abs(vector_eclusionArea[j].rectEndPoint.x - vector_eclusionArea[j].rectStartPoint.x) / 2;

                if (dx > halfWidth_EclusionArea | dy > halfHeight_EclusionArea)
                {
                    average.x += intersections[i].x;
                    average.y += intersections[i].y;
                    count++;
                    count2++;
                }
            }
        }
        else
        {
            average.x += intersections[i].x;
            average.y += intersections[i].y;
            count++;
        }
    }

    if (count2 != (int)vector_eclusionArea.size() * (int)intersections.size() && count2 == 0)
    {
        qDebug() << "没有交点" << endl;
        intersectionPoints.clear();
        intersections.clear();
        return {0, 0};
    }
    else
    {
        average.x /= count;
        average.y /= count;
        qDebug() <<"交点坐标为："<<average.x <<","<< average.y;
        intersectionPoints.clear();
        intersections.clear();
        return average;
    }
}


/** --------------@brief：进行删除操作后更新所有矩形信息------------- **/
/** --------------@note： 静态成员函数------------- **/
std::vector<RectangleInfo> FindRectCenterDlg::updataAllRectInfo(int minRectDistanceIndex,
                                                                std::vector<RectangleInfo> &vector_AllRect,
                                                                std::vector<RectangleInfo> &vector_SelectArea,
                                                                std::vector<RectangleInfo> &vec_EclusionArea)
{
    AllInfoCollection &allInfoCollection = FindRectCenterDlg::getAllInfoCollection();

    //删除符合条件的矩形
    if(minRectDistanceIndex != -1)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(NULL, "Confirmation",
                                      "是否要删除矩形?",
                                      QMessageBox::Yes|QMessageBox::No);
        if(reply == QMessageBox::Yes)
        {
            RectangleInfo removedRect = vector_AllRect[minRectDistanceIndex]; //获取被删除的矩形
            vector_AllRect.erase(vector_AllRect.begin() + minRectDistanceIndex); //删除矩形
            allInfoCollection.vec_AllRect = vector_AllRect; //更新包含所有矩形的容器

            //查找在'vector_SelectArea'中与被删除的矩形相同的元素，并删除
            auto ite_SelectArea = std::find_if(vector_SelectArea.begin(), vector_SelectArea.end(), [&](const RectangleInfo& rect)
                                 {
                                   return compareRect(rect, removedRect);
                                                                         });
            if (ite_SelectArea != vector_SelectArea.end())
            {
                vector_SelectArea.erase(ite_SelectArea);
                allInfoCollection.vec_SelectArea = vector_SelectArea; //更新'vector_SelectArea'容器
            }

            //查找在'vec_EclusionArea'中与被删除的矩形相同的元素，并删除
            auto ite_EclusionArea = std::find_if(vec_EclusionArea.begin(), vec_EclusionArea.end(), [&](const RectangleInfo& rect)
                                 {
                                   return compareRect(rect, removedRect);
                                                                         });
            if (ite_EclusionArea != vec_EclusionArea.end())
            {
                vec_EclusionArea.erase(ite_EclusionArea);
                allInfoCollection.vec_EclusionArea = vec_EclusionArea; //更新'vec_EclusionArea'容器
            }
        }
        else
        {
            QMessageBox::information(NULL, "PROMPT(提示)", "请继续绘制");
        }
    }
    return allInfoCollection.vec_AllRect;
    //qDebug() << "vector_AllRect的容量为:" << vector_AllRect.size();
    //qDebug() << "vector_SelectArea的容量为:" << vector_SelectArea.size();
}


/** --------------@brief：删除直线后更新图像，更新容器------------- **/
/** --------------@note： 静态成员函数------------- **/
std::vector<LineInfo> FindRectCenterDlg::updataAllLineInfo(int minLineDistanceIndex,
                                                           std::vector<LineInfo> &vec_AllDrawLine,
                                                           std::vector<LineInfo> &vec_LeftLine,
                                                           std::vector<LineInfo> &vec_RightLine,
                                                           std::vector<LineInfo> &vec_UpLine,
                                                           std::vector<LineInfo> &vec_DownLine)
{
    AllInfoCollection &allInfoCollection = FindRectCenterDlg::getAllInfoCollection();

    if(minLineDistanceIndex != -1)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(NULL, "Confirmation",
                                      "是否要删除直线?",
                                      QMessageBox::Yes|QMessageBox::No);
        if(reply == QMessageBox::Yes)
        {
            LineInfo removedLine = vec_AllDrawLine[minLineDistanceIndex]; //获取被删除的直线
            vec_AllDrawLine.erase(vec_AllDrawLine.begin() + minLineDistanceIndex); //删除矩形
            allInfoCollection.vec_AllDrawLine = vec_AllDrawLine; //更新包含所有直线的容器

            //查找在'vec_LeftLine'中与被删除的直线相同的元素，并删除
            auto ite_LeftLine = std::find_if(vec_LeftLine.begin(), vec_LeftLine.end(), [&](const LineInfo& leftLine)
                                 {
                                   return compareLines(leftLine, removedLine);
                                                                         });
            if (ite_LeftLine != vec_LeftLine.end())
            {
                vec_LeftLine.erase(ite_LeftLine);
                allInfoCollection.vec_LeftLine = vec_LeftLine; //更新'vec_LeftLine'容器
            }
            //查找在'vec_RightLine'中与被删除的直线相同的元素，并删除
            auto ite_RightLine = std::find_if(vec_RightLine.begin(), vec_RightLine.end(), [&](const LineInfo& rightLine)
                                 {
                                   return compareLines(rightLine, removedLine);
                                                                         });
            if (ite_RightLine != vec_RightLine.end())
            {
                vec_RightLine.erase(ite_RightLine);
                allInfoCollection.vec_RightLine = vec_RightLine; //更新'vec_RightLine'容器
            }
            //查找在'vec_UpLine'中与被删除的直线相同的元素，并删除
            auto ite_UpLine = std::find_if(vec_UpLine.begin(), vec_UpLine.end(), [&](const LineInfo& upLine)
                                 {
                                   return compareLines(upLine, removedLine);
                                                                         });
            if (ite_UpLine != vec_UpLine.end())
            {
                vec_UpLine.erase(ite_UpLine);
                allInfoCollection.vec_UpLine = vec_UpLine; //更新'vec_UpLine'容器
            }
            //查找在'vec_DownLine'中与被删除的直线相同的元素，并删除
            auto ite_DownLine = std::find_if(vec_DownLine.begin(), vec_DownLine.end(), [&](const LineInfo& downLine)
                                 {
                                   return compareLines(downLine, removedLine);
                                                                         });
            if (ite_DownLine != vec_DownLine.end())
            {
                vec_DownLine.erase(ite_DownLine);
                allInfoCollection.vec_DownLine = vec_DownLine; //更新'vec_DownLine'容器
            }
        }
        else
        {
            QMessageBox::information(NULL, "PROMPT(提示)", "请继续绘制直线");
        }
    }
    return allInfoCollection.vec_AllDrawLine;
}



/*--------------@brief：Sobel边缘检测-------------*/
/*--------------@note： -------------*/
bool FindRectCenterDlg::mySobel(cv::Mat &inputImg)
{
    //static cv::Mat sobelImg;
    //static cv::Mat m_srcSobelEdges;
    //sobelImg = FindRectCenterDlg::getsobelEdgesImg();

    bool isTrueVal = true;
    //使用'Sobel'算子检测图像中的边缘
    cv::Mat grad_x, grad_y;
    cv::Sobel(inputImg, grad_x, CV_16S, 1, 0);
    cv::Sobel(inputImg, grad_y, CV_16S, 0, 1);
    cv::convertScaleAbs(grad_x, grad_x);
    cv::convertScaleAbs(grad_y, grad_y);
    cv::addWeighted(grad_x, 0.5, grad_y, 0.5, 0, m_sobelEdges);

    FindRectCenterDlg::setsobelEdgesImg(m_sobelEdges);

    //cv::cvtColor(sobelImg, m_srcSobelEdges, cv::COLOR_BGR2GRAY);

    //FindRectCenterDlg::setsobelEdgesImg(m_srcSobelEdges);

    if(m_sobelEdges.data == 0)
    {
        isTrueVal = false;
    }

    return isTrueVal;
}


/*--------------@brief：图像二值化-------------*/
/*--------------@note： -------------*/
bool FindRectCenterDlg::binImageFunc()
{
    m_binImg.release();
    bool isTrueVal = false;
    /*double minthresholdnum = 0.0;
    double maxthresholdnum = 1.0;
    if(iThreshold !=0)
    {
        double tempthresholdnum;
        tempthresholdnum = iThreshold;
        if(minthresholdnum<tempthresholdnum && tempthresholdnum<maxthresholdnum)
        {
            iBinThreshNum = int(tempthresholdnum*255);
        }
        else if (1<=tempthresholdnum && tempthresholdnum<=255)
        {
            iBinThreshNum = int(tempthresholdnum);
        }else
        {
            QMessageBox::critical(this,str_cn("错误信息"),str_cn("请输入正确的阈值或比例阈值！"));
            isTrueVal = true;
        }
    }*/

    qDebug()<<"iBinThreshNum:"<<iBinThreshNum<<endl;

    if(isTrueVal)
    {
        return isTrueVal;
    }
    //二值化处理  THRESH_BINARY:当前点值大于阈值时，取Maxval,也就是第四个参数，下面再不说明，否则设置为0
    cv::threshold(m_sobelEdges, m_binImg, iBinThreshNum, 255, cv::THRESH_BINARY);
    cv::imwrite("D:/QT_Training/PXHForNick/binImg.jpg", m_binImg);

    //二值图
//    if(m_binImg.channels()==1)
//    {
//        cv::cvtColor(m_binImg, m_sobelBGREdges, cv::COLOR_GRAY2BGR);
//    }
//    else if(m_binImg.channels()==3)
//    {
//        m_sobelBGREdges=m_binImg.clone();
//    }

    //cv::imshow(winName,m_sobelBGREdges);
//    cv::cvtColor(m_sobelBGREdges, m_srcSobelEdges, cv::COLOR_BGR2GRAY);
//    m_UpImage=m_sobelBGREdges;

    return isTrueVal;
}


/*--------------@brief：将opencv显示窗口嵌入到'widget'-------------*/
/*--------------@note： -------------*/
void FindRectCenterDlg::namedWindowToWidget(std::string namedWindowTitle, QWidget *widget)
{
    HWND hwnd = (HWND)cvGetWindowHandle(namedWindowTitle.c_str());
    HWND hparent =::GetParent(hwnd);
    ::SetParent(hwnd, (HWND)widget->winId());
    ::ShowWindow(hparent, SW_HIDE);
}


/** --------------@brief：求得拟合直线的斜率和截距------------- **/
/** --------------@note： 最小二乘法------------- **/
FitLineInfo FindRectCenterDlg::fitLine(std::vector<cv::Point> &pointsFp)
{
    int n = pointsFp.size(); //点的个数
    double x_sum = 0; // x坐标之和
    double y_sum = 0; // y坐标之和
    double xy_sum = 0; // x*y之和
    double x2_sum = 0; // x^2之和
    //遍历所有点，计算各项和
    for (cv::Point p : pointsFp)
    {
        x_sum += p.x;
        y_sum += p.y;
        xy_sum += p.x * p.y;
        x2_sum += p.x * p.x;
    }
    //根据公式计算斜率和截距
    double k = (n * xy_sum - x_sum * y_sum) / (n * x2_sum - x_sum * x_sum);
    double b = (y_sum - k * x_sum) / n;
    qDebug() << "斜率:" << k << " 截距:" << b;
    //返回拟合的直线
    return FitLineInfo(k, b);
}


/** --------------@brief：获取两条直线的交点------------- **/
/** --------------@note： ------------- **/
cv::Point FindRectCenterDlg::getLineIntersection(FitLineInfo &fp1, FitLineInfo &fp2)
{
    //交点的坐标
    cv::Point tempIntersection;
    //根据公式求x
    tempIntersection.x = (fp2.b - fp1.b) / (fp1.k - fp2.k);
    //根据公式求y
    tempIntersection.y = fp1.k * tempIntersection.x + fp1.b;
    qDebug() << "The intersection is (" << tempIntersection.x << ", " << tempIntersection.y << ")" << endl;
    return tempIntersection;
}


/** --------------@brief：求得器件的中心点------------- **/
/** --------------@note： 四条拟合直线对角线的交点------------- **/
cv::Point FindRectCenterDlg::findCenter(Line &fp1, Line &fp2)
{
    cv::Point p;
    double a1 = fp1.p2.y - fp1.p1.y;
    double b1 = fp1.p1.x - fp1.p2.x;
    double c1 = a1 * fp1.p1.x + b1 * fp1.p1.y;

    double a2 = fp2.p2.y - fp2.p1.y;
    double b2 = fp2.p1.x - fp2.p2.x;
    double c2 = a2 * fp2.p1.x + b2 * fp2.p1.y;

    double determinant = a1 * b2 - a2 * b1;

    if (determinant == 0)
    {
        qDebug() << "Lines are parallel" << endl;
        return p;
    }
    else
    {
        p.x = (b2 * c1 - b1 * c2) / determinant;
        p.y = (a1 * c2 - a2 * c1) / determinant;
        return p;
    }

}


/** --------------@brief：将坐标放入Json文件------------- **/
/** --------------@note： ------------- **/
QJsonObject FindRectCenterDlg::pointToJson(const cv::Point &point)
{
    QJsonObject jsonObject;
    jsonObject["x"] = point.x;
    jsonObject["y"] = point.y;
    return jsonObject;
}


/** --------------@brief：将筛选区域放入Json文件------------- **/
/** --------------@note： ------------- **/
QJsonObject FindRectCenterDlg::eclusionAreaToJson(const RectangleInfo &item)
{
    QJsonObject jsonObject;
    jsonObject["EclRectStart"]  = pointToJson(item.rectStartPoint);
    jsonObject["EclRectEnd"]    = pointToJson(item.rectEndPoint);
    jsonObject["EclRectCenter"] = pointToJson(item.rectCenterPoint);
    return jsonObject;
}


/** --------------@brief：将选择区域放入Json文件------------- **/
/** --------------@note： ------------- **/
QJsonObject FindRectCenterDlg::selectAreaToJson(const RectangleInfo &item)
{
    QJsonObject jsonObject;
    jsonObject["SelRectStart"]  = pointToJson(item.rectStartPoint);
    jsonObject["SelRectEnd"]    = pointToJson(item.rectEndPoint);
    jsonObject["SelRectCenter"] = pointToJson(item.rectCenterPoint);
    return jsonObject;
}


/** --------------@brief：将绘制的直线和与之对应的选择区域存入Json文件------------- **/
/** --------------@note： ------------- **/
QJsonObject FindRectCenterDlg::bindLineAndRectToJson(const BindLineAndRect &item)
{
    QJsonObject jsonObject;
    jsonObject["RectStart"]    = pointToJson(item.rectangleInfo.rectStartPoint);
    jsonObject["RectEnd"]      = pointToJson(item.rectangleInfo.rectEndPoint);
    jsonObject["RectCenter"]   = pointToJson(item.rectangleInfo.rectCenterPoint);
    jsonObject["LineStart"]    = pointToJson(item.lineInfo.lineStartPoint);
    jsonObject["LineEnd"]      = pointToJson(item.lineInfo.lineEndPoint);
    jsonObject["intersection"] = pointToJson(item.lineInfo.intersectionPoint);
    return jsonObject;
}


/** --------------@brief：将所有直线存入Json文件------------- **/
/** --------------@note： ------------- **/
QJsonObject FindRectCenterDlg::allLineToJson(const LineInfo &item)
{
    QJsonObject jsonObject;
    jsonObject["LineStart"]    = pointToJson(item.lineStartPoint);
    jsonObject["LineEnd"]      = pointToJson(item.lineEndPoint);
    jsonObject["LineIntersection"] = pointToJson(item.intersectionPoint);

    return jsonObject;
}


/** --------------@brief：生成Json文件------------- **/
/** --------------@note： 存入的信息有筛选区域、绘制的直线和选择区域------------- **/
void FindRectCenterDlg::saveToJson(const std::vector<RectangleInfo> &eclusionAreaVec,
                                   const std::vector<RectangleInfo> &selectAreaVec,
                                   const std::vector<LineInfo> &allDrawLineVec,
                                   const QString &fileName)
{
    QJsonObject jsonObject;
    QJsonArray  jsonArray_eclusionArea;
    QJsonArray  jsonArray_selectArea;
    QJsonArray  jsonArray_allLine;

    //存入筛选区域
    for (const RectangleInfo &item : eclusionAreaVec)
    {
         jsonArray_eclusionArea.append(eclusionAreaToJson(item));
    }
    jsonObject["EclusionAreaVector"] = jsonArray_eclusionArea;

    //存入选择区域
    for (const RectangleInfo &item : selectAreaVec)
    {
         jsonArray_selectArea.append(selectAreaToJson(item));
    }
    jsonObject["SelectAreaVector"] = jsonArray_selectArea;

    //存入绘制的直线
    for (const LineInfo &item : allDrawLineVec)
    {
         jsonArray_allLine.append(allLineToJson(item));
    }
    jsonObject["AllLineVector"] = jsonArray_allLine;

    QJsonDocument jsonDoc(jsonObject);
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly))
    {
        file.write(jsonDoc.toJson());
    }
}


/** --------------@brief：生成Json文件------------- **/
/** --------------@note： 存入的信息有筛选区域、绘制的直线和选择区域------------- **/
/*void FindRectCenterDlg::saveToJson(const std::vector<RectangleInfo> &RectVector,
                                   const std::vector<std::vector<BindLineAndRect>> &RectLineVectors,
                                   const QString &fileName)
{
    QJsonObject jsonObject;
    QJsonArray  jsonArray;

    //存入筛选区域的信息
    for (const RectangleInfo &item : RectVector)
    {
         jsonArray.append(eclusionAreaToJson(item));
    }
    jsonObject["RectVector"] = jsonArray;

    //将绘制的直线和与之对应的选择区域存入Json
    QJsonArray jsonArray_2;
    for (const std::vector<BindLineAndRect> &myVector : RectLineVectors)
    {
        QJsonArray vectorArray;
        for (const BindLineAndRect &item : myVector)
        {
            vectorArray.append(bindLineAndRectToJson(item));
        }
        jsonArray_2.append(vectorArray);
    }

    jsonObject["RectLineVectors"] = jsonArray_2;

    QJsonDocument jsonDoc(jsonObject);
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly))
    {
        file.write(jsonDoc.toJson());
    }

}*/


/*--------------@brief：接收'cameradialog'界面传过来的仰望相机图像-------------*/
/*--------------@note： -------------*/
void FindRectCenterDlg::receiveUpImg(cv::Mat UpImg, int index_Img)
{
    isUpImgorDownImg = index_Img; //0仰望，1俯视
    m_UpImage = UpImg;
    cv::namedWindow(winName);

    ui->widgetPicture->setMinimumSize(m_UpImage.cols+60,m_UpImage.rows+60);
   // ui->widgetColor->setMinimumSize(imgOrigin.cols+60,imgOrigin.rows+60);
   // ui->widgetColor->hide();
    ui->scrollArea->widget()->setMinimumSize(m_UpImage.cols+60,m_UpImage.rows+60);

    cv::imshow(winName,m_UpImage);
    namedWindowToWidget(winName,ui->widgetPicture);

//    g_iZoom = 1;//初始缩放值为1，表示原图
//    m_scaleImg = m_UpImage;

//    cv::setMouseCallback(winName, moveImg, (void*)(&m_scaleImg)); //鼠标事件
}


/*--------------@brief：对图像进行预处理，sobel+二值化-------------*/
/*--------------@note： -------------*/
void FindRectCenterDlg::on_btnPreProcess_clicked()
{
    if(m_UpImage.data)
    {
        bool isSobelFlag = mySobel(m_UpImage);
        if(isSobelFlag)
        {
            QMessageBox::information(NULL, "PROMPT(提示)", "Sobel边缘检测成功");
        }
        else
        {
            QMessageBox::information(NULL, "PROMPT(提示)", "Sobel边缘检测失败");
        }
    }
    else
    {
        QMessageBox::information(NULL, "PROMPT(提示)", "未获取原始图像信息");
    }

    if(m_sobelEdges.data)
    {
        bool isBinFlag = binImageFunc();
        if(isBinFlag)
        {
            QMessageBox::information(NULL, "PROMPT(提示)", "二值化失败");
        }
        else
        {
            QMessageBox::information(NULL, "PROMPT(提示)", "二值化成功");
            cv::imshow("test", m_binImg);
            m_scaleImg = m_binImg;
            cv::setMouseCallback(winName, moveImg, (void*)(&m_scaleImg)); //鼠标事件
            ui->btnExcludeProcess->setEnabled(true); //使能'排除区域'按钮
            ui->btnPreProcess->setEnabled(false); //禁用'图像预处理'按钮
        }
    }
    else
    {
        QMessageBox::information(NULL, "PROMPT(提示)", "未获取二值化图像信息");
    }
}


/*--------------@brief：添加排除区域-------------*/
/*--------------@note： -------------*/
void FindRectCenterDlg::on_btnExcludeProcess_clicked()
{
    //0仰望图像，1俯视图像
    switch(isUpImgorDownImg)
    {
    case 0:
        cv::imshow("test", m_binImg);
        //鼠标回调函数，参数1表示窗口名称，参数2表示调用回调函数,参数3表示传给回调函数的用户数据
        cv::setMouseCallback("test", addExclusionArea, (void*)(&m_binImg));
        ui->btnSelectProcess->setEnabled(true); //使能'选择区域'按钮
        //ui->btnPreProcess->setEnabled(false);   //禁用'图像预处理'按钮
        break;

    case 1:

        //imshow("test", image);
        //鼠标回调函数，参数1表示名称，参数2表示调用on_Mouse,参数3表示传给回调函数的参数
        //cv::setMouseCallback("test", excludeMouse, (void*)(&image));

        break;

    default:
        break;

    }
}


/** --------------@brief：添加选择区域------------- **/
/** --------------@note： ------------- **/
void FindRectCenterDlg::on_btnSelectProcess_clicked()
{
    //0仰望图像，1俯视图像
    switch(isUpImgorDownImg)
    {
    case 0:
        //鼠标回调函数，参数1表示窗口名称，参数2表示调用回调函数,参数3表示传给回调函数的用户数据
        cv::setMouseCallback("test", addSelectArea, (void*)(&m_binImg));
        ui->btnExcludeProcess->setEnabled(false); //禁用'排除区域'按钮
        ui->btnDrawLeftProcess->setEnabled(true); //使能'绘制左边缘线'按钮
        break;

    case 1:

        //imshow("test", image);
        //鼠标回调函数，参数1表示名称，参数2表示调用on_Mouse,参数3表示传给回调函数的参数
        //cv::setMouseCallback("test", excludeMouse, (void*)(&image));

        break;

    default:
        break;

    }
}


/** --------------@brief：绘制左边缘线------------- **/
/** --------------@note： ------------- **/
void FindRectCenterDlg::on_btnDrawLeftProcess_clicked()
{
    //0仰望图像，1俯视图像
    switch(isUpImgorDownImg)
    {
    case 0:
        //cv::imshow("test", m_binImg);
        //鼠标回调函数，参数1表示窗口名称，参数2表示调用回调函数,参数3表示传给回调函数的用户数据
        cv::setMouseCallback("test", drawLeftLine, (void*)(&m_binImg));
        ui->btnDrawRightProcess->setEnabled(true); //使能'绘制右边缘线'按钮
        ui->btnUndo->setEnabled(true); //使能'删除'按钮
        break;

    case 1:

        //imshow("test", image);
        //鼠标回调函数，参数1表示名称，参数2表示调用on_Mouse,参数3表示传给回调函数的参数
        //cv::setMouseCallback("test", excludeMouse, (void*)(&image));

        break;

    default:
        break;
    }

}


/** --------------@brief：绘制右边缘线------------- **/
/** --------------@note： ------------- **/
void FindRectCenterDlg::on_btnDrawRightProcess_clicked()
{
    //0仰望图像，1俯视图像
    switch(isUpImgorDownImg)
    {
    case 0:
        //cv::imshow("test", m_binImg);
        //鼠标回调函数，参数1表示窗口名称，参数2表示调用回调函数,参数3表示传给回调函数的用户数据
        cv::setMouseCallback("test", drawRightLine, (void*)(&m_binImg));
        ui->btnDrawUpProcess->setEnabled(true); //使能'绘制上边缘线'按钮
        break;

    case 1:

        //imshow("test", image);
        //鼠标回调函数，参数1表示名称，参数2表示调用on_Mouse,参数3表示传给回调函数的参数
        //cv::setMouseCallback("test", excludeMouse, (void*)(&image));

        break;

    default:
        break;
    }

}


/** --------------@brief：绘制上边缘线------------- **/
/** --------------@note： ------------- **/
void FindRectCenterDlg::on_btnDrawUpProcess_clicked()
{
    //0仰望图像，1俯视图像
    switch(isUpImgorDownImg)
    {
    case 0:
        //cv::imshow("test", m_binImg);
        //鼠标回调函数，参数1表示窗口名称，参数2表示调用回调函数,参数3表示传给回调函数的用户数据
        cv::setMouseCallback("test", drawUpLine, (void*)(&m_binImg));
        ui->btnDrawBottomProcess->setEnabled(true); //使能'绘制下边缘线'按钮
        break;

    case 1:

        //imshow("test", image);
        //鼠标回调函数，参数1表示名称，参数2表示调用on_Mouse,参数3表示传给回调函数的参数
        //cv::setMouseCallback("test", excludeMouse, (void*)(&image));

        break;

    default:
        break;
    }

}


/** --------------@brief：绘制下边缘线------------- **/
/** --------------@note： ------------- **/
void FindRectCenterDlg::on_btnDrawBottomProcess_clicked()
{
    //0仰望图像，1俯视图像
    switch(isUpImgorDownImg)
    {
    case 0:
        //cv::imshow("test", m_binImg);
        //鼠标回调函数，参数1表示窗口名称，参数2表示调用回调函数,参数3表示传给回调函数的用户数据
        cv::setMouseCallback("test", drawDownLine, (void*)(&m_binImg));
        ui->btnFitLeftProcess->setEnabled(true); //使能'拟合左边缘线'按钮
        break;

    case 1:

        //imshow("test", image);
        //鼠标回调函数，参数1表示名称，参数2表示调用on_Mouse,参数3表示传给回调函数的参数
        //cv::setMouseCallback("test", excludeMouse, (void*)(&image));

        break;

    default:
        break;
    }
}


/** --------------@brief：拟合左边缘线------------- **/
/** --------------@note： ------------- **/
void FindRectCenterDlg::on_btnFitLeftProcess_clicked()
{
    static std::vector<LineInfo> vec_LeftLine;
    vec_LeftLine = FindRectCenterDlg::getLeftLineVec(); //获取左边缘线容器

    //0仰望图像，1俯视图像
    switch(isUpImgorDownImg)
    {
    case 0:
        if (vec_LeftLine.size() == 0)
        {
            QMessageBox::information(NULL, "PROMPT(提示)", "图像没有拟合点");
        }
        else
        {
            ui->btnSelectProcess->setEnabled(false);     //禁用'选择区域'按钮
            ui->btnDrawLeftProcess->setEnabled(false);   //禁用'绘制左边缘线'按钮
            ui->btnDrawRightProcess->setEnabled(false);  //禁用'绘制右边缘线'按钮
            ui->btnDrawUpProcess->setEnabled(false);     //禁用'绘制上边缘线'按钮
            ui->btnDrawBottomProcess->setEnabled(false); //禁用'绘制下边缘线'按钮
            ui->btnFitLeftProcess->setEnabled(false);    //禁用'拟合左边缘线'按钮
            ui->btnUndo->setEnabled(false);              //禁用'删除'按钮
            ui->btnFitRightProcess->setEnabled(true);    //使能'拟合右边缘线'按钮

            std::vector<cv::Point> intersections;
            //取出直线与图像边缘的交点
            for (int i = 0; i < int(vec_LeftLine.size()); i++)
            {
                intersections.push_back(vec_LeftLine[i].intersectionPoint);
            }

            FitLineInfo m_fitLine = fitLine(intersections); //求得拟合直线的斜率以及截距
            qDebug() << "左边缘线的斜率:"<<m_fitLine.k<<",截距:"<<m_fitLine.b;
            //qDebug() << "左边缘线的截距："<<m_fitLine.b;
            FindRectCenterDlg::setFitLineVec(m_fitLine); //将拟合直线的斜率以及截距放进容器
        }
        break;

    case 1:

        break;

    default:
        break;
    }  
}


/** --------------@brief：拟合右边缘线------------- **/
/** --------------@note： ------------- **/
void FindRectCenterDlg::on_btnFitRightProcess_clicked()
{
    static std::vector<LineInfo> vec_RightLine;
    vec_RightLine = FindRectCenterDlg::getRightLineVec(); //获取右边缘线容器

    //0仰望图像，1俯视图像
    switch(isUpImgorDownImg)
    {
    case 0:
        if (vec_RightLine.size() == 0)
        {
            QMessageBox::information(NULL, "PROMPT(提示)", "图像没有拟合点");
        }
        else
        {
            ui->btnFitRightProcess->setEnabled(false); //禁用'拟合右边缘线'按钮
            ui->btnFitUpProcess->setEnabled(true);  //使能'拟合上边缘线'按钮

            std::vector<cv::Point> intersections;
            //取出直线与图像边缘的交点
            for (int i = 0; i < int(vec_RightLine.size()); i++)
            {
                intersections.push_back(vec_RightLine[i].intersectionPoint);
            }

            FitLineInfo m_fitLine = fitLine(intersections); //拟合直线
            qDebug() << "右边缘线的斜率:"<<m_fitLine.k<<",截距:"<<m_fitLine.b;
            //qDebug() << "右边缘线的截距："<<m_fitLine.b;
            FindRectCenterDlg::setFitLineVec(m_fitLine); //将拟合直线放进容器
        }
        break;

    case 1:

        break;

    default:
        break;
    }
}


/** --------------@brief：拟合上边缘线------------- **/
/** --------------@note： ------------- **/
void FindRectCenterDlg::on_btnFitUpProcess_clicked()
{
    static std::vector<LineInfo> vec_UPLine;
    vec_UPLine = FindRectCenterDlg::getUpLineVec(); //获取上边缘线容器

    //0仰望图像，1俯视图像
    switch(isUpImgorDownImg)
    {
    case 0:
        if (vec_UPLine.size() == 0)
        {
            QMessageBox::information(NULL, "PROMPT(提示)", "图像没有拟合点");
        }
        else
        {
            ui->btnFitUpProcess->setEnabled(false); //禁用'拟合右边缘线'按钮
            ui->btnFitBottomProcess->setEnabled(true); //使能'拟合下边缘线'按钮

            std::vector<cv::Point> intersections;
            //取出直线与图像边缘的交点
            for (int i = 0; i < int(vec_UPLine.size()); i++)
            {
                intersections.push_back(vec_UPLine[i].intersectionPoint);
            }

            FitLineInfo m_fitLine = fitLine(intersections); //拟合直线
            qDebug() << "上边缘线的斜率:"<<m_fitLine.k<<",截距:"<<m_fitLine.b;
            //qDebug() << "上边缘线的截距："<<m_fitLine.b;
            FindRectCenterDlg::setFitLineVec(m_fitLine); //将拟合直线放进容器
        }
        break;

    case 1:

        break;

    default:
        break;
    }

}


/** --------------@brief：拟合下边缘线------------- **/
/** --------------@note： ------------- **/
void FindRectCenterDlg::on_btnFitBottomProcess_clicked()
{
    static std::vector<LineInfo> vec_DownLine;
    vec_DownLine = FindRectCenterDlg::getDownLineVec(); //获取上边缘线容器

    //0仰望图像，1俯视图像
    switch(isUpImgorDownImg)
    {
    case 0:
        if (vec_DownLine.size() == 0)
        {
            QMessageBox::information(NULL, "PROMPT(提示)", "图像没有拟合点");
        }
        else
        {
            ui->btnFitBottomProcess->setEnabled(false); //禁用'拟合下边缘线'按钮
            ui->btnCenterProcess->setEnabled(true); //使能'中心点'按钮

            std::vector<cv::Point> intersections;
            //取出直线与图像边缘的交点
            for (int i = 0; i < int(vec_DownLine.size()); i++)
            {
                intersections.push_back(vec_DownLine[i].intersectionPoint);
            }

            FitLineInfo m_fitLine = fitLine(intersections); //拟合直线
            qDebug() << "下边缘线的斜率:"<<m_fitLine.k<<",截距:"<<m_fitLine.b;
            //qDebug() << "下边缘线的截距："<<m_fitLine.b;
            FindRectCenterDlg::setFitLineVec(m_fitLine); //将拟合直线放进容器
        }
        break;

    case 1:

        break;

    default:
        break;
    }
}


/** --------------@brief：寻找图像的中心点------------- **/
/** --------------@note： ------------- **/
void FindRectCenterDlg::on_btnCenterProcess_clicked()
{
    static std::vector<FitLineInfo> vec_FitLine;
    vec_FitLine = FindRectCenterDlg::getFitLineVec();

    //0仰望图像，1俯视图像
    switch(isUpImgorDownImg)
    {
    case 0:
        if (vec_FitLine.size() == 0)
        {
            QMessageBox::information(NULL, "PROMPT(提示)", "图像没有交点");
        }
        else
        {
            ui->btnCenterProcess->setEnabled(false); //禁用'中心点'按钮
            ui->btnJsonProcess->setEnabled(true);    //使能'生成Json文件'按钮

            //获取四条拟合直线的四个交点，0-左边缘 1-右边缘 2-上边缘 3-下边缘
            cv::Point P1 = getLineIntersection(vec_FitLine[0], vec_FitLine[2]);
            cv::Point P2 = getLineIntersection(vec_FitLine[0], vec_FitLine[3]);
            cv::Point P3 = getLineIntersection(vec_FitLine[3], vec_FitLine[1]);
            cv::Point P4 = getLineIntersection(vec_FitLine[1], vec_FitLine[2]);

            //double angleInRadians = atan(vec_FitLine[3].k);  //计算弧度值
            //double angleInDegrees = angleInRadians * 180 / M_PI; //转换为角度值
            //qDebug() << "BGRSobelEdges angle in degrees: " << angleInDegrees;

            cv::line(m_binImg, P1, P2, cv::Scalar(0, 255, 255), 2); //拟合的左边缘线
            cv::line(m_binImg, P2, P3, cv::Scalar(0, 255, 255), 2); //拟合的下边缘线
            cv::line(m_binImg, P3, P4, cv::Scalar(0, 255, 255), 2); //拟合的右边缘线
            cv::line(m_binImg, P4, P1, cv::Scalar(0, 255, 255), 2); //拟合的上边缘线
            //qDebug()<<"P1的坐标为:"<<P1.x<<P1.y;
            //qDebug()<<"P2的坐标为:"<<P2.x<<P2.y;
            //qDebug()<<"P3的坐标为:"<<P3.x<<P3.y;
            //qDebug()<<"P4的坐标为:"<<P4.x<<P4.y;
            Line l1 = {P1, P3};
            Line l2 = {P2, P4};
            cv::line(m_binImg, P1, P3, cv::Scalar(0, 255, 255), 2);
            cv::line(m_binImg, P2, P4, cv::Scalar(0, 255, 255), 2);
            cv::imshow("test", m_binImg);
            //器件中心点
            cv::Point P5 = findCenter(l1, l2); /** findCenter的形参有待改进 **/
            qDebug() << "CameraSrcImg中心坐标：" << P5.x << "," << P5.y;
        }
        break;

    case 1:

        break;

    default:
        break;
    }
}


/** --------------@brief：生成Json文件------------- **/
/** --------------@note： ------------- **/
void FindRectCenterDlg::on_btnJsonProcess_clicked()
{
    QString currentText = ui->comboBox->currentText();

    static std::vector<RectangleInfo> vector_eclusionArea;
    static std::vector<RectangleInfo> vec_selectArea;
    static std::vector<LineInfo> vec_allDrawLine;
    static QString finnal;

    //0仰望图像，1俯视图像
    switch(isUpImgorDownImg)
    {
    case 0:
        ui->btnJsonProcess->setEnabled(false); //禁用'生成Json文件'按钮
        finnal = currentText + "-" + "DataCameraImage.json";

        vector_eclusionArea = FindRectCenterDlg::getEclusionAreaVec(); //获取筛选区域容器
        vec_selectArea = FindRectCenterDlg::getSelectAreaVec(); //获取选择区域容器
        vec_allDrawLine = FindRectCenterDlg::getAllLineVec(); //获取绘制的所有直线的容器
        saveToJson(vector_eclusionArea, vec_selectArea, vec_allDrawLine, finnal);

        break;

    case 1:
        break;

    default:
        break;
    }
}


/** --------------@brief：生成Json文件------------- **/
/** --------------@note： ------------- **/
/*void FindRectCenterDlg::on_btnJsonProcess_clicked()
{
    QString currentText = ui->comboBox->currentText();

    static std::vector<RectangleInfo> vector_eclusionArea;
    //static std::vector<std::vector<BindLineAndRect>> RectLineVectors;
    static std::vector<BindLineAndRect> vec_leftLine_leftSelectArea;
    static std::vector<BindLineAndRect> vec_rightLine_rightSelectArea;
    static std::vector<BindLineAndRect> vec_upLine_upSelectArea;
    static std::vector<BindLineAndRect> vec_downLine_downSelectArea;

    static std::vector<std::vector<BindLineAndRect>> doubleVec_bindLineAndRect;
    static QString finnal;

    //0仰望图像，1俯视图像
    switch(isUpImgorDownImg)
    {
    case 0:
        finnal = currentText + "-" + "DataCameraImage.json";

        vector_eclusionArea = FindRectCenterDlg::getEclusionAreaVec(); //获取筛选区域集合

        //获取左、右、上、下绘制的直线与相对应的选取区域的容器
        vec_leftLine_leftSelectArea   = FindRectCenterDlg::get_leftLineAddleftSelectAreaVec();
        vec_rightLine_rightSelectArea = FindRectCenterDlg::get_rightLineAddrightSelectAreaVec();
        vec_upLine_upSelectArea       = FindRectCenterDlg::get_upLineAddupSelectAreaVec();
        vec_downLine_downSelectArea   = FindRectCenterDlg::get_downLineAdddownSelectAreaVec();

        doubleVec_bindLineAndRect = {vec_leftLine_leftSelectArea,
                                     vec_rightLine_rightSelectArea,
                                     vec_upLine_upSelectArea,
                                     vec_downLine_downSelectArea};

        saveToJson(vector_eclusionArea, doubleVec_bindLineAndRect, finnal);
        break;

    case 1:

        break;

    default:
        break;
    }
}*/


/** --------------@brief：撤销直线------------- **/
/** --------------@note： ------------- **/
void FindRectCenterDlg::on_btnUndo_clicked()
{
    //cv::setMouseCallback(winName, unDo, (void*)(&m_scaleImg)); //鼠标事件
    cv::setMouseCallback(winName, unDo, (void*)(&m_binImg)); //鼠标事件
}






















