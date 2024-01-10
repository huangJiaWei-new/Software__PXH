#include "findrectcenterdlg.h"
#include "ui_findrectcenterdlg.h"
#include <windows.h>
#include <opencv2/highgui/highgui_c.h>
#include <QMessageBox>
#include <QDebug>
#include <QWheelEvent>
#include "cmd_def.h"

//初始化静态变量
std::string FindRectCenterDlg::winName = "test";
cv::Mat FindRectCenterDlg::m_scaleImg  = cv::Mat::zeros(3, 3, CV_8UC1);
//cv::Mat FindRectCenterDlg::m_
int FindRectCenterDlg::exclusionCount  = 0;
cv::Point FindRectCenterDlg::startPoint_Mouse = (-1, -1);
cv::Point FindRectCenterDlg::endPoint_Mouse   = (-1, -1);
RectangleInfo FindRectCenterDlg::m_rectInfo;

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

    //绘制筛选区域
    if (event == cv::EVENT_LBUTTONDOWN)
    {
        if (exclusionCount == 0)
        {
            FindRectCenterDlg::setRectStartPoint(cv::Point(x, y));    //设置矩形起始点坐标
            startPoint_rect = FindRectCenterDlg::getRectStartPoint(); //获取矩形起始点的坐标
            //qDebug() << "x的坐标" <<startPoint_rect.x<< "Y的坐标" <<startPoint_rect.y;
            exclusionCount++;
            FindRectCenterDlg::setExclusionCount(exclusionCount);
        }
        else if (exclusionCount == 1)
        {         
            FindRectCenterDlg::setRectEndPoint(cv::Point(x, y)); //设置矩形终点坐标
            endPoint_rect = FindRectCenterDlg::getRectEndPoint(); //获取矩形终点坐标

            //记录矩形的中心点坐标
            //qDebug() << "x的坐标" <<startPoint_rect.x<< "Y的坐标" <<startPoint_rect.y;
            //qDebug() << "x的坐标" <<endPoint_rect.x<< "Y的坐标" <<endPoint_rect.y;

            centerPoint_rect = cv::Point( (startPoint_rect.x + endPoint_rect.x) / 2,
                                          (startPoint_rect.y + endPoint_rect.y) / 2 );
            FindRectCenterDlg::setRectCenterPoint(centerPoint_rect); //设置矩形的中心点坐标

            cv::rectangle(image, startPoint_rect, endPoint_rect, cv::Scalar(0, 0, 255), 2);
            cv::imshow("test", image);
            QMessageBox::information(NULL, "PROMPT(提示)", "请一次性绘制完排除区域");
            exclusionCount = 0;
            FindRectCenterDlg::setExclusionCount(exclusionCount);
        }
    }
}


/** --------------@brief：添加选择区域回调函数------------- **/
/** --------------@note： ------------- **/
static void addSelectArea(int event,int x,int y,int flags,void *userdata)
{
    cv::Mat image = *((cv::Mat*)userdata);

    static int exclusionCount = FindRectCenterDlg::getExclusionCount();
    static cv::Point startPoint_rect;
    static cv::Point endPoint_rect;
    static cv::Point centerPoint_rect;

    //绘制筛选区域
    if (event == cv::EVENT_LBUTTONDOWN)
    {
        if (exclusionCount == 0)
        {
            FindRectCenterDlg::setRectStartPoint(cv::Point(x, y));    //设置矩形起始点坐标
            startPoint_rect = FindRectCenterDlg::getRectStartPoint(); //获取矩形起始点的坐标
            //qDebug() << "x的坐标" <<startPoint_rect.x<< "Y的坐标" <<startPoint_rect.y;
            exclusionCount++;
            FindRectCenterDlg::setExclusionCount(exclusionCount);
        }
        else if (exclusionCount == 1)
        {
            FindRectCenterDlg::setRectEndPoint(cv::Point(x, y)); //设置矩形终点坐标
            endPoint_rect = FindRectCenterDlg::getRectEndPoint(); //获取矩形终点坐标

            //记录矩形的中心点坐标
            //qDebug() << "x的坐标" <<startPoint_rect.x<< "Y的坐标" <<startPoint_rect.y;
            //qDebug() << "x的坐标" <<endPoint_rect.x<< "Y的坐标" <<endPoint_rect.y;

            centerPoint_rect = cv::Point( (startPoint_rect.x + endPoint_rect.x) / 2,
                                          (startPoint_rect.y + endPoint_rect.y) / 2 );
            FindRectCenterDlg::setRectCenterPoint(centerPoint_rect); //设置矩形的中心点坐标

            cv::rectangle(image, startPoint_rect, endPoint_rect, cv::Scalar(0, 255, 0), 2);
            cv::imshow("test", image);
            QMessageBox::information(NULL, "PROMPT(提示)", "请绘制对应的边缘交线");
            exclusionCount = 0;
            FindRectCenterDlg::setExclusionCount(exclusionCount);
        }
    }

}


/** --------------@brief：------------- **/
/** --------------@note： ------------- **/
void FindRectCenterDlg::setScaleImg(cv::Mat inputImg)
{
   m_scaleImg = inputImg;
}


/*--------------@brief：获取比例图像-------------*/
/*--------------@note： 静态成员函数-------------*/
cv::Mat FindRectCenterDlg::getScaleImg()
{
    return m_scaleImg;
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
void FindRectCenterDlg::setStartPoint_Mouse(cv::Point startPointMouse)
{
    startPoint_Mouse = startPointMouse;
}


/** --------------@brief：设置鼠标终点的坐标------------- **/
/** --------------@note： 静态成员函数------------- **/
void FindRectCenterDlg::setEndPonint_Mouse(cv::Point endPointMouse)
{
    endPoint_Mouse = endPointMouse;
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


/*--------------@brief：设置矩形的起点坐标-------------*/
/*--------------@note： 静态成员函数-------------*/
void FindRectCenterDlg::setRectStartPoint(cv::Point startPoint)
{
    m_rectInfo.rectStartPoint = startPoint;
}


/*--------------@brief：设置矩形的终点坐标-------------*/
/*--------------@note： 静态成员函数-------------*/
void FindRectCenterDlg::setRectEndPoint(cv::Point endPoint)
{
    m_rectInfo.rectEndPoint = endPoint;
}


/*--------------@brief：设置矩形的中心点坐标-------------*/
/*--------------@note： 静态成员函数-------------*/
void FindRectCenterDlg::setRectCenterPoint(cv::Point centerPoint)
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



///*--------------@brief：获取矩形结构体的成员-------------*/
///*--------------@note： -------------*/
//RectangleInfo FindRectCenterDlg::getRectangleInfo()
//{
//    return m_rectInfo.rectStartPoint;
//}


/*--------------@brief：Sobel边缘检测-------------*/
/*--------------@note： -------------*/
bool FindRectCenterDlg::mySobel(cv::Mat &inputImg)
{
    bool isTrueVal = true;
    //使用'Sobel'算子检测图像中的边缘
    cv::Mat grad_x, grad_y;
    cv::Sobel(inputImg, grad_x, CV_16S, 1, 0);
    cv::Sobel(inputImg, grad_y, CV_16S, 0, 1);
    cv::convertScaleAbs(grad_x, grad_x);
    cv::convertScaleAbs(grad_y, grad_y);
    cv::addWeighted(grad_x, 0.5, grad_y, 0.5, 0, m_sobelEdges);

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


/*--------------@brief：-------------*/
/*--------------@note： -------------*/
//void FindRectCenterDlg::excludeMouseDrawing_2(cv::Mat &image)
//{
//    cv::imshow("test", image);
//    //鼠标回调函数，参数1表示名称，参数2表示调用on_Mouse,参数3表示传给回调函数的参数
//    cv::setMouseCallback("test", excludeMouse_2, (void*)(&image));
//}


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
    m_scaleImg = m_UpImage;

    cv::setMouseCallback(winName, moveImg, (void*)(&m_scaleImg)); //鼠标事件
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
        //鼠标回调函数，参数1表示窗口名称，参数2表示调用回调函数,参数3表示传给回调函数的用户数据
        cv::setMouseCallback("test", addExclusionArea, (void*)(&m_scaleImg));
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
        cv::setMouseCallback("test", addSelectArea, (void*)(&m_scaleImg));
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























