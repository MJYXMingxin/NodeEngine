/****************************************************************************
** Meta object code from reading C++ file 'NE_Line_Basic.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/NE_Line_Basic.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NE_Line_Basic.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_NE_Line_Basic_t {
    uint offsetsAndSizes[2];
    char stringdata0[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_NE_Line_Basic_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_NE_Line_Basic_t qt_meta_stringdata_NE_Line_Basic = {
    {
        QT_MOC_LITERAL(0, 13)   // "NE_Line_Basic"
    },
    "NE_Line_Basic"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_NE_Line_Basic[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject NE_Line_Basic::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_NE_Line_Basic.offsetsAndSizes,
    qt_meta_data_NE_Line_Basic,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_NE_Line_Basic_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<NE_Line_Basic, std::true_type>
    >,
    nullptr
} };

void NE_Line_Basic::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *NE_Line_Basic::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NE_Line_Basic::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NE_Line_Basic.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsPathItem"))
        return static_cast< QGraphicsPathItem*>(this);
    return QObject::qt_metacast(_clname);
}

int NE_Line_Basic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_stringdata_NE_Drag_Line_t {
    uint offsetsAndSizes[2];
    char stringdata0[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_NE_Drag_Line_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_NE_Drag_Line_t qt_meta_stringdata_NE_Drag_Line = {
    {
        QT_MOC_LITERAL(0, 12)   // "NE_Drag_Line"
    },
    "NE_Drag_Line"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_NE_Drag_Line[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject NE_Drag_Line::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_NE_Drag_Line.offsetsAndSizes,
    qt_meta_data_NE_Drag_Line,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_NE_Drag_Line_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<NE_Drag_Line, std::true_type>
    >,
    nullptr
} };

void NE_Drag_Line::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *NE_Drag_Line::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NE_Drag_Line::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NE_Drag_Line.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsPathItem"))
        return static_cast< QGraphicsPathItem*>(this);
    return QObject::qt_metacast(_clname);
}

int NE_Drag_Line::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
