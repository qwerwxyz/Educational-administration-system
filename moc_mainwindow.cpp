/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../server/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 11), // "new_connect"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 4), // "read"
QT_MOC_LITERAL(4, 29, 6), // "cinput"
QT_MOC_LITERAL(5, 36, 6), // "oinput"
QT_MOC_LITERAL(6, 43, 9), // "studentin"
QT_MOC_LITERAL(7, 53, 9), // "teacherin"
QT_MOC_LITERAL(8, 63, 7), // "savecom"
QT_MOC_LITERAL(9, 71, 7), // "saveopt"
QT_MOC_LITERAL(10, 79, 11), // "savestudent"
QT_MOC_LITERAL(11, 91, 11), // "saveteacher"
QT_MOC_LITERAL(12, 103, 7), // "update1"
QT_MOC_LITERAL(13, 111, 11), // "comparenum1"
QT_MOC_LITERAL(14, 123, 8), // "stu_data"
QT_MOC_LITERAL(15, 132, 1), // "a"
QT_MOC_LITERAL(16, 134, 1), // "b"
QT_MOC_LITERAL(17, 136, 11), // "comparenum2"
QT_MOC_LITERAL(18, 148, 11), // "comparenum3"
QT_MOC_LITERAL(19, 160, 11) // "comparenum4"

    },
    "MainWindow\0new_connect\0\0read\0cinput\0"
    "oinput\0studentin\0teacherin\0savecom\0"
    "saveopt\0savestudent\0saveteacher\0update1\0"
    "comparenum1\0stu_data\0a\0b\0comparenum2\0"
    "comparenum3\0comparenum4"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08 /* Private */,
       3,    0,   90,    2, 0x08 /* Private */,
       4,    0,   91,    2, 0x08 /* Private */,
       5,    0,   92,    2, 0x08 /* Private */,
       6,    0,   93,    2, 0x08 /* Private */,
       7,    0,   94,    2, 0x08 /* Private */,
       8,    0,   95,    2, 0x08 /* Private */,
       9,    0,   96,    2, 0x08 /* Private */,
      10,    0,   97,    2, 0x08 /* Private */,
      11,    0,   98,    2, 0x08 /* Private */,
      12,    0,   99,    2, 0x08 /* Private */,
      13,    2,  100,    2, 0x08 /* Private */,
      17,    2,  105,    2, 0x08 /* Private */,
      18,    2,  110,    2, 0x08 /* Private */,
      19,    2,  115,    2, 0x08 /* Private */,

 // slots: parameters
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
    QMetaType::Bool, 0x80000000 | 14, 0x80000000 | 14,   15,   16,
    QMetaType::Bool, 0x80000000 | 14, 0x80000000 | 14,   15,   16,
    QMetaType::Bool, 0x80000000 | 14, 0x80000000 | 14,   15,   16,
    QMetaType::Bool, 0x80000000 | 14, 0x80000000 | 14,   15,   16,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->new_connect(); break;
        case 1: _t->read(); break;
        case 2: _t->cinput(); break;
        case 3: _t->oinput(); break;
        case 4: _t->studentin(); break;
        case 5: _t->teacherin(); break;
        case 6: _t->savecom(); break;
        case 7: _t->saveopt(); break;
        case 8: _t->savestudent(); break;
        case 9: _t->saveteacher(); break;
        case 10: _t->update1(); break;
        case 11: { bool _r = _t->comparenum1((*reinterpret_cast< const stu_data(*)>(_a[1])),(*reinterpret_cast< const stu_data(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 12: { bool _r = _t->comparenum2((*reinterpret_cast< const stu_data(*)>(_a[1])),(*reinterpret_cast< const stu_data(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 13: { bool _r = _t->comparenum3((*reinterpret_cast< const stu_data(*)>(_a[1])),(*reinterpret_cast< const stu_data(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 14: { bool _r = _t->comparenum4((*reinterpret_cast< const stu_data(*)>(_a[1])),(*reinterpret_cast< const stu_data(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
