/****************************************************************************
** Meta object code from reading C++ file 'camparadialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Pxh/camera/camparadialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'camparadialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CamParaDialog_t {
    QByteArrayData data[26];
    char stringdata0[415];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CamParaDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CamParaDialog_t qt_meta_stringdata_CamParaDialog = {
    {
QT_MOC_LITERAL(0, 0, 13), // "CamParaDialog"
QT_MOC_LITERAL(1, 14, 13), // "imageCaptured"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 3), // "Mat"
QT_MOC_LITERAL(4, 33, 14), // "imageCaptured2"
QT_MOC_LITERAL(5, 48, 17), // "ShowimageCaptured"
QT_MOC_LITERAL(6, 66, 18), // "ShowimageCaptured2"
QT_MOC_LITERAL(7, 85, 17), // "on_bnEnum_clicked"
QT_MOC_LITERAL(8, 103, 17), // "on_bnOpen_clicked"
QT_MOC_LITERAL(9, 121, 18), // "on_bnClose_clicked"
QT_MOC_LITERAL(10, 140, 26), // "on_bnContinuesMode_clicked"
QT_MOC_LITERAL(11, 167, 24), // "on_bnTriggerMode_clicked"
QT_MOC_LITERAL(12, 192, 18), // "on_bnStart_clicked"
QT_MOC_LITERAL(13, 211, 17), // "on_bnStop_clicked"
QT_MOC_LITERAL(14, 229, 29), // "on_cbSoftTrigger_stateChanged"
QT_MOC_LITERAL(15, 259, 4), // "arg1"
QT_MOC_LITERAL(16, 264, 24), // "on_cbSoftTrigger_clicked"
QT_MOC_LITERAL(17, 289, 24), // "on_bnTriggerExec_clicked"
QT_MOC_LITERAL(18, 314, 21), // "on_bnGetParam_clicked"
QT_MOC_LITERAL(19, 336, 21), // "on_bnSetParam_clicked"
QT_MOC_LITERAL(20, 358, 7), // "RGB2BGR"
QT_MOC_LITERAL(21, 366, 14), // "unsigned char*"
QT_MOC_LITERAL(22, 381, 8), // "pRgbData"
QT_MOC_LITERAL(23, 390, 6), // "nWidth"
QT_MOC_LITERAL(24, 397, 7), // "nHeight"
QT_MOC_LITERAL(25, 405, 9) // "sendImage"

    },
    "CamParaDialog\0imageCaptured\0\0Mat\0"
    "imageCaptured2\0ShowimageCaptured\0"
    "ShowimageCaptured2\0on_bnEnum_clicked\0"
    "on_bnOpen_clicked\0on_bnClose_clicked\0"
    "on_bnContinuesMode_clicked\0"
    "on_bnTriggerMode_clicked\0on_bnStart_clicked\0"
    "on_bnStop_clicked\0on_cbSoftTrigger_stateChanged\0"
    "arg1\0on_cbSoftTrigger_clicked\0"
    "on_bnTriggerExec_clicked\0on_bnGetParam_clicked\0"
    "on_bnSetParam_clicked\0RGB2BGR\0"
    "unsigned char*\0pRgbData\0nWidth\0nHeight\0"
    "sendImage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CamParaDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  104,    2, 0x06 /* Public */,
       4,    1,  107,    2, 0x06 /* Public */,
       5,    1,  110,    2, 0x06 /* Public */,
       6,    1,  113,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,  116,    2, 0x0a /* Public */,
       8,    0,  117,    2, 0x0a /* Public */,
       9,    0,  118,    2, 0x0a /* Public */,
      10,    0,  119,    2, 0x0a /* Public */,
      11,    0,  120,    2, 0x0a /* Public */,
      12,    0,  121,    2, 0x0a /* Public */,
      13,    0,  122,    2, 0x0a /* Public */,
      14,    1,  123,    2, 0x0a /* Public */,
      16,    0,  126,    2, 0x0a /* Public */,
      17,    0,  127,    2, 0x0a /* Public */,
      18,    0,  128,    2, 0x0a /* Public */,
      19,    0,  129,    2, 0x0a /* Public */,
      20,    3,  130,    2, 0x0a /* Public */,
      25,    0,  137,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int, 0x80000000 | 21, QMetaType::UInt, QMetaType::UInt,   22,   23,   24,
    QMetaType::Bool,

       0        // eod
};

void CamParaDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CamParaDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->imageCaptured((*reinterpret_cast< Mat(*)>(_a[1]))); break;
        case 1: _t->imageCaptured2((*reinterpret_cast< Mat(*)>(_a[1]))); break;
        case 2: _t->ShowimageCaptured((*reinterpret_cast< Mat(*)>(_a[1]))); break;
        case 3: _t->ShowimageCaptured2((*reinterpret_cast< Mat(*)>(_a[1]))); break;
        case 4: _t->on_bnEnum_clicked(); break;
        case 5: _t->on_bnOpen_clicked(); break;
        case 6: _t->on_bnClose_clicked(); break;
        case 7: _t->on_bnContinuesMode_clicked(); break;
        case 8: _t->on_bnTriggerMode_clicked(); break;
        case 9: _t->on_bnStart_clicked(); break;
        case 10: _t->on_bnStop_clicked(); break;
        case 11: _t->on_cbSoftTrigger_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_cbSoftTrigger_clicked(); break;
        case 13: _t->on_bnTriggerExec_clicked(); break;
        case 14: _t->on_bnGetParam_clicked(); break;
        case 15: _t->on_bnSetParam_clicked(); break;
        case 16: { int _r = _t->RGB2BGR((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 17: { bool _r = _t->sendImage();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CamParaDialog::*)(Mat );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CamParaDialog::imageCaptured)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CamParaDialog::*)(Mat );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CamParaDialog::imageCaptured2)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CamParaDialog::*)(Mat );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CamParaDialog::ShowimageCaptured)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CamParaDialog::*)(Mat );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CamParaDialog::ShowimageCaptured2)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CamParaDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CamParaDialog.data,
    qt_meta_data_CamParaDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CamParaDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CamParaDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CamParaDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int CamParaDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void CamParaDialog::imageCaptured(Mat _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CamParaDialog::imageCaptured2(Mat _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CamParaDialog::ShowimageCaptured(Mat _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CamParaDialog::ShowimageCaptured2(Mat _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
