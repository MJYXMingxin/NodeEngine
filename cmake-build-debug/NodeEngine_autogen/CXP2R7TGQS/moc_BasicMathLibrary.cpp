/****************************************************************************
** Meta object code from reading C++ file 'BasicMathLibrary.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/nodes/BasicMathLibrary.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BasicMathLibrary.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_AddNode_t {
    uint offsetsAndSizes[4];
    char stringdata0[8];
    char stringdata1[1];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_AddNode_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_AddNode_t qt_meta_stringdata_AddNode = {
    {
        QT_MOC_LITERAL(0, 7),  // "AddNode"
        QT_MOC_LITERAL(8, 0)   // ""
    },
    "AddNode",
    ""
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_AddNode[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   15, // constructors
       0,       // flags
       0,       // signalCount

 // constructors: parameters
    0x80000000 | 1,

 // constructors: name, argc, parameters, tag, flags, initial metatype offsets
       0,    0,   14,    1, 0x0e,    1 /* Public */,

       0        // eod
};

Q_CONSTINIT const QMetaObject AddNode::staticMetaObject = { {
    QMetaObject::SuperData::link<NE_Node::staticMetaObject>(),
    qt_meta_stringdata_AddNode.offsetsAndSizes,
    qt_meta_data_AddNode,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_AddNode_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<AddNode, std::true_type>
    >,
    nullptr
} };

void AddNode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { AddNode *_r = new AddNode();
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        default: break;
        }
    }
    (void)_o;
}

const QMetaObject *AddNode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AddNode::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AddNode.stringdata0))
        return static_cast<void*>(this);
    return NE_Node::qt_metacast(_clname);
}

int AddNode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = NE_Node::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_stringdata_SubtractNode_t {
    uint offsetsAndSizes[4];
    char stringdata0[13];
    char stringdata1[1];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_SubtractNode_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_SubtractNode_t qt_meta_stringdata_SubtractNode = {
    {
        QT_MOC_LITERAL(0, 12),  // "SubtractNode"
        QT_MOC_LITERAL(13, 0)   // ""
    },
    "SubtractNode",
    ""
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_SubtractNode[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   15, // constructors
       0,       // flags
       0,       // signalCount

 // constructors: parameters
    0x80000000 | 1,

 // constructors: name, argc, parameters, tag, flags, initial metatype offsets
       0,    0,   14,    1, 0x0e,    1 /* Public */,

       0        // eod
};

Q_CONSTINIT const QMetaObject SubtractNode::staticMetaObject = { {
    QMetaObject::SuperData::link<NE_Node::staticMetaObject>(),
    qt_meta_stringdata_SubtractNode.offsetsAndSizes,
    qt_meta_data_SubtractNode,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_SubtractNode_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SubtractNode, std::true_type>
    >,
    nullptr
} };

void SubtractNode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { SubtractNode *_r = new SubtractNode();
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        default: break;
        }
    }
    (void)_o;
}

const QMetaObject *SubtractNode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SubtractNode::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SubtractNode.stringdata0))
        return static_cast<void*>(this);
    return NE_Node::qt_metacast(_clname);
}

int SubtractNode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = NE_Node::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_stringdata_MultiplyNode_t {
    uint offsetsAndSizes[4];
    char stringdata0[13];
    char stringdata1[1];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MultiplyNode_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_MultiplyNode_t qt_meta_stringdata_MultiplyNode = {
    {
        QT_MOC_LITERAL(0, 12),  // "MultiplyNode"
        QT_MOC_LITERAL(13, 0)   // ""
    },
    "MultiplyNode",
    ""
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_MultiplyNode[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   15, // constructors
       0,       // flags
       0,       // signalCount

 // constructors: parameters
    0x80000000 | 1,

 // constructors: name, argc, parameters, tag, flags, initial metatype offsets
       0,    0,   14,    1, 0x0e,    1 /* Public */,

       0        // eod
};

Q_CONSTINIT const QMetaObject MultiplyNode::staticMetaObject = { {
    QMetaObject::SuperData::link<NE_Node::staticMetaObject>(),
    qt_meta_stringdata_MultiplyNode.offsetsAndSizes,
    qt_meta_data_MultiplyNode,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_MultiplyNode_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MultiplyNode, std::true_type>
    >,
    nullptr
} };

void MultiplyNode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { MultiplyNode *_r = new MultiplyNode();
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        default: break;
        }
    }
    (void)_o;
}

const QMetaObject *MultiplyNode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MultiplyNode::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MultiplyNode.stringdata0))
        return static_cast<void*>(this);
    return NE_Node::qt_metacast(_clname);
}

int MultiplyNode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = NE_Node::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_stringdata_DivideNode_t {
    uint offsetsAndSizes[4];
    char stringdata0[11];
    char stringdata1[1];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_DivideNode_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_DivideNode_t qt_meta_stringdata_DivideNode = {
    {
        QT_MOC_LITERAL(0, 10),  // "DivideNode"
        QT_MOC_LITERAL(11, 0)   // ""
    },
    "DivideNode",
    ""
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_DivideNode[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   15, // constructors
       0,       // flags
       0,       // signalCount

 // constructors: parameters
    0x80000000 | 1,

 // constructors: name, argc, parameters, tag, flags, initial metatype offsets
       0,    0,   14,    1, 0x0e,    1 /* Public */,

       0        // eod
};

Q_CONSTINIT const QMetaObject DivideNode::staticMetaObject = { {
    QMetaObject::SuperData::link<NE_Node::staticMetaObject>(),
    qt_meta_stringdata_DivideNode.offsetsAndSizes,
    qt_meta_data_DivideNode,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_DivideNode_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<DivideNode, std::true_type>
    >,
    nullptr
} };

void DivideNode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { DivideNode *_r = new DivideNode();
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        default: break;
        }
    }
    (void)_o;
}

const QMetaObject *DivideNode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DivideNode::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DivideNode.stringdata0))
        return static_cast<void*>(this);
    return NE_Node::qt_metacast(_clname);
}

int DivideNode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = NE_Node::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
