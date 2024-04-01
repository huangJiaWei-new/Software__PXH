/****************************************************************************
** Meta object code from reading C++ file 'openmulticamdlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Pxh/camera/openmulticamdlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'openmulticamdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OpenMultiCamDlg_t {
    QByteArrayData data[70];
    char stringdata0[1041];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OpenMultiCamDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OpenMultiCamDlg_t qt_meta_stringdata_OpenMultiCamDlg = {
    {
QT_MOC_LITERAL(0, 0, 15), // "OpenMultiCamDlg"
QT_MOC_LITERAL(1, 16, 17), // "sigUpdatePicture1"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 17), // "sigUpdatePicture2"
QT_MOC_LITERAL(4, 53, 17), // "sigUpdatePicture3"
QT_MOC_LITERAL(5, 71, 17), // "sigUpdatePicture4"
QT_MOC_LITERAL(6, 89, 10), // "sigSendImg"
QT_MOC_LITERAL(7, 100, 7), // "cv::Mat"
QT_MOC_LITERAL(8, 108, 18), // "activateFindCenter"
QT_MOC_LITERAL(9, 127, 21), // "on_btnEnumCam_clicked"
QT_MOC_LITERAL(10, 149, 12), // "showErrorMsg"
QT_MOC_LITERAL(11, 162, 9), // "csMessage"
QT_MOC_LITERAL(12, 172, 9), // "nErrorNum"
QT_MOC_LITERAL(13, 182, 16), // "camCallBackInner"
QT_MOC_LITERAL(14, 199, 14), // "unsigned char*"
QT_MOC_LITERAL(15, 214, 5), // "pData"
QT_MOC_LITERAL(16, 220, 21), // "MV_FRAME_OUT_INFO_EX*"
QT_MOC_LITERAL(17, 242, 10), // "pFrameInfo"
QT_MOC_LITERAL(18, 253, 8), // "camIndex"
QT_MOC_LITERAL(19, 262, 14), // "frameCountInfo"
QT_MOC_LITERAL(20, 277, 11), // "convert2Mat"
QT_MOC_LITERAL(21, 289, 12), // "pstImageInfo"
QT_MOC_LITERAL(22, 302, 8), // "cv::Mat*"
QT_MOC_LITERAL(23, 311, 8), // "srcImage"
QT_MOC_LITERAL(24, 320, 7), // "RGB2BGR"
QT_MOC_LITERAL(25, 328, 8), // "pRgbData"
QT_MOC_LITERAL(26, 337, 6), // "nWidth"
QT_MOC_LITERAL(27, 344, 7), // "nHeight"
QT_MOC_LITERAL(28, 352, 18), // "startCamByCallBack"
QT_MOC_LITERAL(29, 371, 17), // "startCamByQThread"
QT_MOC_LITERAL(30, 389, 25), // "startCamByQThreadCallBack"
QT_MOC_LITERAL(31, 415, 21), // "startCamByBeginThread"
QT_MOC_LITERAL(32, 437, 14), // "timerUpdateFun"
QT_MOC_LITERAL(33, 452, 14), // "setTriggerMode"
QT_MOC_LITERAL(34, 467, 12), // "nTriggerMode"
QT_MOC_LITERAL(35, 480, 16), // "setTriggerSource"
QT_MOC_LITERAL(36, 497, 14), // "nTriggerSource"
QT_MOC_LITERAL(37, 512, 14), // "doSoftwareOnce"
QT_MOC_LITERAL(38, 527, 17), // "showUpCameraImage"
QT_MOC_LITERAL(39, 545, 8), // "cv::Mat&"
QT_MOC_LITERAL(40, 554, 13), // "UpCameraImage"
QT_MOC_LITERAL(41, 568, 19), // "showDownCameraImage"
QT_MOC_LITERAL(42, 588, 15), // "DownCameraImage"
QT_MOC_LITERAL(43, 604, 5), // "sobel"
QT_MOC_LITERAL(44, 610, 7), // "imageFp"
QT_MOC_LITERAL(45, 618, 12), // "binImageFunc"
QT_MOC_LITERAL(46, 631, 8), // "fit_line"
QT_MOC_LITERAL(47, 640, 10), // "S_RectLine"
QT_MOC_LITERAL(48, 651, 23), // "std::vector<cv::Point>&"
QT_MOC_LITERAL(49, 675, 8), // "pointsFp"
QT_MOC_LITERAL(50, 684, 15), // "getIntersection"
QT_MOC_LITERAL(51, 700, 9), // "cv::Point"
QT_MOC_LITERAL(52, 710, 11), // "S_RectLine&"
QT_MOC_LITERAL(53, 722, 3), // "fp1"
QT_MOC_LITERAL(54, 726, 3), // "fp2"
QT_MOC_LITERAL(55, 730, 12), // "intersection"
QT_MOC_LITERAL(56, 743, 7), // "S_Line&"
QT_MOC_LITERAL(57, 751, 21), // "on_btnOpenCam_clicked"
QT_MOC_LITERAL(58, 773, 23), // "on_btnStartAqui_clicked"
QT_MOC_LITERAL(59, 797, 18), // "on_btnStop_clicked"
QT_MOC_LITERAL(60, 816, 19), // "on_btnClose_clicked"
QT_MOC_LITERAL(61, 836, 27), // "on_btnContinuesMode_clicked"
QT_MOC_LITERAL(62, 864, 25), // "on_btnTriggerMode_clicked"
QT_MOC_LITERAL(63, 890, 25), // "on_btnTriggerExec_clicked"
QT_MOC_LITERAL(64, 916, 29), // "on_btnSetUpCameraLine_clicked"
QT_MOC_LITERAL(65, 946, 31), // "on_btnSetDownCameraLine_clicked"
QT_MOC_LITERAL(66, 978, 18), // "on_btnJson_clicked"
QT_MOC_LITERAL(67, 997, 10), // "revCmdList"
QT_MOC_LITERAL(68, 1008, 8), // "cmd_list"
QT_MOC_LITERAL(69, 1017, 23) // "on_btnShowImage_clicked"

    },
    "OpenMultiCamDlg\0sigUpdatePicture1\0\0"
    "sigUpdatePicture2\0sigUpdatePicture3\0"
    "sigUpdatePicture4\0sigSendImg\0cv::Mat\0"
    "activateFindCenter\0on_btnEnumCam_clicked\0"
    "showErrorMsg\0csMessage\0nErrorNum\0"
    "camCallBackInner\0unsigned char*\0pData\0"
    "MV_FRAME_OUT_INFO_EX*\0pFrameInfo\0"
    "camIndex\0frameCountInfo\0convert2Mat\0"
    "pstImageInfo\0cv::Mat*\0srcImage\0RGB2BGR\0"
    "pRgbData\0nWidth\0nHeight\0startCamByCallBack\0"
    "startCamByQThread\0startCamByQThreadCallBack\0"
    "startCamByBeginThread\0timerUpdateFun\0"
    "setTriggerMode\0nTriggerMode\0"
    "setTriggerSource\0nTriggerSource\0"
    "doSoftwareOnce\0showUpCameraImage\0"
    "cv::Mat&\0UpCameraImage\0showDownCameraImage\0"
    "DownCameraImage\0sobel\0imageFp\0"
    "binImageFunc\0fit_line\0S_RectLine\0"
    "std::vector<cv::Point>&\0pointsFp\0"
    "getIntersection\0cv::Point\0S_RectLine&\0"
    "fp1\0fp2\0intersection\0S_Line&\0"
    "on_btnOpenCam_clicked\0on_btnStartAqui_clicked\0"
    "on_btnStop_clicked\0on_btnClose_clicked\0"
    "on_btnContinuesMode_clicked\0"
    "on_btnTriggerMode_clicked\0"
    "on_btnTriggerExec_clicked\0"
    "on_btnSetUpCameraLine_clicked\0"
    "on_btnSetDownCameraLine_clicked\0"
    "on_btnJson_clicked\0revCmdList\0cmd_list\0"
    "on_btnShowImage_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OpenMultiCamDlg[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      38,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  204,    2, 0x06 /* Public */,
       3,    0,  205,    2, 0x06 /* Public */,
       4,    0,  206,    2, 0x06 /* Public */,
       5,    0,  207,    2, 0x06 /* Public */,
       6,    2,  208,    2, 0x06 /* Public */,
       8,    0,  213,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,  214,    2, 0x08 /* Private */,
      10,    2,  215,    2, 0x08 /* Private */,
      13,    4,  220,    2, 0x08 /* Private */,
      20,    3,  229,    2, 0x08 /* Private */,
      24,    3,  236,    2, 0x08 /* Private */,
      28,    0,  243,    2, 0x08 /* Private */,
      29,    0,  244,    2, 0x08 /* Private */,
      30,    0,  245,    2, 0x08 /* Private */,
      31,    0,  246,    2, 0x08 /* Private */,
      32,    0,  247,    2, 0x08 /* Private */,
      33,    1,  248,    2, 0x08 /* Private */,
      35,    1,  251,    2, 0x08 /* Private */,
      37,    0,  254,    2, 0x08 /* Private */,
      38,    1,  255,    2, 0x08 /* Private */,
      41,    1,  258,    2, 0x08 /* Private */,
      43,    1,  261,    2, 0x08 /* Private */,
      45,    0,  264,    2, 0x08 /* Private */,
      46,    1,  265,    2, 0x08 /* Private */,
      50,    2,  268,    2, 0x08 /* Private */,
      55,    2,  273,    2, 0x08 /* Private */,
      57,    0,  278,    2, 0x08 /* Private */,
      58,    0,  279,    2, 0x08 /* Private */,
      59,    0,  280,    2, 0x08 /* Private */,
      60,    0,  281,    2, 0x08 /* Private */,
      61,    0,  282,    2, 0x08 /* Private */,
      62,    0,  283,    2, 0x08 /* Private */,
      63,    0,  284,    2, 0x08 /* Private */,
      64,    0,  285,    2, 0x08 /* Private */,
      65,    0,  286,    2, 0x08 /* Private */,
      66,    0,  287,    2, 0x08 /* Private */,
      67,    1,  288,    2, 0x08 /* Private */,
      69,    0,  291,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Int,    2,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::LongLong,   11,   12,
    QMetaType::Void, 0x80000000 | 14, 0x80000000 | 16, QMetaType::Int, QMetaType::QString,   15,   17,   18,   19,
    QMetaType::Bool, 0x80000000 | 16, 0x80000000 | 14, 0x80000000 | 22,   21,   15,   23,
    QMetaType::Int, 0x80000000 | 14, QMetaType::UInt, QMetaType::UInt,   25,   26,   27,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   34,
    QMetaType::Void, QMetaType::Int,   36,
    QMetaType::Void,
    0x80000000 | 7, 0x80000000 | 39,   40,
    0x80000000 | 7, 0x80000000 | 39,   42,
    QMetaType::Bool, 0x80000000 | 39,   44,
    QMetaType::Bool,
    0x80000000 | 47, 0x80000000 | 48,   49,
    0x80000000 | 51, 0x80000000 | 52, 0x80000000 | 52,   53,   54,
    0x80000000 | 51, 0x80000000 | 56, 0x80000000 | 56,   53,   54,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   68,
    QMetaType::Void,

       0        // eod
};

void OpenMultiCamDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OpenMultiCamDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigUpdatePicture1(); break;
        case 1: _t->sigUpdatePicture2(); break;
        case 2: _t->sigUpdatePicture3(); break;
        case 3: _t->sigUpdatePicture4(); break;
        case 4: _t->sigSendImg((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->activateFindCenter(); break;
        case 6: _t->on_btnEnumCam_clicked(); break;
        case 7: _t->showErrorMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< long long(*)>(_a[2]))); break;
        case 8: _t->camCallBackInner((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< MV_FRAME_OUT_INFO_EX*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 9: { bool _r = _t->convert2Mat((*reinterpret_cast< MV_FRAME_OUT_INFO_EX*(*)>(_a[1])),(*reinterpret_cast< unsigned char*(*)>(_a[2])),(*reinterpret_cast< cv::Mat*(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { int _r = _t->RGB2BGR((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 11: _t->startCamByCallBack(); break;
        case 12: _t->startCamByQThread(); break;
        case 13: _t->startCamByQThreadCallBack(); break;
        case 14: _t->startCamByBeginThread(); break;
        case 15: _t->timerUpdateFun(); break;
        case 16: _t->setTriggerMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->setTriggerSource((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->doSoftwareOnce(); break;
        case 19: { cv::Mat _r = _t->showUpCameraImage((*reinterpret_cast< cv::Mat(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< cv::Mat*>(_a[0]) = std::move(_r); }  break;
        case 20: { cv::Mat _r = _t->showDownCameraImage((*reinterpret_cast< cv::Mat(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< cv::Mat*>(_a[0]) = std::move(_r); }  break;
        case 21: { bool _r = _t->sobel((*reinterpret_cast< cv::Mat(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 22: { bool _r = _t->binImageFunc();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 23: { S_RectLine _r = _t->fit_line((*reinterpret_cast< std::vector<cv::Point>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< S_RectLine*>(_a[0]) = std::move(_r); }  break;
        case 24: { cv::Point _r = _t->getIntersection((*reinterpret_cast< S_RectLine(*)>(_a[1])),(*reinterpret_cast< S_RectLine(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< cv::Point*>(_a[0]) = std::move(_r); }  break;
        case 25: { cv::Point _r = _t->intersection((*reinterpret_cast< S_Line(*)>(_a[1])),(*reinterpret_cast< S_Line(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< cv::Point*>(_a[0]) = std::move(_r); }  break;
        case 26: _t->on_btnOpenCam_clicked(); break;
        case 27: _t->on_btnStartAqui_clicked(); break;
        case 28: _t->on_btnStop_clicked(); break;
        case 29: _t->on_btnClose_clicked(); break;
        case 30: _t->on_btnContinuesMode_clicked(); break;
        case 31: _t->on_btnTriggerMode_clicked(); break;
        case 32: _t->on_btnTriggerExec_clicked(); break;
        case 33: _t->on_btnSetUpCameraLine_clicked(); break;
        case 34: _t->on_btnSetDownCameraLine_clicked(); break;
        case 35: _t->on_btnJson_clicked(); break;
        case 36: _t->revCmdList((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 37: _t->on_btnShowImage_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (OpenMultiCamDlg::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OpenMultiCamDlg::sigUpdatePicture1)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (OpenMultiCamDlg::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OpenMultiCamDlg::sigUpdatePicture2)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (OpenMultiCamDlg::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OpenMultiCamDlg::sigUpdatePicture3)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (OpenMultiCamDlg::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OpenMultiCamDlg::sigUpdatePicture4)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (OpenMultiCamDlg::*)(cv::Mat , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OpenMultiCamDlg::sigSendImg)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (OpenMultiCamDlg::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OpenMultiCamDlg::activateFindCenter)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject OpenMultiCamDlg::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_OpenMultiCamDlg.data,
    qt_meta_data_OpenMultiCamDlg,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *OpenMultiCamDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OpenMultiCamDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OpenMultiCamDlg.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int OpenMultiCamDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 38)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 38;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 38)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 38;
    }
    return _id;
}

// SIGNAL 0
void OpenMultiCamDlg::sigUpdatePicture1()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void OpenMultiCamDlg::sigUpdatePicture2()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void OpenMultiCamDlg::sigUpdatePicture3()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void OpenMultiCamDlg::sigUpdatePicture4()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void OpenMultiCamDlg::sigSendImg(cv::Mat _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void OpenMultiCamDlg::activateFindCenter()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
