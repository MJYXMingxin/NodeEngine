/****************************************************************************
** Meta object code from reading C++ file 'NE_View.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/NE_View.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NE_View.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_NE_View_t {
    uint offsetsAndSizes[12];
    char stringdata0[8];
    char stringdata1[20];
    char stringdata2[1];
    char stringdata3[17];
    char stringdata4[5];
    char stringdata5[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_NE_View_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_NE_View_t qt_meta_stringdata_NE_View = {
    {
        QT_MOC_LITERAL(0, 7),  // "NE_View"
        QT_MOC_LITERAL(8, 19),  // "onItemDoubleClicked"
        QT_MOC_LITERAL(28, 0),  // ""
        QT_MOC_LITERAL(29, 16),  // "QTreeWidgetItem*"
        QT_MOC_LITERAL(46, 4),  // "item"
        QT_MOC_LITERAL(51, 6)   // "column"
    },
    "NE_View",
    "onItemDoubleClicked",
    "",
    "QTreeWidgetItem*",
    "item",
    "column"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_NE_View[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   20,    2, 0x08,    1 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,

       0        // eod
};

Q_CONSTINIT const QMetaObject NE_View::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsView::staticMetaObject>(),
    qt_meta_stringdata_NE_View.offsetsAndSizes,
    qt_meta_data_NE_View,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_NE_View_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<NE_View, std::true_type>,
        // method 'onItemDoubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTreeWidgetItem *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void NE_View::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NE_View *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onItemDoubleClicked((*reinterpret_cast< std::add_pointer_t<QTreeWidgetItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject *NE_View::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NE_View::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NE_View.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int NE_View::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
