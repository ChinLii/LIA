/****************************************************************************
** Meta object code from reading C++ file 'imageview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../imageview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imageview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ImageView_t {
    QByteArrayData data[15];
    char stringdata[198];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageView_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageView_t qt_meta_stringdata_ImageView = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ImageView"
QT_MOC_LITERAL(1, 10, 6), // "zoomIn"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 7), // "zoomOut"
QT_MOC_LITERAL(4, 26, 9), // "saveImage"
QT_MOC_LITERAL(5, 36, 16), // "leftClickOnPanel"
QT_MOC_LITERAL(6, 53, 17), // "rightClickOnPanel"
QT_MOC_LITERAL(7, 71, 10), // "backToHome"
QT_MOC_LITERAL(8, 82, 13), // "backToProject"
QT_MOC_LITERAL(9, 96, 12), // "backToFolder"
QT_MOC_LITERAL(10, 109, 17), // "enterOriginalMode"
QT_MOC_LITERAL(11, 127, 18), // "enterProcessedMode"
QT_MOC_LITERAL(12, 146, 17), // "enterEditableMode"
QT_MOC_LITERAL(13, 164, 12), // "processImage"
QT_MOC_LITERAL(14, 177, 20) // "setSliderValueLabels"

    },
    "ImageView\0zoomIn\0\0zoomOut\0saveImage\0"
    "leftClickOnPanel\0rightClickOnPanel\0"
    "backToHome\0backToProject\0backToFolder\0"
    "enterOriginalMode\0enterProcessedMode\0"
    "enterEditableMode\0processImage\0"
    "setSliderValueLabels"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    0,   89,    2, 0x08 /* Private */,
      13,    0,   90,    2, 0x08 /* Private */,
      14,    0,   91,    2, 0x08 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ImageView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ImageView *_t = static_cast<ImageView *>(_o);
        switch (_id) {
        case 0: _t->zoomIn(); break;
        case 1: _t->zoomOut(); break;
        case 2: _t->saveImage(); break;
        case 3: _t->leftClickOnPanel(); break;
        case 4: _t->rightClickOnPanel(); break;
        case 5: _t->backToHome(); break;
        case 6: _t->backToProject(); break;
        case 7: _t->backToFolder(); break;
        case 8: _t->enterOriginalMode(); break;
        case 9: _t->enterProcessedMode(); break;
        case 10: _t->enterEditableMode(); break;
        case 11: _t->processImage(); break;
        case 12: _t->setSliderValueLabels(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ImageView::staticMetaObject = {
    { &AbstractView::staticMetaObject, qt_meta_stringdata_ImageView.data,
      qt_meta_data_ImageView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ImageView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ImageView.stringdata))
        return static_cast<void*>(const_cast< ImageView*>(this));
    return AbstractView::qt_metacast(_clname);
}

int ImageView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
