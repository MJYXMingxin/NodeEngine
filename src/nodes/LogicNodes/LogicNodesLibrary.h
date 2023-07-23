//
// Created by 12603 on 2023/7/23.
//

#ifndef NODEENGINE_LOGICNODESLIBRARY_H
#define NODEENGINE_LOGICNODESLIBRARY_H

#include "../NodeLibraryPluginInterface.h"
#include "BranchNode.h"

//#if defined(NODEENGINE_LOGICNODESLIBRARY_H)
//#  define ABSTRACTPROCESSSHARED_EXPORT Q_DECL_EXPORT
//#else
//#  define ABSTRACTPROCESSSHARED_EXPORT Q_DECL_IMPORT
//#endif

class Q_DECL_EXPORT LogicNodesLibrary : public QObject, public NodeLibraryPluginInterface{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID NodeLibraryPluginInterfaceIID)
    Q_INTERFACES(NodeLibraryPluginInterface)
public:
    LogicNodesLibrary();
    ~LogicNodesLibrary() override;
    QString GetLibraryName() override;
    NE_Node* CreateNodeByName(const QString& name) override;
    QMap<QString, const QMetaObject*> GetLibraryMap() override;
private:
    QString _library_name;
    QMap<QString, const QMetaObject*> _library_map;
};

#endif //NODEENGINE_LOGICNODESLIBRARY_H
