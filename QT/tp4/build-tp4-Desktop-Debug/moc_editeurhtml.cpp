/****************************************************************************
** Meta object code from reading C++ file 'editeurhtml.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../tp4/editeurhtml.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editeurhtml.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EditeurHTML_t {
    QByteArrayData data[17];
    char stringdata[210];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_EditeurHTML_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_EditeurHTML_t qt_meta_stringdata_EditeurHTML = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 7),
QT_MOC_LITERAL(2, 20, 0),
QT_MOC_LITERAL(3, 21, 8),
QT_MOC_LITERAL(4, 30, 8),
QT_MOC_LITERAL(5, 39, 10),
QT_MOC_LITERAL(6, 50, 15),
QT_MOC_LITERAL(7, 66, 13),
QT_MOC_LITERAL(8, 80, 14),
QT_MOC_LITERAL(9, 95, 12),
QT_MOC_LITERAL(10, 108, 14),
QT_MOC_LITERAL(11, 123, 8),
QT_MOC_LITERAL(12, 132, 18),
QT_MOC_LITERAL(13, 151, 10),
QT_MOC_LITERAL(14, 162, 12),
QT_MOC_LITERAL(15, 175, 21),
QT_MOC_LITERAL(16, 197, 11)
    },
    "EditeurHTML\0newFile\0\0openFile\0saveFile\0"
    "saveFileAs\0closeCurrentTab\0copySelection\0"
    "pasteSelection\0cutSelection\0setCurrentStat\0"
    "closeTab\0checkAvailableSave\0closeEvent\0"
    "QCloseEvent*\0currentTabNameChanged\0"
    "aboutDialog\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditeurHTML[] = {

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
       1,    0,   89,    2, 0x08,
       3,    0,   90,    2, 0x08,
       3,    1,   91,    2, 0x08,
       4,    0,   94,    2, 0x08,
       5,    0,   95,    2, 0x08,
       6,    0,   96,    2, 0x08,
       7,    0,   97,    2, 0x08,
       8,    0,   98,    2, 0x08,
       9,    0,   99,    2, 0x08,
      10,    1,  100,    2, 0x08,
      11,    1,  103,    2, 0x08,
      12,    1,  106,    2, 0x08,
      13,    1,  109,    2, 0x08,
      15,    1,  112,    2, 0x08,
      16,    0,  115,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 14,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,

       0        // eod
};

void EditeurHTML::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EditeurHTML *_t = static_cast<EditeurHTML *>(_o);
        switch (_id) {
        case 0: _t->newFile(); break;
        case 1: _t->openFile(); break;
        case 2: _t->openFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->saveFile(); break;
        case 4: _t->saveFileAs(); break;
        case 5: _t->closeCurrentTab(); break;
        case 6: _t->copySelection(); break;
        case 7: _t->pasteSelection(); break;
        case 8: _t->cutSelection(); break;
        case 9: _t->setCurrentStat((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->closeTab((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->checkAvailableSave((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 13: _t->currentTabNameChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->aboutDialog(); break;
        default: ;
        }
    }
}

const QMetaObject EditeurHTML::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_EditeurHTML.data,
      qt_meta_data_EditeurHTML,  qt_static_metacall, 0, 0}
};


const QMetaObject *EditeurHTML::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditeurHTML::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EditeurHTML.stringdata))
        return static_cast<void*>(const_cast< EditeurHTML*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int EditeurHTML::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
