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
    QByteArrayData data[9];
    char stringdata0[138];
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
QT_MOC_LITERAL(8, 110, 27) // "on_btnSelectProcess_clicked"

    },
    "FindRectCenterDlg\0receiveUpImg\0\0cv::Mat\0"
    "UpImg\0index_Img\0on_btnPreProcess_clicked\0"
    "on_btnExcludeProcess_clicked\0"
    "on_btnSelectProcess_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FindRectCenterDlg[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x08 /* Private */,
       6,    0,   39,    2, 0x08 /* Private */,
       7,    0,   40,    2, 0x08 /* Private */,
       8,    0,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
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
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE