#ifndef CMD_DEF_H
#define CMD_DEF_H

#include <QString>

//#define  M_PI 3.14

#define str_cn QString::fromLocal8Bit

#define INDEX_CAMPARA_SHOW           1       //显示相机设置界面
#define INDEX_FINDCENTER_SHOW        2       //显示查找直线和中心的设置界面
#define INDEX_SERIALPORT_SHOW        3       //显示查找直线和中心的设置界面
#define INDEX_DetectingCircle_SHOW   4       //标记圆设置界面

#define MAX_DEVICE_NUM            2       //相机最大个数

#define CMD_MEWTOCOL_HEADER       0x25    //mewtocol %开头
#define CMD_MEWTOCOL_END          0x0D    //mewtocol 回车符号结束

#define CMD_RCS                   0x01    //读单个PLC触点
#define CMD_RCP                   0x02    //读多个PLC触点
#define CMD_RCC                   0x03    //读多个PLC触点（字单位）
#define CMD_RDD                   0x04    //读单个PLC数据
#define CMD_RDDW                  0x05    //读多个PLC数据

#define CMD_WDD                   0x06    //写单个PLC数据
#define CMD_WDDW                  0x07    //写多个PLC数据
#define CMD_WCS                   0x08    //写单个PLC触点

 


#endif // CMD_DEF_H
