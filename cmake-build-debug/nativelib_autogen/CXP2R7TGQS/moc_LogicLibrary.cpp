/****************************************************************************
** Meta object code from reading C++ file 'LogicLibrary.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/nodes/LogicLibrary.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LogicLibrary.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_BranchNode_t {
    uint offsetsAndSizes[4];
    char stringdata0[11];
    char stringdata1[1];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_BranchNode_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_BranchNode_t qt_meta_stringdata_BranchNode = {
    {
        QT_MOC_LITERAL(0, 10),  // "BranchNode"
        QT_MOC_LITERAL(11, 0)   // ""
    },
    "BranchNode",
    ""
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_BranchNode[] = {

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

Q_CONSTINIT const QMetaObject BranchNode::staticMetaObject = { {
    QMetaObject::SuperData::link<NE_Node::staticMetaObject>(),
    qt_meta_stringdata_BranchNode.offsetsAndSizes,
    qt_meta_data_BranchNode,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_BranchNode_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<BranchNode, std::true_type>
    >,
    nullptr
} };

void BranchNode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { BranchNode *_r = new BranchNode();
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        default: break;
        }
    }
    (void)_o;
}

const QMetaObject *BranchNode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BranchNode::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BranchNode.stringdata0))
        return static_cast<void*>(this);
    return NE_Node::qt_metacast(_clname);
}

int BranchNode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = NE_Node::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_stringdata_GreaterNode_t {
    uint offsetsAndSizes[4];
    char stringdata0[12];
    char stringdata1[1];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_GreaterNode_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_GreaterNode_t qt_meta_stringdata_GreaterNode = {
    {
        QT_MOC_LITERAL(0, 11),  // "GreaterNode"
        QT_MOC_LITERAL(12, 0)   // ""
    },
    "GreaterNode",
    ""
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_GreaterNode[] = {

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

Q_CONSTINIT const QMetaObject GreaterNode::staticMetaObject = { {
    QMetaObject::SuperData::link<NE_Node::staticMetaObject>(),
    qt_meta_stringdata_GreaterNode.offsetsAndSizes,
    qt_meta_data_GreaterNode,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_GreaterNode_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<GreaterNode, std::true_type>
    >,
    nullptr
} };

void GreaterNode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { GreaterNode *_r = new GreaterNode();
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        default: break;
        }
    }
    (void)_o;
}

const QMetaObject *GreaterNode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GreaterNode::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GreaterNode.stringdata0))
        return static_cast<void*>(this);
    return NE_Node::qt_metacast(_clname);
}

int GreaterNode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = NE_Node::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
