/****************************************************************************
** Meta object code from reading C++ file 'findrectcenterdlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Pxh/findcenter/findrectcenterdlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'findrectcenterdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FindRectCenterDlg_t {
    QByteArrayData data[20];
    char stringdata0[449];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FindRectCenterDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FindRectCenterDlg_t qt_meta_stringdata_FindRectCenterDlg = {
    {
QT_MOC_LITERAL(0, 0, 17), // "FindRectCenterDlg"
QT_MOC_LITERAL(1, 18, 12), // "receiveUpImg"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 7), // "cv::Mat"
QT_MOC_LITERAL(4, 40, 5), // "UpImg"
QT_MOC_LITERAL(5, 46, 9), // "index_Img"
QT_MOC_LITERAL(6, 56, 24), // "on_btnPreProcess_clicked"
QT_MOC_LITERAL(7, 81, 28), // "on_btnExcludeProcess_clicked"
QT_MOC_LITERAL(8, 110, 27), // "on_btnSelectProcess_clicked"
QT_MOC_LITERAL(9, 138, 29), // "on_btnDrawLeftProcess_clicked"
QT_MOC_LITERAL(10, 168, 30), // "on_btnDrawRightProcess_clicked"
QT_MOC_LITERAL(11, 199, 27), // "on_btnDrawUpProcess_clicked"
QT_MOC_LITERAL(12, 227, 31), // "on_btnDrawBottomProcess_clicked"
QT_MOC_LITERAL(13, 259, 28), // "on_btnFitLeftProcess_clicked"
QT_MOC_LITERAL(14, 288, 29), // "on_btnFitRightProcess_clicked"
QT_MOC_LITERAL(15, 318, 26), // "on_btnFitUpProcess_clicked"
QT_MOC_LITERAL(16, 345, 30), // "on_btnFitBottomProcess_clicked"
QT_MOC_LITERAL(17, 376, 27), // "on_btnCenterProcess_clicked"
QT_MOC_LITERAL(18, 404, 25), // "on_btnJsonProcess_clicked"
QT_MOC_LITERAL(19, 430, 18) // "on_btnUndo_clicked"

    },
    "FindRectCenterDlg\0receiveUpImg\0\0cv::Mat\0"
    "UpImg\0index_Img\0on_btnPreProcess_clicked\0"
    "on_btnExcludeProcess_clicked\0"
    "on_btnSelectProcess_clicked\0"
    "on_btnDrawLeftProcess_clicked\0"
    "on_btnDrawRightProcess_clicked\0"
    "on_btnDrawUpProcess_clicked\0"
    "on_btnDrawBottomProcess_clicked\0"
    "on_btnFitLeftProcess_clicked\0"
    "on_btnFitRightProcess_clicked\0"
    "on_btnFitUpProcess_clicked\0"
    "on_btnFitBottomProcess_clicked\0"
    "on_btnCenterProcess_clicked\0"
    "on_btnJsonProcess_clicked\0on_btnUndo_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FindRectCenterDlg[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   89,    2, 0x08 /* Private */,
       6,    0,   94,    2, 0x08 /* Private */,
       7,    0,   95,    2, 0x08 /* Private */,
       8,    0,   96,    2, 0x08 /* Private */,
       9,    0,   97,    2, 0x08 /* Private */,
      10,    0,   98,    2, 0x08 /* Private */,
      11,    0,   99,    2, 0x08 /* Private */,
      12,    0,  100,    2, 0x08 /* Private */,
      13,    0,  101,    2, 0x08 /* Private */,
      14,    0,  102,    2, 0x08 /* Private */,
      15,    0,  103,    2, 0x08 /* Private */,
      16,    0,  104,    2, 0x08 /* Private */,
      17,    0,  105,    2, 0x08 /* Private */,
      18,    0,  106,    2, 0x08 /* Private */,
      19,    0,  107,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FindRectCenterDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FindRectCenterDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->receiveUpImg((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->on_btnPreProcess_clicked(); break;
        case 2: _t->on_btnExcludeProcess_clicked(); break;
        case 3: _t->on_btnSelectProcess_clicked(); break;
        case 4: _t->on_btnDrawLeftProcess_clicked(); break;
        case 5: _t->on_btnDrawRightProcess_clicked(); break;
        case 6: _t->on_btnDrawUpProcess_clicked(); break;
        case 7: _t->on_btnDrawBottomProcess_clicked(); break;
        case 8: _t->on_btnFitLeftProcess_clicked(); break;
        case 9: _t->on_btnFitRightProcess_clicked(); break;
        case 10: _t->on_btnFitUpProcess_clicked(); break;
        case 11: _t->on_btnFitBottomProcess_clicked(); break;
        case 12: _t->on_btnCenterProcess_clicked(); break;
        case 13: _t->on_btnJsonProcess_clicked(); break;
        case 14: _t->on_btnUndo_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FindRectCenterDlg::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_FindRectCenterDlg.data,
    qt_meta_data_FindRectCenterDlg,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FindRectCenterDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FindRectCenterDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FindRectCenterDlg.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int FindRectCenterDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
