//
// Created by 12603 on 2023/7/23.
//

#ifndef NODEENGINE_NODELIBRARYPLUGININTERFACE_H
#define NODEENGINE_NODELIBRARYPLUGININTERFACE_H

#include "../../pch.h"
#include "../../NE_Node_Basic.h"

#define NodeLibraryPluginInterfaceIID "com.nodeengine.PluginInterface/1.0.0"

class NodeLibraryPluginInterface{
public:
    virtual ~NodeLibraryPluginInterface() = default;
    virtual QStringList GetLibraryNameList() = 0;
    virtual NE_Node* CreateNodeByName(const QString& name) = 0;
    virtual NE_Node* CreateNodeByName(const QString& lib, const QString& node) = 0;
    virtual QMap<QString, QMap<QString, const QMetaObject*>> GetLibraryMap() = 0;
    virtual QMap<QString, const QMetaObject*> GetLiraryByName(const QString& name) = 0;
};

Q_DECLARE_INTERFACE(NodeLibraryPluginInterface, NodeLibraryPluginInterfaceIID)

#endif //NODEENGINE_NODELIBRARYPLUGININTERFACE_H
