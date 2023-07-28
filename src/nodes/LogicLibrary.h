//
// Created by 12603 on 2023/7/16.
//

#ifndef NODEENGINE_LOGICLIBRARY_H
#define NODEENGINE_LOGICLIBRARY_H

#include "../NE_Node_Basic.h"

class NE_Node;
class NE_NodeInput;
class NE_NodeOutput;

class BranchNode : public NE_Node
{
    Q_OBJECT
public:
    explicit Q_INVOKABLE BranchNode();
    int run_node() override;
protected:
};

class GreaterNode : public NE_Node
{
Q_OBJECT
public:
    explicit Q_INVOKABLE GreaterNode();
    int run_node() override;
protected:
};

#endif //NODEENGINE_LOGICLIBRARY_H
