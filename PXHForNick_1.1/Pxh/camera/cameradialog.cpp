#include "camera/cameradialog.h"
#include "ui_openmulticamdlg.h"
#include <QMessageBox>
#include <QDebug>
#include <windows.h>
#include <QGuiApplication>

#define  M_PI 3.14
// 全局变量
cv::Point S_sp(-1, -1);
cv::Point S_ep(-1, -1);
cv::Mat S_temp;
std::vector<cv::Point> S_intersectionPoints;
std::vector<cv::Point> S_intersections;
cv::Mat m_srcSobelEdge;
S_LineResult S_Line_Result;  //直线结果
S_SelectRect S_Select_Rect;  //总结果
S_LineResult S_Line_Result_2;
S_SelectRect S_Select_Rect_2;
cv::Mat S_LineImage, S_LineImage_2;
std::vector<S_RectLine> S_Rect_Line, S_Rect_Line_2;  //存放每条线的斜率和截距
QHash<int, QString> TypeHash;

OpenMultiCamDlg::OpenMultiCamDlg(QWidget *parent,QList<CMvCamera*> listMyCamera) :
    QWidget(parent),
    ui(new Ui::OpenMultiCamDlg)
{
    ui->setupUi(this);
    m_bStartGrabbing=false;

    //清除'm_listMyCamera'列表
    if(m_listMyCamera.count()>0)
        m_listMyCamera.clear();

    connect(this,SIGNAL(sigUpdatePicture1()),ui->widgetPicture1,SIGNAL(sigUpdate()));
    connect(this,SIGNAL(sigUpdatePicture2()),ui->widgetPicture2,SIGNAL(sigUpdate()));
    connect(this,SIGNAL(sigUpdatePicture3()),ui->widgetPicture3,SIGNAL(sigUpdate()));
    connect(this,SIGNAL(sigUpdatePicture4()),ui->widgetPicture4,SIGNAL(sigUpdate()));

    for (int i = 0; i < MAX_DEVICE_NUM; i++)
    {
        m_listMyCamera.append(listMyCamera[i]);
    }

    ui->btnOpenCam->setEnabled(false); //禁止'打开设备'按钮
    ui->btnSetUpCameraLine->setEnabled(true);   //启用'设置仰望相机校正参数'按钮
    ui->btnSetDownCameraLine->setEnabled(true); //启用'设置俯视相机校正参数'按钮
    ui->btnJson->setEnabled(true);      //启用'解析Json'按钮
    ui->btnShowImage->setEnabled(true); //启用'实时显示'按钮

    m_isRealTimeProcess = false;
}

OpenMultiCamDlg::~OpenMultiCamDlg()
{

    delete ui;
}


/*--------------@brief：显示相机设备错误-------------*/
/*--------------@note： -------------*/
void OpenMultiCamDlg::showErrorMsg(QString csMessage, long long nErrorNum)
{
    QString errorMsg = csMessage;
    if (nErrorNum != 0)
    {
        QString TempMsg;
        TempMsg.sprintf(": Error = %x: ", nErrorNum);
        errorMsg += TempMsg;
    }

    switch(nErrorNum)
    {
    case MV_E_HANDLE:           errorMsg += "Error or invalid handle ";                                         break;
    case MV_E_SUPPORT:          errorMsg += "Not supported function ";                                          break;
    case MV_E_BUFOVER:          errorMsg += "Cache is full ";                                                   break;
    case MV_E_CALLORDER:        errorMsg += "Function calling order error ";                                    break;
    case MV_E_PARAMETER:        errorMsg += "Incorrect parameter ";                                             break;
    case MV_E_RESOURCE:         errorMsg += "Applying resource failed ";                                        break;
    case MV_E_NODATA:           errorMsg += "No data ";                                                         break;
    case MV_E_PRECONDITION:     errorMsg += "Precondition error, or running environment changed ";              break;
    case MV_E_VERSION:          errorMsg += "Version mismatches ";                                              break;
    case MV_E_NOENOUGH_BUF:     errorMsg += "Insufficient memory ";                                             break;
    case MV_E_ABNORMAL_IMAGE:   errorMsg += "Abnormal image, maybe incomplete image because of lost packet ";   break;
    case MV_E_UNKNOW:           errorMsg += "Unknown error ";                                                   break;
    case MV_E_GC_GENERIC:       errorMsg += "General error ";                                                   break;
    case MV_E_GC_ACCESS:        errorMsg += "Node accessing condition error ";                                  break;
    case MV_E_ACCESS_DENIED:	errorMsg += "No permission ";                                                   break;
    case MV_E_BUSY:             errorMsg += "Device is busy, or network disconnected ";                         break;
    case MV_E_NETER:            errorMsg += "Network error ";                                                   break;
    }

    QMessageBox::information(NULL, "PROMPT(提示)", errorMsg);
}


/*--------------@brief：回调函数显示图像-------------*/
/*--------------@note： -------------*/
void OpenMultiCamDlg::camCallBackInner(unsigned char *pData, MV_FRAME_OUT_INFO_EX *pFrameInfo, int camIndex, QString frameCountInfo)
{
    cv::Mat mat_dst;
    bool rlt=convert2Mat(pFrameInfo, pData, &mat_dst);

    //获取当前设备的IP地址
    int m_nIp1 = ((m_stDevList.pDeviceInfo[camIndex]->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
    int m_nIp2 = ((m_stDevList.pDeviceInfo[camIndex]->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
    int m_nIp3 = ((m_stDevList.pDeviceInfo[camIndex]->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
    int m_nIp4 = (m_stDevList.pDeviceInfo[camIndex]->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);

    m_curIp = QString::number(m_nIp1) + "."+ QString::number(m_nIp2)+ "." + QString::number(m_nIp3) + "." + QString::number(m_nIp4);
    int m_typeNum = m_typeHash[m_curIp];
    qDebug()<<m_typeNum;

    //判断是否为实时状态
    if (m_isRealTimeProcess)
    {
        mutex.lock(); //加锁，确保线程安全
        cv::Mat m_temp;

        if (m_typeNum == 0)
        {
            m_temp = showUpCameraImage(mat_dst);
        }
        else if (m_typeNum == 1)
        {
            m_temp = showDownCameraImage(mat_dst);
        }

        //进行图像结果显示 Mat -> QImage
        QImage img_Temp,img_Temp2;
        QPixmap pixmapTemp;
        img_Temp =QImage((const unsigned char*)(m_temp.data), m_temp.cols, m_temp.rows, m_temp.step, QImage::Format_RGB888);

        if(img_Temp.isNull())
        {
            qDebug()<<"MatArcImg->Qtemp is null"<<endl;
        }

        switch(m_typeNum)
        {
        case 0:
            img_Temp2 = img_Temp.scaled(ui->widgetPicture1->size(), Qt::IgnoreAspectRatio);
            pixmapTemp=QPixmap::fromImage(img_Temp2);
            ui->widgetPicture1->SetPicturePixmap(pixmapTemp,0);

            if(ui->btnTriggerMode->isChecked())//只在触发模式下              
                m_matImgUp=mat_dst.clone();
            else
                m_matImgUp=NULL;

            emit sigUpdatePicture1(); //通知应用程序更新'ui->widgetPicture1'上显示的图像
            break;
        case 1:
            img_Temp2 = img_Temp.scaled(ui->widgetPicture2->size(), Qt::IgnoreAspectRatio);
            pixmapTemp=QPixmap::fromImage(img_Temp2);
            ui->widgetPicture2->SetPicturePixmap(pixmapTemp,1);

            if(ui->btnTriggerMode->isChecked())//只在触发模式下
                m_matImgDown=mat_dst.clone();
            else
                m_matImgDown=NULL;

            emit sigUpdatePicture2();                   
            break;
        case 2:
            img_Temp2 = img_Temp.scaled(ui->widgetPicture3->size(), Qt::IgnoreAspectRatio);
            pixmapTemp=QPixmap::fromImage(img_Temp2);
            ui->widgetPicture3->SetPicturePixmap(pixmapTemp,2);

            emit sigUpdatePicture3();         
            break;
        case 3:
            img_Temp2 = img_Temp.scaled(ui->widgetPicture4->size(), Qt::IgnoreAspectRatio);
            pixmapTemp=QPixmap::fromImage(img_Temp2);
            ui->widgetPicture4->SetPicturePixmap(pixmapTemp,3);

            emit sigUpdatePicture4();           
            break;
        }
        mat_dst.release();
        m_temp.release();       
        mutex.unlock();//解锁
    }
    else
    {
        //进行图像结果显示 Mat -> QImage
        QImage img_Temp,img_Temp2;
        QPixmap pixmapTemp;
        if (pFrameInfo->enPixelType == PixelType_Gvsp_Mono8)
        {
            img_Temp =QImage((const unsigned char*)(mat_dst.data), mat_dst.cols, mat_dst.rows, mat_dst.step, QImage::Format_Grayscale8);
        }
        else if (pFrameInfo->enPixelType == PixelType_Gvsp_RGB8_Packed)
        {
            img_Temp =QImage((const unsigned char*)(mat_dst.data), mat_dst.cols, mat_dst.rows, mat_dst.step, QImage::Format_RGB888);
        }
        else
        {
            qDebug()<<"Mat to Qimage, unsupported pixel format! \n";
            return ;
        }

        switch (m_typeNum)
        {
        case 0:
            img_Temp2 = img_Temp.scaled(ui->widgetPicture1->size(), Qt::IgnoreAspectRatio);
            pixmapTemp=QPixmap::fromImage(img_Temp2);
            ui->widgetPicture1->SetPicturePixmap(pixmapTemp,0);

            if(ui->btnTriggerMode->isChecked())//只在触发模式下
                m_matImgUp=mat_dst.clone();
            else
                m_matImgUp=NULL;

            emit sigUpdatePicture1();
            break;
        case 1:
            img_Temp2 = img_Temp.scaled(ui->widgetPicture2->size(), Qt::IgnoreAspectRatio);
            pixmapTemp=QPixmap::fromImage(img_Temp2);
            ui->widgetPicture2->SetPicturePixmap(pixmapTemp,1);

            if(ui->btnTriggerMode->isChecked())//只在触发模式下
                m_matImgDown=mat_dst.clone();
            else
                m_matImgDown=NULL;

            emit sigUpdatePicture2();
            break;
        case 2:
            img_Temp2 = img_Temp.scaled(ui->widgetPicture3->size(), Qt::IgnoreAspectRatio);
            pixmapTemp=QPixmap::fromImage(img_Temp2);
            ui->widgetPicture3->SetPicturePixmap(pixmapTemp,2);

            emit sigUpdatePicture3();
            break;
        case 3:
            img_Temp2 = img_Temp.scaled(ui->widgetPicture4->size(), Qt::IgnoreAspectRatio);
            pixmapTemp=QPixmap::fromImage(img_Temp2);
            ui->widgetPicture4->SetPicturePixmap(pixmapTemp,3);

            emit sigUpdatePicture4();
            break;
        }
        mat_dst.release();
    }
}


/*--------------@brief：相机回调-------------*/
/*--------------@note： 每次回调都从这进入，如果同名无法区分是哪个相机进入的-------------*/

void __stdcall OpenMultiCamDlg::camCallBack0(unsigned char *pData, MV_FRAME_OUT_INFO_EX *pFrameInfo, void *pUser)
{
    //'pData'表示捕获到的图像数据指针
    //'pFrameInfo'包含有关捕获到的图像帧的信息
    //'pUser'指向用户自定义数据的指针，通常用于传递上下文信息给回调函数
    if(pUser)
    {
        OpenMultiCamDlg *pWindow = (OpenMultiCamDlg*)pUser;
        pWindow->camCallBackInner(pData, pFrameInfo,0,"");
    }
}

void OpenMultiCamDlg::camCallBack1(unsigned char *pData, MV_FRAME_OUT_INFO_EX *pFrameInfo, void *pUser)
{
    if(pUser)
    {
        OpenMultiCamDlg *pWindow = (OpenMultiCamDlg*)pUser;
        pWindow->camCallBackInner(pData, pFrameInfo,1,"");
    }
}

void OpenMultiCamDlg::camCallBack2(unsigned char *pData, MV_FRAME_OUT_INFO_EX *pFrameInfo, void *pUser)
{
    if(pUser)
    {
        OpenMultiCamDlg *pWindow = (OpenMultiCamDlg*)pUser;
        pWindow->camCallBackInner(pData, pFrameInfo,2,"");
    }
}

void OpenMultiCamDlg::camCallBack3(unsigned char *pData, MV_FRAME_OUT_INFO_EX *pFrameInfo, void *pUser)
{
    if(pUser)
    {
        OpenMultiCamDlg *pWindow = (OpenMultiCamDlg*)pUser;
        pWindow->camCallBackInner(pData, pFrameInfo,3,"");
    }
}


/*--------------@brief：开始采集，通过多线程方法QThread+ 注册-------------*/
/*--------------@note： -------------*/
void OpenMultiCamDlg::startCamByQThreadCallBack()
{
    //为每一个相机创建一个线程
    for(int i=0;i<m_listWorkingCamera.count();i++)
    {
        QThread *camThread=new QThread();
        threadListWorkingCam.append(camThread);
    }

    i_camIndex=0;

    //为每个相机注册不同的回调函数
    for(int i=0;i<m_listWorkingCamera.count();i++)
    {
        switch (i)
        {
        case 0:
            m_listWorkingCamera[i]->RegisterImageCallBack(camCallBack0, this);
            break;
        case 1:
            m_listWorkingCamera[i]->RegisterImageCallBack(camCallBack1, this);
            break;
        case 2:
            m_listWorkingCamera[i]->RegisterImageCallBack(camCallBack2, this);
            break;
        case 3:
            m_listWorkingCamera[i]->RegisterImageCallBack(camCallBack3, this);
            break;
        }
        //将相机对象移动到先前为该相机创建的线程中，以便在该线程中执行相机操作
        m_listWorkingCamera[i]->moveToThread(threadListWorkingCam[i]);

        i_camIndex=i;
        int nRet = m_listWorkingCamera[i]->StartGrabbing(); //开始图像采集

        if (MV_OK != nRet)
        {
            showErrorMsg("Start grabbing fail", nRet);
            continue;
        }
        else
        {
            m_bStartGrabbing =  true;
            ui->btnStop->setEnabled(true);           //启用'停止采集'按钮
            ui->btnOpenCam->setEnabled(false);       //禁止'打开设备'按钮
            ui->btnStartAqui->setEnabled(false);     //禁止'开始采集'按钮
            ui->btnTriggerMode->setEnabled(false);   //禁止'触发模式'按钮
            ui->btnContinuesMode->setEnabled(false); //禁止'连续模式'按钮
            /***************有疑问btnTriggerMode*/
            //'触发模式按钮'为True,则启用'软触发一次'按钮，反之
            if(ui->btnTriggerMode->isChecked())
              ui->btnTriggerExec->setEnabled(true);
            else
              ui->btnTriggerExec->setEnabled(false);
        }
    }
}


/*--------------@brief：format将数据流转换为Mat格式-------------*/
/*--------------@note： -------------*/
bool OpenMultiCamDlg::convert2Mat(MV_FRAME_OUT_INFO_EX *pstImageInfo, unsigned char *pData, cv::Mat *srcImage)
{
    if (pstImageInfo->enPixelType == PixelType_Gvsp_Mono8) //单通道灰度图像
    {
        *srcImage = cv::Mat(pstImageInfo->nHeight, pstImageInfo->nWidth, CV_8UC1, pData);
    }
    else if (pstImageInfo->enPixelType == PixelType_Gvsp_RGB8_Packed) //RGB图像
    {
        RGB2BGR(pData, pstImageInfo->nWidth, pstImageInfo->nHeight);
        *srcImage = cv::Mat(pstImageInfo->nHeight, pstImageInfo->nWidth, CV_8UC3, pData);
    }
    else
    {
        qDebug()<<"MV_FRAME to Mat ,unsupported pixel format !\n";
        return false;
    }

    if ( NULL == srcImage->data )
    {
        return false;
    }
    return true;
}


/*--------------@brief：将RGB转换为BGR-------------*/
/*--------------@note： -------------*/
int OpenMultiCamDlg::RGB2BGR(unsigned char *pRgbData, unsigned int nWidth, unsigned int nHeight)
{
    if ( NULL == pRgbData )
    {
        return MV_E_PARAMETER;
    }

    for (unsigned int j = 0; j < nHeight; j++)
    {
        for (unsigned int i = 0; i < nWidth; i++)
        {
            unsigned char red = pRgbData[j * (nWidth * 3) + i * 3];
            pRgbData[j * (nWidth * 3) + i * 3]     = pRgbData[j * (nWidth * 3) + i * 3 + 2];
            pRgbData[j * (nWidth * 3) + i * 3 + 2] = red;
        }
    }
    return MV_OK;
}


/*--------------@brief：实时显示仰望相机图像-------------*/
/*--------------@note： -------------*/
cv::Mat OpenMultiCamDlg::showUpCameraImage(cv::Mat &UpCameraImage)
{
    if(UpCameraImage.data)
    {
        bool isSobelFlag = sobel(UpCameraImage);
        if(isSobelFlag)
        {
            //QMessageBox::information(NULL, "PROMPT(提示)", "Sobel边缘检测成功");
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
            //QMessageBox::information(NULL, "PROMPT(提示)", "二值化成功");
        }
    }
    else
    {
        QMessageBox::information(NULL, "PROMPT(提示)", "未获取二值化图像信息");
    }

    //排除区域
    for (int i = 0; i < int(S_Select_Rect.sxRect.size()); i++)
    {
        cv::rectangle(m_sobelEdgesBgr, S_Select_Rect.sxRect[i].RectStart, S_Select_Rect.sxRect[i].RectEnd, cv::Scalar(0, 0, 255), 2);
    }

    //左选择区域、左边缘与直线交点
    for (int i = 0; i < int(S_Select_Rect.RectAddLine_LV.size()); i++)
    {
        cv::rectangle(m_sobelEdgesBgr, S_Select_Rect.RectAddLine_LV[i].RectLineResult_Rect.RectStart, S_Select_Rect.RectAddLine_LV[i].RectLineResult_Rect.RectEnd, cv::Scalar(0, 255, 0), 2);
        S_LineImage = cv::Mat::zeros(m_sobelEdgesBgr.size(), CV_8UC1);
        int dx = S_Select_Rect.RectAddLine_LV[i].RectLineResult_Rect.RectEnd.x - S_Select_Rect.RectAddLine_LV[i].RectLineResult_Rect.RectStart.x;
        int dy = S_Select_Rect.RectAddLine_LV[i].RectLineResult_Rect.RectEnd.y - S_Select_Rect.RectAddLine_LV[i].RectLineResult_Rect.RectStart.y;
        cv::Rect box(S_Select_Rect.RectAddLine_LV[i].RectLineResult_Rect.RectStart.x, S_Select_Rect.RectAddLine_LV[i].RectLineResult_Rect.RectStart.y, dx, dy);
        cv::line(m_sobelEdgesBgr, S_Select_Rect.RectAddLine_LV[i].RectLineResult_Line.LineStart, S_Select_Rect.RectAddLine_LV[i].RectLineResult_Line.LineEnd, cv::Scalar(255, 0, 0), 1);
        cv::line(S_LineImage, S_Select_Rect.RectAddLine_LV[i].RectLineResult_Line.LineStart, S_Select_Rect.RectAddLine_LV[i].RectLineResult_Line.LineEnd, cv::Scalar(255, 255, 255), 1);
        cv::Point intersection = S_findIntersections(m_srcSobelEdge,S_LineImage, box);
        S_Line_Result.intersection = intersection;

        if (S_Line_Result.intersection.x != 0 && S_Line_Result.intersection.y != 0)
        {
            S_Select_Rect.lineResult_LV.push_back(S_Line_Result);
        }
    }
    //拟合左边缘线
    if (S_Select_Rect.lineResult_LV.size() == 0)
    {
        //QMessageBox::information(NULL, "PROMPT(提示)", "CameraSrcImg没有拟合点");
    }
    else
    {
        std::vector<cv::Point> intersections;
        for (int i = 0; i < int(S_Select_Rect.lineResult_LV.size()); i++)
        {
            intersections.push_back(S_Select_Rect.lineResult_LV[i].intersection);
        }
        S_RectLine l = fit_line(intersections);
        S_Rect_Line.push_back(l);
    }

    //上选择区域、上边缘与直线交点
    for (int i = 0; i < int(S_Select_Rect.RectAddLine_UL.size()); i++)
    {
        cv::rectangle(m_sobelEdgesBgr, S_Select_Rect.RectAddLine_UL[i].RectLineResult_Rect.RectStart, S_Select_Rect.RectAddLine_UL[i].RectLineResult_Rect.RectEnd, cv::Scalar(0, 255, 0), 2);
        S_LineImage = cv::Mat::zeros(m_sobelEdgesBgr.size(), CV_8UC1);
        int dx = S_Select_Rect.RectAddLine_UL[i].RectLineResult_Rect.RectEnd.x - S_Select_Rect.RectAddLine_UL[i].RectLineResult_Rect.RectStart.x;
        int dy = S_Select_Rect.RectAddLine_UL[i].RectLineResult_Rect.RectEnd.y - S_Select_Rect.RectAddLine_UL[i].RectLineResult_Rect.RectStart.y;
        cv::Rect box(S_Select_Rect.RectAddLine_UL[i].RectLineResult_Rect.RectStart.x, S_Select_Rect.RectAddLine_UL[i].RectLineResult_Rect.RectStart.y, dx, dy);
        cv::line(m_sobelEdgesBgr, S_Select_Rect.RectAddLine_UL[i].RectLineResult_Line.LineStart, S_Select_Rect.RectAddLine_UL[i].RectLineResult_Line.LineEnd, cv::Scalar(255, 0, 0), 1);
        cv::line(S_LineImage, S_Select_Rect.RectAddLine_UL[i].RectLineResult_Line.LineStart, S_Select_Rect.RectAddLine_UL[i].RectLineResult_Line.LineEnd, cv::Scalar(255, 255, 255), 1);
        cv::Point intersection = S_findIntersections(m_srcSobelEdge,S_LineImage, box);
        S_Line_Result.intersection = intersection;

        if (S_Line_Result.intersection.x != 0 && S_Line_Result.intersection.y != 0)
        {
            S_Select_Rect.lineResult_UL.push_back(S_Line_Result);
        }
    }
    //拟合上边缘线
    if (S_Select_Rect.lineResult_UL.size() == 0)
    {
        //QMessageBox::information(NULL, "PROMPT(提示)", "CameraSrcImg没有拟合点");
    }
    else
    {
        std::vector<cv::Point> intersections;
        for (int i = 0; i < int(S_Select_Rect.lineResult_UL.size()); i++)
        {
            intersections.push_back(S_Select_Rect.lineResult_UL[i].intersection);
        }
        S_RectLine l = fit_line(intersections);
        S_Rect_Line.push_back(l);
    }

    //右选择区域、右边缘与直线交点
    for (int i = 0; i < int(S_Select_Rect.RectAddLine_RV.size()); i++)
    {
        cv::rectangle(m_sobelEdgesBgr, S_Select_Rect.RectAddLine_RV[i].RectLineResult_Rect.RectStart, S_Select_Rect.RectAddLine_RV[i].RectLineResult_Rect.RectEnd, cv::Scalar(0, 255, 0), 2);
        S_LineImage = cv::Mat::zeros(m_sobelEdgesBgr.size(), CV_8UC1);
        int dx = S_Select_Rect.RectAddLine_RV[i].RectLineResult_Rect.RectEnd.x - S_Select_Rect.RectAddLine_RV[i].RectLineResult_Rect.RectStart.x;
        int dy = S_Select_Rect.RectAddLine_RV[i].RectLineResult_Rect.RectEnd.y - S_Select_Rect.RectAddLine_RV[i].RectLineResult_Rect.RectStart.y;
        cv::Rect box(S_Select_Rect.RectAddLine_RV[i].RectLineResult_Rect.RectStart.x, S_Select_Rect.RectAddLine_RV[i].RectLineResult_Rect.RectStart.y, dx, dy);
        cv::line(m_sobelEdgesBgr, S_Select_Rect.RectAddLine_RV[i].RectLineResult_Line.LineStart, S_Select_Rect.RectAddLine_RV[i].RectLineResult_Line.LineEnd, cv::Scalar(255, 0, 0), 1);
        cv::line(S_LineImage, S_Select_Rect.RectAddLine_RV[i].RectLineResult_Line.LineStart, S_Select_Rect.RectAddLine_RV[i].RectLineResult_Line.LineEnd, cv::Scalar(255, 255, 255), 1);
        cv::Point intersection = S_findIntersections(m_srcSobelEdge,S_LineImage, box);
        S_Line_Result.intersection = intersection;
        if (S_Line_Result.intersection.x != 0 && S_Line_Result.intersection.y != 0)
        {
            S_Select_Rect.lineResult_RV.push_back(S_Line_Result);
        }
    }
    //拟合右边缘线
    if (S_Select_Rect.lineResult_RV.size() == 0)
    {
        //QMessageBox::information(NULL, "PROMPT(提示)", "CameraSrcImg没有拟合点");
    }
    else
    {
        std::vector<cv::Point> intersections;
        for (int i = 0; i < int(S_Select_Rect.lineResult_RV.size()); i++)
        {
            intersections.push_back(S_Select_Rect.lineResult_RV[i].intersection);
        }
        S_RectLine l = fit_line(intersections);
        S_Rect_Line.push_back(l);
    }

    //下选择区域、下边缘与直线交点
    for (int i = 0; i < int(S_Select_Rect.RectAddLine_DL.size()); i++)
    {
        cv::rectangle(m_sobelEdgesBgr, S_Select_Rect.RectAddLine_DL[i].RectLineResult_Rect.RectStart, S_Select_Rect.RectAddLine_DL[i].RectLineResult_Rect.RectEnd, cv::Scalar(0, 255, 0), 2);
        S_LineImage = cv::Mat::zeros(m_sobelEdgesBgr.size(), CV_8UC1);
        int dx = S_Select_Rect.RectAddLine_DL[i].RectLineResult_Rect.RectEnd.x - S_Select_Rect.RectAddLine_DL[i].RectLineResult_Rect.RectStart.x;
        int dy = S_Select_Rect.RectAddLine_DL[i].RectLineResult_Rect.RectEnd.y - S_Select_Rect.RectAddLine_DL[i].RectLineResult_Rect.RectStart.y;
        cv::Rect box(S_Select_Rect.RectAddLine_DL[i].RectLineResult_Rect.RectStart.x, S_Select_Rect.RectAddLine_DL[i].RectLineResult_Rect.RectStart.y, dx, dy);
        cv::line(m_sobelEdgesBgr, S_Select_Rect.RectAddLine_DL[i].RectLineResult_Line.LineStart, S_Select_Rect.RectAddLine_DL[i].RectLineResult_Line.LineEnd, cv::Scalar(255, 0, 0), 1);
        cv::line(S_LineImage, S_Select_Rect.RectAddLine_DL[i].RectLineResult_Line.LineStart, S_Select_Rect.RectAddLine_DL[i].RectLineResult_Line.LineEnd, cv::Scalar(255, 255, 255), 1);
        cv::Point intersection = S_findIntersections(m_srcSobelEdge,S_LineImage, box);
        S_Line_Result.intersection = intersection;
        if (S_Line_Result.intersection.x != 0 && S_Line_Result.intersection.y != 0)
        {
            S_Select_Rect.lineResult_DL.push_back(S_Line_Result);
        }
    }
    //拟合下边缘线
    if (S_Select_Rect.lineResult_DL.size() == 0)
    {
        //QMessageBox::information(NULL, "PROMPT(提示)", "CameraSrcImg没有拟合点");
    }
    else
    {
        std::vector<cv::Point> intersections;
        for (int i = 0; i < int(S_Select_Rect.lineResult_DL.size()); i++)
        {
            intersections.push_back(S_Select_Rect.lineResult_DL[i].intersection);
        }
        S_RectLine l = fit_line(intersections);
        S_Rect_Line.push_back(l);
    }

    //求中心点
    if (S_Rect_Line.size() == 0)
    {
        //QMessageBox::information(NULL, "PROMPT(提示)", "CameraSrcImg没有交点");
    }
    else
    {
        //四个交点
        cv::Point P1 = getIntersection(S_Rect_Line[0], S_Rect_Line[1]);
        cv::Point P2 = getIntersection(S_Rect_Line[1], S_Rect_Line[2]);
        cv::Point P3 = getIntersection(S_Rect_Line[2], S_Rect_Line[3]);
        cv::Point P4 = getIntersection(S_Rect_Line[3], S_Rect_Line[0]);

        double angleInRadiansUp = atan(S_Rect_Line[1].k);  //计算弧度值
        double angleInDegreesUp = angleInRadiansUp * 180 / M_PI; //转换为角度值
        qDebug() << "BGRSobelEdges angle in degrees(上边缘): " << angleInDegreesUp;

        double angleInRadiansBottom = atan(S_Rect_Line[3].k);  //计算弧度值
        double angleInDegreesBottom = angleInRadiansBottom * 180 / M_PI; //转换为角度值
        qDebug() << "BGRSobelEdges angle in degrees(下边缘): " << angleInDegreesBottom;

        double angleInDegreesMean = (angleInDegreesUp + angleInDegreesBottom) / 2;
        qDebug() << "BGRSobelEdges angle in degrees(平均值): " << angleInDegreesMean;

        S_Line l1 = {P1, P3};
        S_Line l2 = {P2, P4};
        //器件中心点
        cv::Point CameraImageCenter = intersection(l1, l2);
        qDebug() << "CameraSrcImg中心坐标：" << CameraImageCenter.x << "," << CameraImageCenter.y;
        cv::circle(m_sobelEdgesBgrCopy, CameraImageCenter, 5, cv::Scalar(0, 0, 255) ,2 , 8);
        cv::Mat temp;

        if(m_sobelEdgesBgrCopy.channels()==3)
        {
            cv::cvtColor(m_sobelEdgesBgrCopy, temp, CV_BGR2RGB);  //BGR convert to RGB
            qDebug()<<"BGR convert to RGB"<<endl;
        }
        else if(m_sobelEdgesBgrCopy.channels()==1)
        {
            cv::cvtColor(m_sobelEdgesBgrCopy,temp, CV_GRAY2RGB);  //GRAY convert to RGB
            qDebug()<<"GRAY convert to RGB"<<endl;
        }

        return temp;
    }
}


/*--------------@brief：实时显示俯瞰相机-------------*/
/*--------------@note： -------------*/
cv::Mat OpenMultiCamDlg::showDownCameraImage(cv::Mat &DownCameraImage)
{
    if(DownCameraImage.data)
    {
        bool isSobelFlag = sobel(DownCameraImage);
        if(isSobelFlag)
        {
            //QMessageBox::information(NULL, "PROMPT(提示)", "Sobel边缘检测成功");
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
            //QMessageBox::information(NULL, "PROMPT(提示)", "二值化成功");
        }
    }
    else
    {
        QMessageBox::information(NULL, "PROMPT(提示)", "未获取二值化图像信息");
    }

    //排除区域
    for (int i = 0; i < int(S_Select_Rect_2.sxRect_2.size()); i++)
    {
        cv::rectangle(m_sobelEdgesBgr, S_Select_Rect_2.sxRect_2[i].RectStart, S_Select_Rect_2.sxRect_2[i].RectEnd, cv::Scalar(0, 0, 255), 2);
    }

    //左选择区域、左边缘与直线交点
    for (int i = 0; i < int(S_Select_Rect_2.RectAddLine_LV_2.size()); i++)
    {
        cv::rectangle(m_sobelEdgesBgr, S_Select_Rect_2.RectAddLine_LV_2[i].RectLineResult_Rect.RectStart, S_Select_Rect_2.RectAddLine_LV_2[i].RectLineResult_Rect.RectEnd, cv::Scalar(0, 255, 0), 2);
        S_LineImage_2 = cv::Mat::zeros(m_sobelEdgesBgr.size(), CV_8UC1);
        int dx = S_Select_Rect_2.RectAddLine_LV_2[i].RectLineResult_Rect.RectEnd.x - S_Select_Rect_2.RectAddLine_LV_2[i].RectLineResult_Rect.RectStart.x;
        int dy = S_Select_Rect_2.RectAddLine_LV_2[i].RectLineResult_Rect.RectEnd.y - S_Select_Rect_2.RectAddLine_LV_2[i].RectLineResult_Rect.RectStart.y;
        cv::Rect box(S_Select_Rect_2.RectAddLine_LV_2[i].RectLineResult_Rect.RectStart.x, S_Select_Rect_2.RectAddLine_LV_2[i].RectLineResult_Rect.RectStart.y, dx, dy);
        cv::line(m_sobelEdgesBgr, S_Select_Rect_2.RectAddLine_LV_2[i].RectLineResult_Line.LineStart, S_Select_Rect_2.RectAddLine_LV_2[i].RectLineResult_Line.LineEnd, cv::Scalar(255, 0, 0), 1);
        cv::line(S_LineImage_2, S_Select_Rect_2.RectAddLine_LV_2[i].RectLineResult_Line.LineStart, S_Select_Rect_2.RectAddLine_LV_2[i].RectLineResult_Line.LineEnd, cv::Scalar(255, 255, 255), 1);
        cv::Point intersection = S_findIntersections_2(m_srcSobelEdge,S_LineImage_2, box);
        S_Line_Result_2.intersection = intersection;
        if (S_Line_Result_2.intersection.x != 0 && S_Line_Result_2.intersection.y != 0)
        {
            S_Select_Rect_2.lineResult_LV_2.push_back(S_Line_Result_2);
        }
    }
    //拟合左边缘线
    if (S_Select_Rect_2.lineResult_LV_2.size() == 0)
    {
        //QMessageBox::information(NULL, "PROMPT(提示)", "CameraSrcImg_2没有拟合点");
    }
    else
    {
        std::vector<cv::Point> intersections;
        for (int i = 0; i < int(S_Select_Rect_2.lineResult_LV_2.size()); i++)
        {
            intersections.push_back(S_Select_Rect_2.lineResult_LV_2[i].intersection);
        }
        S_RectLine l_2 = fit_line(intersections);
        S_Rect_Line_2.push_back(l_2);
    }

    //上选择区域、上边缘与直线交点
    for (int i = 0; i < int(S_Select_Rect_2.RectAddLine_UL_2.size()); i++)
    {
        cv::rectangle(m_sobelEdgesBgr, S_Select_Rect_2.RectAddLine_UL_2[i].RectLineResult_Rect.RectStart, S_Select_Rect_2.RectAddLine_UL_2[i].RectLineResult_Rect.RectEnd, cv::Scalar(0, 255, 0), 2);
        S_LineImage_2 = cv::Mat::zeros(m_sobelEdgesBgr.size(), CV_8UC1);
        int dx = S_Select_Rect_2.RectAddLine_UL_2[i].RectLineResult_Rect.RectEnd.x - S_Select_Rect_2.RectAddLine_UL_2[i].RectLineResult_Rect.RectStart.x;
        int dy = S_Select_Rect_2.RectAddLine_UL_2[i].RectLineResult_Rect.RectEnd.y - S_Select_Rect_2.RectAddLine_UL_2[i].RectLineResult_Rect.RectStart.y;
        cv::Rect box(S_Select_Rect_2.RectAddLine_UL_2[i].RectLineResult_Rect.RectStart.x, S_Select_Rect_2.RectAddLine_UL_2[i].RectLineResult_Rect.RectStart.y, dx, dy);
        cv::line(m_sobelEdgesBgr, S_Select_Rect_2.RectAddLine_UL_2[i].RectLineResult_Line.LineStart, S_Select_Rect_2.RectAddLine_UL_2[i].RectLineResult_Line.LineEnd, cv::Scalar(255, 0, 0), 1);
        cv::line(S_LineImage_2, S_Select_Rect_2.RectAddLine_UL_2[i].RectLineResult_Line.LineStart, S_Select_Rect_2.RectAddLine_UL_2[i].RectLineResult_Line.LineEnd, cv::Scalar(255, 255, 255), 1);
        cv::Point intersection = S_findIntersections_2(m_srcSobelEdge,S_LineImage_2, box);
        S_Line_Result_2.intersection = intersection;
        if (S_Line_Result_2.intersection.x != 0 && S_Line_Result_2.intersection.y != 0)
        {
            S_Select_Rect_2.lineResult_UL_2.push_back(S_Line_Result_2);
        }
    }
    //拟合上边缘线
    if (S_Select_Rect_2.lineResult_UL_2.size() == 0)
    {
        //QMessageBox::information(NULL, "PROMPT(提示)", "CameraSrcImg_2没有拟合点");
    }
    else
    {
        std::vector<cv::Point> intersections;
        for (int i = 0; i < int(S_Select_Rect_2.lineResult_UL_2.size()); i++)
        {
            intersections.push_back(S_Select_Rect_2.lineResult_UL_2[i].intersection);
        }
        S_RectLine l_2 = fit_line(intersections);
        S_Rect_Line_2.push_back(l_2);
    }

    //右选择区域、右边缘与直线交点
    for (int i = 0; i < int(S_Select_Rect_2.RectAddLine_RV_2.size()); i++)
    {
        cv::rectangle(m_sobelEdgesBgr, S_Select_Rect_2.RectAddLine_RV_2[i].RectLineResult_Rect.RectStart, S_Select_Rect_2.RectAddLine_RV_2[i].RectLineResult_Rect.RectEnd, cv::Scalar(0, 255, 0), 2);
        S_LineImage_2 = cv::Mat::zeros(m_sobelEdgesBgr.size(), CV_8UC1);
        int dx = S_Select_Rect_2.RectAddLine_RV_2[i].RectLineResult_Rect.RectEnd.x - S_Select_Rect_2.RectAddLine_RV_2[i].RectLineResult_Rect.RectStart.x;
        int dy = S_Select_Rect_2.RectAddLine_RV_2[i].RectLineResult_Rect.RectEnd.y - S_Select_Rect_2.RectAddLine_RV_2[i].RectLineResult_Rect.RectStart.y;
        cv::Rect box(S_Select_Rect_2.RectAddLine_RV_2[i].RectLineResult_Rect.RectStart.x, S_Select_Rect_2.RectAddLine_RV_2[i].RectLineResult_Rect.RectStart.y, dx, dy);
        cv::line(m_sobelEdgesBgr, S_Select_Rect_2.RectAddLine_RV_2[i].RectLineResult_Line.LineStart, S_Select_Rect_2.RectAddLine_RV_2[i].RectLineResult_Line.LineEnd, cv::Scalar(255, 0, 0), 1);
        cv::line(S_LineImage_2, S_Select_Rect_2.RectAddLine_RV_2[i].RectLineResult_Line.LineStart, S_Select_Rect_2.RectAddLine_RV_2[i].RectLineResult_Line.LineEnd, cv::Scalar(255, 255, 255), 1);
        cv::Point intersection = S_findIntersections_2(m_srcSobelEdge,S_LineImage_2, box);
        S_Line_Result_2.intersection = intersection;
        if (S_Line_Result_2.intersection.x != 0 && S_Line_Result_2.intersection.y != 0)
        {
            S_Select_Rect_2.lineResult_RV_2.push_back(S_Line_Result_2);
        }
    }
    //拟合右边缘线
    if (S_Select_Rect_2.lineResult_RV_2.size() == 0)
    {
        //QMessageBox::information(NULL, "PROMPT(提示)", "CameraSrcImg没有拟合点");
    }
    else
    {
        std::vector<cv::Point> intersections;
        for (int i = 0; i < int(S_Select_Rect_2.lineResult_RV_2.size()); i++)
        {
            intersections.push_back(S_Select_Rect_2.lineResult_RV_2[i].intersection);
        }
        S_RectLine l_2 = fit_line(intersections);
        S_Rect_Line_2.push_back(l_2);
    }


    //下选择区域、下边缘与直线交点
    for (int i = 0; i < int(S_Select_Rect_2.RectAddLine_DL_2.size()); i++)
    {
        cv::rectangle(m_sobelEdgesBgr, S_Select_Rect_2.RectAddLine_DL_2[i].RectLineResult_Rect.RectStart, S_Select_Rect_2.RectAddLine_DL_2[i].RectLineResult_Rect.RectEnd, cv::Scalar(0, 255, 0), 2);
        S_LineImage_2 = cv::Mat::zeros(m_sobelEdgesBgr.size(), CV_8UC1);
        int dx = S_Select_Rect_2.RectAddLine_DL_2[i].RectLineResult_Rect.RectEnd.x - S_Select_Rect_2.RectAddLine_DL_2[i].RectLineResult_Rect.RectStart.x;
        int dy = S_Select_Rect_2.RectAddLine_DL_2[i].RectLineResult_Rect.RectEnd.y - S_Select_Rect_2.RectAddLine_DL_2[i].RectLineResult_Rect.RectStart.y;
        cv::Rect box(S_Select_Rect_2.RectAddLine_DL_2[i].RectLineResult_Rect.RectStart.x, S_Select_Rect_2.RectAddLine_DL_2[i].RectLineResult_Rect.RectStart.y, dx, dy);
        cv::line(m_sobelEdgesBgr, S_Select_Rect_2.RectAddLine_DL_2[i].RectLineResult_Line.LineStart, S_Select_Rect_2.RectAddLine_DL_2[i].RectLineResult_Line.LineEnd, cv::Scalar(255, 0, 0), 1);
        cv::line(S_LineImage_2, S_Select_Rect_2.RectAddLine_DL_2[i].RectLineResult_Line.LineStart, S_Select_Rect_2.RectAddLine_DL_2[i].RectLineResult_Line.LineEnd, cv::Scalar(255, 255, 255), 1);
        cv::Point intersection = S_findIntersections_2(m_srcSobelEdge,S_LineImage_2, box);
        S_Line_Result_2.intersection = intersection;
        if (S_Line_Result_2.intersection.x != 0 && S_Line_Result_2.intersection.y != 0)
        {
            S_Select_Rect_2.lineResult_DL_2.push_back(S_Line_Result_2);
        }
    }
    //拟合下边缘线
    if (S_Select_Rect_2.lineResult_DL_2.size() == 0)
    {
        //QMessageBox::information(NULL, "PROMPT(提示)", "CameraSrcImg没有拟合点");
    }
    else
    {
        std::vector<cv::Point> intersections;
        for (int i = 0; i < int(S_Select_Rect_2.lineResult_DL_2.size()); i++)
        {
            intersections.push_back(S_Select_Rect_2.lineResult_DL_2[i].intersection);
        }
        S_RectLine l_2 = fit_line(intersections);
        S_Rect_Line_2.push_back(l_2);
    }

    //求中心点
    if (S_Rect_Line_2.size() == 0)
    {
        //QMessageBox::information(NULL, "PROMPT(提示)", "CameraSrcImg没有交点");
    }
    else
    {
        //四个交点
        cv::Point P1_2 = getIntersection(S_Rect_Line_2[0], S_Rect_Line_2[1]);
        cv::Point P2_2 = getIntersection(S_Rect_Line_2[1], S_Rect_Line_2[2]);
        cv::Point P3_2 = getIntersection(S_Rect_Line_2[2], S_Rect_Line_2[3]);
        cv::Point P4_2 = getIntersection(S_Rect_Line_2[3], S_Rect_Line_2[0]);

        double angleInRadiansUp_2 = atan(S_Rect_Line_2[1].k);  //计算弧度值
        double angleInDegreesUp_2 = angleInRadiansUp_2 * 180 / M_PI; //转换为角度值
        qDebug() << "BGRSobelEdges angle in degrees(上边缘): " << angleInDegreesUp_2;

        double angleInRadiansBottom_2 = atan(S_Rect_Line_2[3].k);  //计算弧度值
        double angleInDegreesBottom_2 = angleInRadiansBottom_2 * 180 / M_PI; //转换为角度值
        qDebug() << "BGRSobelEdges angle in degrees(下边缘): " << angleInDegreesBottom_2;

        double angleInDegreesMean_2 = (angleInDegreesUp_2 + angleInDegreesBottom_2) / 2;
        qDebug() << "BGRSobelEdges angle in degrees(平均值): " << angleInDegreesMean_2;

        S_Line l1_2 = {P1_2, P3_2};
        S_Line l2_2 = {P2_2, P4_2};
        //器件中心点
        cv::Point CameraImageCenter_2 = intersection(l1_2, l2_2);
        qDebug() << "CameraSrcImg_2中心坐标：" << CameraImageCenter_2.x << "," << CameraImageCenter_2.y;
        cv::circle(m_sobelEdgesBgrCopy, CameraImageCenter_2, 5, cv::Scalar(0, 0, 255), 2, 8);
        cv::Mat temp;
        if(m_sobelEdgesBgrCopy.channels()==3)
        {
            cv::cvtColor(m_sobelEdgesBgrCopy, temp, CV_BGR2RGB);  //BGR convert to RGB
            qDebug()<<"BGR convert to RGB"<<endl;
        }
        else if(m_sobelEdgesBgrCopy.channels()==1)
        {
            cv::cvtColor(m_sobelEdgesBgrCopy,temp, CV_GRAY2RGB);  //GRAY convert to RGB
            qDebug()<<"GRAY convert to RGB"<<endl;
        }
        return temp;
    }
}


/*--------------@brief：sobel边缘检测-------------*/
/*--------------@note： -------------*/
bool OpenMultiCamDlg::sobel(cv::Mat &imageFp)
{
    bool isTrueVal = true;
    //使用Sobel算子检测图像中的边缘
    cv::Mat grad_x, grad_y;
    cv::Sobel(imageFp, grad_x, CV_16S, 1, 0);
    cv::Sobel(imageFp, grad_y, CV_16S, 0, 1);
    cv::convertScaleAbs(grad_x, grad_x);
    cv::convertScaleAbs(grad_y, grad_y);
    cv::addWeighted(grad_x, 0.5, grad_y, 0.5, 0, m_sobelEdges);
    if(m_sobelEdges.data == 0)
    {
        isTrueVal = false;
    }
    return isTrueVal;
}


/*--------------@brief：-------------*/
/*--------------@note： -------------*/
bool OpenMultiCamDlg::binImageFunc()
{
    m_matBinImage.release();
    bool isTrueVal = false;
    double minthresholdnum = 0.0;
    double maxthresholdnum = 1.0;
    if(m_threshold !=0)
    {
        double tempthresholdnum;
        tempthresholdnum = m_threshold;
        if(minthresholdnum<tempthresholdnum && tempthresholdnum<maxthresholdnum)
        {
            m_iBinThreshNum = int(tempthresholdnum*255);
        }
        else if (1<=tempthresholdnum && tempthresholdnum<=255)
        {
            m_iBinThreshNum = int(tempthresholdnum);
        }
        else
        {
           QMessageBox::critical(this,"错误信息","请输入正确的阈值或比例阈值！");
           isTrueVal = true;
        }
    }
    qDebug()<<"iBinThreshNum:"<<m_iBinThreshNum<<endl;
    if(isTrueVal)
    {
        return isTrueVal;
    }
    cv::threshold(m_sobelEdges, m_matBinImage, m_iBinThreshNum, 255, cv::THRESH_BINARY);
//    namedWindow("matBinImg",CV_WINDOW_NORMAL);
//    imshow("matBinImg",matBinImg);
    //二值图
    m_matBinImage.copyTo(m_srcSobelEdge);
    cv::cvtColor(m_matBinImage, m_sobelEdgesBgr, cv::COLOR_GRAY2BGR);
    cv::cvtColor(m_matBinImage, m_sobelEdgesBgrCopy, cv::COLOR_GRAY2BGR);
    return isTrueVal;
}


/*--------------@brief：两条直线的交点-------------*/
/*--------------@note： -------------*/
cv::Point OpenMultiCamDlg::getIntersection(S_RectLine &fp1, S_RectLine &fp2)
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


/*--------------@brief：使用最小二乘法拟合直线-------------*/
/*--------------@note： -------------*/
S_RectLine OpenMultiCamDlg::fit_line(std::vector<cv::Point> &pointsFp)
{
    int n = pointsFp.size(); // 点的个数
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
    return S_RectLine(k, b);
}


/*--------------@brief：-------------*/
/*--------------@note： -------------*/
cv::Point OpenMultiCamDlg::S_findIntersections(cv::Mat &BinaryImage, cv::Mat &newBinaryImage, cv::Rect &roi)
{
    cv::Mat mask = cv::Mat::zeros(BinaryImage.size(), CV_8UC1);
    mask(roi).setTo(255);
    cv::findNonZero(BinaryImage & newBinaryImage & mask, S_intersectionPoints);
    if (S_intersectionPoints.size() == 0)
    {
        return {0, 0};
    }
    else
    {
        for (const auto& intersectionPoint : S_intersectionPoints)
        {
            S_intersections.push_back({(int)(intersectionPoint.x), (int)(intersectionPoint.y)});
        }
    }
    cv::Point average = {0, 0};
    int count = 0;
    int count2 = 0;
    for (int i = 0; i < (int)S_intersections.size(); i++)
    {
        if ((int)S_Select_Rect.sxRect.size() != 0)
        {
            //判断交点是否在筛选区域内
            for (int j = 0; j < (int)S_Select_Rect.sxRect.size(); j++)
            {
                int dx = abs(S_intersections[i].x - S_Select_Rect.sxRect[j].RectCenter.x);
                int dy = abs(S_intersections[i].y - S_Select_Rect.sxRect[j].RectCenter.y);
                int sxRectHalfHeight =  abs(S_Select_Rect.sxRect[j].RectEnd.y - S_Select_Rect.sxRect[j].RectStart.y) / 2;
                int sxRectHalfWidth = abs(S_Select_Rect.sxRect[j].RectEnd.x - S_Select_Rect.sxRect[j].RectStart.x) / 2;
                if (dx > sxRectHalfWidth | dy > sxRectHalfHeight)
                {
                    average.x += S_intersections[i].x;
                    average.y += S_intersections[i].y;
                    count++;
                    count2++;
                }
            }
        }
        else
        {
            average.x += S_intersections[i].x;
            average.y += S_intersections[i].y;
            count++;
        }
    }
    if (count2 != (int)S_Select_Rect.sxRect.size() * (int)S_intersections.size() && count2 == 0)
    {
        qDebug() << "没有交点" << endl;
        S_intersectionPoints.clear();
        S_intersections.clear();
        return {0, 0};
    }
    else
    {
        average.x /= count;
        average.y /= count;
        qDebug() << average.x <<","<< average.y;
        S_intersectionPoints.clear();
        S_intersections.clear();
        return average;
    }
}


/*--------------@brief：-------------*/
/*--------------@note： -------------*/
cv::Point OpenMultiCamDlg::S_findIntersections_2(cv::Mat &BinaryImage, cv::Mat &newBinaryImage, cv::Rect &roi)
{
    cv::Mat mask = cv::Mat::zeros(BinaryImage.size(), CV_8UC1);
    mask(roi).setTo(255);
    cv::findNonZero(BinaryImage & newBinaryImage & mask, S_intersectionPoints);
    if (S_intersectionPoints.size() == 0)
    {
        return {0, 0};
    }
    else
    {
        for (const auto& intersectionPoint : S_intersectionPoints)
        {
            S_intersections.push_back({(int)(intersectionPoint.x), (int)(intersectionPoint.y)});
        }
    }
    cv::Point average = {0, 0};
    int count = 0;
    int count2 = 0;
    for (int i = 0; i < (int)S_intersections.size(); i++)
    {
        if ((int)S_Select_Rect_2.sxRect_2.size() != 0)
        {
            //判断交点是否在筛选区域内
            for (int j = 0; j < (int)S_Select_Rect_2.sxRect_2.size(); j++)
            {
                int dx = abs(S_intersections[i].x - S_Select_Rect_2.sxRect_2[j].RectCenter.x);
                int dy = abs(S_intersections[i].y - S_Select_Rect_2.sxRect_2[j].RectCenter.y);
                int sxRectHalfHeight =  abs(S_Select_Rect_2.sxRect_2[j].RectEnd.y - S_Select_Rect_2.sxRect_2[j].RectStart.y) / 2;
                int sxRectHalfWidth = abs(S_Select_Rect_2.sxRect_2[j].RectEnd.x - S_Select_Rect_2.sxRect_2[j].RectStart.x) / 2;
                if (dx > sxRectHalfWidth | dy > sxRectHalfHeight)
                {
                    average.x += S_intersections[i].x;
                    average.y += S_intersections[i].y;
                    count++;
                    count2++;
                }
            }
        }
        else
        {
            average.x += S_intersections[i].x;
            average.y += S_intersections[i].y;
            count++;
        }
    }
    if (count2 != (int)S_Select_Rect_2.sxRect_2.size() * (int)S_intersections.size() && count2 == 0)
    {
        qDebug() << "没有交点" << endl;
        S_intersectionPoints.clear();
        S_intersections.clear();
        return {0, 0};
    }
    else
    {
        average.x /= count;
        average.y /= count;
        qDebug() << average.x <<","<< average.y;
        S_intersectionPoints.clear();
        S_intersections.clear();
        return average;
    }
}


/*--------------@brief：解析Json文件-------------*/
/*--------------@note： -------------*/
cv::Point OpenMultiCamDlg::jsonToPoint(const QJsonObject &jsonObject)
{
    cv::Point point;
    point.x = jsonObject["x"].toInt();
    point.y = jsonObject["y"].toInt();
    return point;
}

S_RectResult OpenMultiCamDlg::jsonToRectResult(const QJsonObject &jsonObject)
{
    S_RectResult item;
    item.RectStart = jsonToPoint(jsonObject["RectStart"].toObject());
    item.RectEnd = jsonToPoint(jsonObject["RectEnd"].toObject());
    item.RectCenter = jsonToPoint(jsonObject["RectCenter"].toObject());
    return item;
}

S_RectLineResult OpenMultiCamDlg::jsonToRectLineResult(const QJsonObject &jsonObject)
{
    S_RectLineResult item;
    item.RectLineResult_Rect.RectStart = jsonToPoint(jsonObject["RectStart"].toObject());
    item.RectLineResult_Rect.RectEnd = jsonToPoint(jsonObject["RectEnd"].toObject());
    item.RectLineResult_Rect.RectCenter = jsonToPoint(jsonObject["RectCenter"].toObject());
    item.RectLineResult_Line.LineStart = jsonToPoint(jsonObject["LineStart"].toObject());
    item.RectLineResult_Line.LineEnd = jsonToPoint(jsonObject["LineEnd"].toObject());
    item.RectLineResult_Line.intersection = jsonToPoint(jsonObject["intersection"].toObject());
    return item;
}

void OpenMultiCamDlg::loadFromJson(std::vector<S_RectResult> &RectVector, std::vector<std::vector<S_RectLineResult> > &RectLineVectors, const QString &fileName)
{
    QFile file(fileName);
    qDebug()<<"fileName:"<<fileName;
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray jsonData = file.readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
        QJsonObject jsonObject = jsonDoc.object();
        QJsonArray jsonArray = jsonObject["RectVector"].toArray();

        for (const QJsonValue &item : jsonArray)
        {
            RectVector.push_back(jsonToRectResult(item.toObject()));
        }

        QJsonArray jsonArray_2 = jsonObject["RectLineVectors"].toArray();

        for (const QJsonValue &value : jsonArray_2)
        {
            QJsonArray vectorArray = value.toArray();
            std::vector<S_RectLineResult> myVector;

            for (const QJsonValue &item : vectorArray)
            {
                myVector.push_back(jsonToRectLineResult(item.toObject()));
            }

            RectLineVectors.push_back(myVector);
        }
    }

}


/*--------------@brief：-------------*/
/*--------------@note： -------------*/
cv::Point OpenMultiCamDlg::intersection(S_Line &fp1, S_Line &fp2)
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


/*--------------@brief：软触发一次-------------*/
/*--------------@note： -------------*/
void OpenMultiCamDlg::doSoftwareOnce()
{
    int nRet = MV_OK;
    for (unsigned int i = 0; i < MAX_DEVICE_NUM; i++)
    {
        if (m_listWorkingCamera[i])
        {
            nRet = m_listWorkingCamera[i]->CommandExecute("TriggerSoftware");
            if (MV_OK != nRet)
            {
                qDebug()<<QString("Soft trigger fail! DevIndex[%1], nRet[%2]\r\n").arg(i+1).arg(nRet);
            }
        }
    }
}


/*--------------@brief：设置触发模式-------------*/
/*--------------@note： -------------*/
void OpenMultiCamDlg::setTriggerMode(int nTriggerMode)
{
    int nRet = MV_OK;
    for (int i = 0; i < m_listWorkingCamera.count(); i++)
    {
        if (m_listWorkingCamera[i])
        {
            nRet = m_listWorkingCamera[i]->SetEnumValue("TriggerMode", nTriggerMode);
            if (MV_OK != nRet)
            {
                qDebug()<<QString("Set Trigger mode fail! DevIndex[%1], TriggerMode[%2], nRet[%3]\r\n").arg(i+1).arg(nTriggerMode).arg(nRet);
            }
        }
    }
}


/*--------------@brief：设置触发源-------------*/
/*--------------@note： -------------*/
void OpenMultiCamDlg::setTriggerSource(int nTriggerSource)
{
    int nRet = MV_OK;
    for (int i = 0; i < m_listWorkingCamera.count(); i++)
    {
        if (m_listWorkingCamera[i])
        {
            nRet = m_listWorkingCamera[i]->SetEnumValue("TriggerMode", nTriggerSource);
            if (MV_OK != nRet)
            {
                qDebug()<<QString("Set Trigger mode fail! DevIndex[%1], TriggerMode[%2], nRet[%3]\r\n").arg(i+1).arg(nTriggerSource).arg(nRet);
            }
        }
    }
}


/*--------------@brief：查找并枚举相机设备-------------*/
/*--------------@note： -------------*/
void OpenMultiCamDlg::on_btnEnumCam_clicked()
{
    ui->ComboDevices->clear();

    //枚举子网内所有设备
    memset(&m_stDevList, 0, sizeof(MV_CC_DEVICE_INFO_LIST)); //'m_stDevList'结构体初始化为0，用于存储相机设备的信息

    int nRet = CMvCamera::EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &m_stDevList);
    if (MV_OK != nRet)
    {     
        return;
    }

    //将值加入到信息列表框中并显示出来
    for (unsigned int i = 0; i < m_stDevList.nDeviceNum; i++)
    {
        QString strMsg;
        MV_CC_DEVICE_INFO *pDeviceInfo = m_stDevList.pDeviceInfo[i];
        if (NULL == pDeviceInfo)
        {
            continue;
        }

        //如果设备有用户定义的名称，它将使用用户定义的名称来创建设备信息字符串
        //如果没有用户定义的名称，它将使用制造商名称、型号和序列号来创建设备信息字符串
        if (pDeviceInfo->nTLayerType == MV_GIGE_DEVICE)
        {
            int nIp1 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
            int nIp2 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
            int nIp3 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
            int nIp4 = (m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);

            if (strcmp("", (char*)pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName) != 0)
            {
                strMsg.sprintf("[%d]GigE:   %s  (%d.%d.%d.%d)", i, pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName, nIp1, nIp2, nIp3, nIp4);
            }
            else
            {
                strMsg.sprintf("[%d]GigE:   %s %s (%s)  (%d.%d.%d.%d)", i, pDeviceInfo->SpecialInfo.stGigEInfo.chManufacturerName,
                               pDeviceInfo->SpecialInfo.stGigEInfo.chModelName, pDeviceInfo->SpecialInfo.stGigEInfo.chSerialNumber, nIp1, nIp2, nIp3, nIp4);
            }
        }
        else if (pDeviceInfo->nTLayerType == MV_USB_DEVICE)
        {
            if (strcmp("", (char*)pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName) != 0)
            {
                strMsg.sprintf("[%d]UsbV3:  %s", i, pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName);
            }
            else
            {
                strMsg.sprintf("[%d]UsbV3:  %s %s (%s)", i, pDeviceInfo->SpecialInfo.stUsb3VInfo.chManufacturerName,
                               pDeviceInfo->SpecialInfo.stUsb3VInfo.chModelName, pDeviceInfo->SpecialInfo.stUsb3VInfo.chSerialNumber);
            }
        }
        else
        {
            showErrorMsg("Unknown device enumerated", 0);
        }
        ui->ComboDevices->addItem(strMsg);
    }

    //判断是否启用'btnOpenCam'打开设备按钮
    if (0 == m_stDevList.nDeviceNum)
    {
        showErrorMsg("No device", 0);
        ui->btnOpenCam->setEnabled(false);
        return;
    }
    else
        ui->btnOpenCam->setEnabled(true);

    ui->ComboDevices->setCurrentIndex(0);   //设置'ComboDevices'的当前选中项为第一个设备
    ui->btnContinuesMode->setChecked(true); //已启用'连续模式'按钮
    ui->btnTriggerMode->setChecked(false);  //已禁止'触发模式按钮'
}


/*--------------@brief：打开相机摄像头-------------*/
/*--------------@note： -------------*/
void OpenMultiCamDlg::on_btnOpenCam_clicked()
{
    //清除'm_listWorkingCamera'列表
    if(m_listWorkingCamera.count()>0)
        m_listWorkingCamera.clear();

    for (unsigned int i = 0; i < MAX_DEVICE_NUM; i++)
    {
        int nRet = m_listMyCamera[i]->Open(m_stDevList.pDeviceInfo[i]);

        //打开'm_listMyCamera'列表中的每个设备，如果打开失败，则释放资源、记录错误消息并继续尝试
        if (MV_OK != nRet)
        {
            delete(m_listMyCamera[i]);
            m_listMyCamera[i] = NULL;
            QString msg = QString("Open device failed! DevIndex[%1], nRet[%2]\r\n").arg(i+1).arg(nRet);
            QMessageBox::information(this,"warnning",msg);
            continue;
        }
        else
        {
            //判断是否是'GigE'设备
            if (m_stDevList.pDeviceInfo[i]->nTLayerType == MV_GIGE_DEVICE)
            {
                //'nPacketSize'用于存储网络包的最佳大小
                unsigned int nPacketSize = 0;
                //获取网络包的最佳大小，并将结果存储在'nPacketSize'变量中
                nRet = m_listMyCamera[i]->GetOptimalPacketSize(&nPacketSize);

                if (nPacketSize>0)
                {
                    //确保相机以最佳网络包大小进行数据传输。
                    nRet = m_listMyCamera[i]->SetIntValue("GevSCPSPacketSize",nPacketSize);
                    if(nRet != MV_OK)
                    {
                        showErrorMsg("Warning: Set Packet Size fail!", nRet);
                    }
                    else
                    {
                        //设置网络相机的参数及修改'cameradialog'界面控件状态
                        m_listMyCamera[i]->SetEnumValue("TriggerMode", MV_TRIGGER_MODE_ON);//间断  软触发
                        m_listMyCamera[i]->SetEnumValue("TriggerSource", MV_TRIGGER_SOURCE_SOFTWARE);
                        m_listWorkingCamera.append(m_listMyCamera[i]);
                        ui->btnOpenCam->setEnabled(false);    //禁止'打开设备'按钮
                        ui->btnClose->setEnabled(true);       //启用'关闭设备'按钮
                        ui->btnStartAqui->setEnabled(true);   //启用'开始采集'按钮
                        ui->btnTriggerMode->setChecked(true); //启用'触发模式'按钮
                        /**************有疑问*/
                        ui->btnTriggerMode->setEnabled(true);
                        ui->btnContinuesMode->setEnabled(true); //启用'连续模式'按钮
                    }
                }
                else
                {
                    showErrorMsg("Warning: Get Packet Size fail!", nRet);
                }
            }
        }
    }

}


/*--------------@brief：关闭相机-------------*/
/*--------------@note： 结束线程，释放资源-------------*/
void OpenMultiCamDlg::on_btnClose_clicked()
{
    m_bStartGrabbing = false;
    for(int i=0;i<m_hGrabThread.count();i++) //停止图像采集的线程
    {
        if (m_hGrabThread[i])
        {
            //等待指定线程句柄（m_hGrabThread[i]）结束 window.h
            WaitForSingleObject(m_hGrabThread[i], INFINITE);
            //关闭图像采集线程的句柄，以释放相关资源
            CloseHandle(m_hGrabThread[i]);//window.h
            m_hGrabThread[i] = NULL;
        }
    }

    for(int i=0;i<threadListWorkingCam.count();i++) //停止工作中的相机的线程
    {
        if (threadListWorkingCam[i])
        {
            threadListWorkingCam[i]->wait(); //等待线程结束
            threadListWorkingCam[i]->quit(); //停止线程
        }
    }

    for(int i=0;i<m_listWorkingCamera.count();i++) //关闭相机
    {
        int nRet = m_listWorkingCamera[i]->Close();
        if (MV_OK != nRet)
        {
            showErrorMsg("Close camera fail", nRet);
            continue;
        }
        else
        {
            m_listWorkingCamera[i]=NULL;
        }
    }

    ui->btnClose->setEnabled(false);     //禁止'关闭设备'按钮
    ui->btnOpenCam->setEnabled(true);    //启用'打开相机'按钮
    ui->btnStartAqui->setEnabled(false); //禁止'开始采集'按钮
    ui->btnStop->setEnabled(false);      //禁止'停止采集'按钮
}


/*--------------@brief：相机工作为连续模式-------------*/
/*--------------@note： -------------*/
void OpenMultiCamDlg::on_btnContinuesMode_clicked()
{
    setTriggerMode(MV_TRIGGER_MODE_OFF);
    ui->btnContinuesMode->setChecked(true); //已启用'连续模式'按钮
    ui->btnTriggerMode->setChecked(false);  //已禁止'触发模式'按钮
    ui->btnTriggerExec->setEnabled(false);  //禁止'软触发一次'按钮
}


/*--------------@brief：相机工作为触发模式-------------*/
/*--------------@note： -------------*/
void OpenMultiCamDlg::on_btnTriggerMode_clicked()
{
    setTriggerMode(MV_TRIGGER_MODE_ON);
    setTriggerSource(MV_TRIGGER_SOURCE_SOFTWARE);//硬触发MV_TRIGGER_SOURCE_LINE0
    ui->btnContinuesMode->setChecked(false); //已禁止'连续模式按钮'
    ui->btnTriggerMode->setChecked(true);    //已启用'触发模式'按钮
    if(m_bStartGrabbing)
      ui->btnTriggerExec->setEnabled(true);  //启用'软触发一次'按钮
}


/*--------------@brief：开始采集图像-------------*/
/*--------------@note： -------------*/
void OpenMultiCamDlg::on_btnStartAqui_clicked()
{
    startCamByQThreadCallBack(); //方法2 QT多线程回调
}


/*--------------@brief：停止采集-------------*/
/*--------------@note： -------------*/
void OpenMultiCamDlg::on_btnStop_clicked()
{
    if (false == m_bStartGrabbing)
    {
        return;
    }
    m_bStartGrabbing = false;
    for(int i=0;i<m_listWorkingCamera.count();i++)
    {
        int nRet = m_listWorkingCamera[i]->StopGrabbing();
        if (MV_OK != nRet)
        {
            showErrorMsg("Stop grabbing fail", nRet);
            continue;
        }
    }
    for(int i=0;i<m_hGrabThread.count();i++)
    {
        if (m_hGrabThread[i])
        {
            //等待指定线程句柄（m_hGrabThread[i]）结束
            WaitForSingleObject(m_hGrabThread[i], INFINITE);//window.h
            //关闭图像采集线程的句柄，以释放相关资源
            CloseHandle(m_hGrabThread[i]);//window.h
            m_hGrabThread[i] = NULL;
        }
    }
    for(int i=0;i<threadListWorkingCam.count();i++) //停止工作中的相机的线程
    {
        if (threadListWorkingCam[i])
        {
            threadListWorkingCam[i]->wait(); //等待线程结束
            threadListWorkingCam[i]->quit(); //停止线程
        }
    }

    ui->btnStartAqui->setEnabled(true);   //启用'开始采集'按钮
    ui->btnStop->setEnabled(false);       //禁止'停止采集'按钮
    ui->btnTriggerMode->setEnabled(true); //启用'触发模式'按钮
    ui->btnContinuesMode->setEnabled(true); //启用'连续模式'按钮
    ui->btnTriggerExec->setEnabled(false);  //禁止'软触发一次'按钮
}


/*--------------@brief：软触发一次-------------*/
/*--------------@note： -------------*/
void OpenMultiCamDlg::on_btnTriggerExec_clicked()
{
    if (FALSE == m_bStartGrabbing)
    {
        QMessageBox::information(this,"提示","Please start grabbing first!\r\n");
        return;
    }
    doSoftwareOnce();
}


/*--------------@brief：对仰望照片进行处理-------------*/
/*--------------@note： -------------*/
void OpenMultiCamDlg::on_btnSetUpCameraLine_clicked()
{
    emit activateFindCenter();//激活主界面的FindCenter
    emit sigSendImg(m_matImgUp,0);//传递图像到FindCenter
}


/*--------------@brief：对俯视照片进行处理-------------*/
/*--------------@note： -------------*/
void OpenMultiCamDlg::on_btnSetDownCameraLine_clicked()
{
    emit activateFindCenter();//激活主界面的FindCenter
    emit sigSendImg(m_matImgDown,2);//传递图像到FindCenter
}


/*--------------@brief：-------------*/
/*--------------@note： -------------*/
void OpenMultiCamDlg::on_btnJson_clicked()
{
    std::vector<S_RectResult> RectVector;
    std::vector<std::vector<S_RectLineResult>> RectLineVectors;
    std::vector<S_RectResult> RectVector_2;
    std::vector<std::vector<S_RectLineResult>> RectLineVectors_2;

    int key = 1;
    switch (key)
    {
    case 1:
        loadFromJson(RectVector, RectLineVectors, TypeHash[1] + "-" + "DataCameraImage.json");
        loadFromJson(RectVector_2, RectLineVectors_2, TypeHash[1] + "-" + "DataCameraImage_2.json");
        break;
    case 2:
        loadFromJson(RectVector, RectLineVectors, TypeHash[2] + "-" + "DataCameraImage.json");
        loadFromJson(RectVector_2, RectLineVectors_2, TypeHash[2] + "-" + "DataCameraImage_2.json");
        break;
    case 3:
        loadFromJson(RectVector, RectLineVectors, TypeHash[3] + "-" + "DataCameraImage.json");
        loadFromJson(RectVector_2, RectLineVectors_2, TypeHash[3] + "-" + "DataCameraImage_2.json");
        break;
    case 4:
        loadFromJson(RectVector, RectLineVectors, TypeHash[4] + "-" + "DataCameraImage.json");
        loadFromJson(RectVector_2, RectLineVectors_2, TypeHash[4] + "-" + "DataCameraImage_2.json");
        break;
    }

    // 图像1
    if (RectVector.size() != 0)
    {
        S_Select_Rect.sxRect = RectVector;
    }
    else
    {
        QMessageBox::information(NULL, "PROMPT(提示)", "RectDataCameraImage数据不全(未选择排除区域)");
    }

    if (RectLineVectors.size() == 4)
    {
        S_Select_Rect.RectAddLine_LV = RectLineVectors[0];
        S_Select_Rect.RectAddLine_UL = RectLineVectors[1];
        S_Select_Rect.RectAddLine_RV = RectLineVectors[2];
        S_Select_Rect.RectAddLine_DL = RectLineVectors[3];
    }
    else
    {
        QMessageBox::information(NULL, "PROMPT(提示)", "LineDataCameraImage数据不全");
    }

    // 图像2
    if (RectVector_2.size() != 0)
    {
        S_Select_Rect_2.sxRect_2 = RectVector_2;
    }
    else
    {
        QMessageBox::information(NULL, "PROMPT(提示)", "RectDataCameraImage_2数据不全(未选择排除区域)");
    }

    if (RectLineVectors_2.size() == 4)
    {
        S_Select_Rect_2.RectAddLine_LV_2 = RectLineVectors_2[0];
        S_Select_Rect_2.RectAddLine_UL_2 = RectLineVectors_2[1];
        S_Select_Rect_2.RectAddLine_RV_2 = RectLineVectors_2[2];
        S_Select_Rect_2.RectAddLine_DL_2 = RectLineVectors_2[3];
    }
    else
    {
        QMessageBox::information(NULL, "PROMPT(提示)", "LineDataCameraImage_2数据不全");
    }
}


/*--------------@brief：实时显示-------------*/
/*--------------@note： -------------*/
void OpenMultiCamDlg::on_btnShowImage_clicked()
{
    m_isRealTimeProcess = true;
    if (FALSE == m_bStartGrabbing)
    {
       // QMessageBox::information(this,"提示",str_cn("Please start grabbing first!\r\n"));
        return;
    }
    doSoftwareOnce();
}








































