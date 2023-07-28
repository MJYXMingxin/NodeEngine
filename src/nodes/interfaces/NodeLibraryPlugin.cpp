//
// Created by 12603 on 2023/7/25.
//

#include "NodeLibraryPlugin.h"

NodeLibraryPlugin::NodeLibraryPlugin()
    :_library_map(QMap<QString, QMap<QString, const QMetaObject *>>()),
    _library_name_list()
{
    QString logic("Logic");
    QMap<QString, const QMetaObject*> logicMap{
        {"Branch", &BranchNode::staticMetaObject},
        {"Greater", &GreaterNode::staticMetaObject}
    };
    _library_name_list.push_back(logic);
    _library_map.insert(logic, logicMap);

    QString math("Math");
    QMap<QString, const QMetaObject*> mathMap{
        {"Add", &AddNode::staticMetaObject},
        {"Subtract", &SubtractNode::staticMetaObject},
        {"Multiply", &MultiplyNode::staticMetaObject},
        {"Divide", &DivideNode::staticMetaObject}
    };
    _library_name_list.push_back(math);
    _library_map.insert(math, mathMap);
}

NodeLibraryPlugin::~NodeLibraryPlugin() = default;

QStringList NodeLibraryPlugin::GetLibraryNameList() {
    return _library_name_list;
}

NE_Node *NodeLibraryPlugin::CreateNodeByName(const QString &name) {
    foreach(auto map, _library_map.values()){
        if(map.value(name)){
            QObject* object = map.value(name)->newInstance();
            return qobject_cast<NE_Node*>(object);
        }
    }
    return nullptr;
}

QMap<QString, QMap<QString, const QMetaObject *>> NodeLibraryPlugin::GetLibraryMap() {
    return _library_map;
}

QMap<QString, const QMetaObject *> NodeLibraryPlugin::GetLiraryByName(const QString &name) {
    return _library_map.value(name);
}

NE_Node *NodeLibraryPlugin::CreateNodeByName(const QString &lib, const QString &node) {
    QObject* object = _library_map.value(lib).value(node)->newInstance();
    return qobject_cast<NE_Node*>(object);
}
