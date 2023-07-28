//
// Created by 12603 on 2023/7/25.
//

#ifndef NODEENGINE_NODELIBRARYPLUGIN_H
#define NODEENGINE_NODELIBRARYPLUGIN_H

#include "NodeLibraryPluginInterface.h"
#include "../BasicMathLibrary.h"
#include "../LogicLibrary.h"

class Q_DECL_EXPORT NodeLibraryPlugin : public QObject, public NodeLibraryPluginInterface{
    Q_OBJECT
    Q_INTERFACES(NodeLibraryPluginInterface)
    Q_PLUGIN_METADATA(IID NodeLibraryPluginInterfaceIID)
public:
    NodeLibraryPlugin();
    ~NodeLibraryPlugin() override;
    QStringList GetLibraryNameList() override;
    NE_Node* CreateNodeByName(const QString& name) override;
    NE_Node* CreateNodeByName(const QString& lib, const QString& node) override;
    QMap<QString, QMap<QString, const QMetaObject*>> GetLibraryMap() override;
    QMap<QString, const QMetaObject*> GetLiraryByName(const QString& name) override;
private:
    QStringList _library_name_list;
    QMap<QString, QMap<QString, const QMetaObject*>> _library_map;
};


#endif //NODEENGINE_NODELIBRARYPLUGIN_H
