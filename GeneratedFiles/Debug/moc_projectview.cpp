/****************************************************************************
** Meta object code from reading C++ file 'projectview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../projectview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'projectview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ProjectView_t {
    QByteArrayData data[9];
    char stringdata[83];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProjectView_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProjectView_t qt_meta_stringdata_ProjectView = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ProjectView"
QT_MOC_LITERAL(1, 12, 15), // "updateSearchBar"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 12), // "deleteFolder"
QT_MOC_LITERAL(4, 42, 10), // "backToHome"
QT_MOC_LITERAL(5, 53, 9), // "newFolder"
QT_MOC_LITERAL(6, 63, 11), // "enterFolder"
QT_MOC_LITERAL(7, 75, 3), // "row"
QT_MOC_LITERAL(8, 79, 3) // "col"

    },
    "ProjectView\0updateSearchBar\0\0deleteFolder\0"
    "backToHome\0newFolder\0enterFolder\0row\0"
    "col"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProjectView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    2,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,

       0        // eod
};

void ProjectView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ProjectView *_t = static_cast<ProjectView *>(_o);
        switch (_id) {
        case 0: _t->updateSearchBar(); break;
        case 1: _t->deleteFolder(); break;
        case 2: _t->backToHome(); break;
        case 3: _t->newFolder(); break;
        case 4: _t->enterFolder((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject ProjectView::staticMetaObject = {
    { &AbstractView::staticMetaObject, qt_meta_stringdata_ProjectView.data,
      qt_meta_data_ProjectView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ProjectView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProjectView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ProjectView.stringdata))
        return static_cast<void*>(const_cast< ProjectView*>(this));
    return AbstractView::qt_metacast(_clname);
}

int ProjectView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
