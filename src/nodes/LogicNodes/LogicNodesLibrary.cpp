//
// Created by 12603 on 2023/7/23.
//

#include "LogicNodesLibrary.h"

LogicNodesLibrary::LogicNodesLibrary(){
    _library_name = "Logic";
    _library_map.insert("Branch", &BranchNode::staticMetaObject);
}

LogicNodesLibrary::~LogicNodesLibrary() {
    if(!_library_map.empty())
        this->deleteLater();
}

QString LogicNodesLibrary::GetLibraryName() {return _library_name; }

QMap<QString, const QMetaObject*> LogicNodesLibrary::GetLibraryMap() { return _library_map; }

NE_Node *LogicNodesLibrary::CreateNodeByName(const QString& name){
    const QMetaObject* metaObject = _library_map.value(name);
    if (metaObject)
    {
        QObject* object = metaObject->newInstance();
        return qobject_cast<NE_Node*>(object);
    }
    return nullptr;
}