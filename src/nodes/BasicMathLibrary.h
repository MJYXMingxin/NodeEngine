//
// Created by 12603 on 2023/7/18.
//

#ifndef NODEENGINE_BASICMATHLIBRARY_H
#define NODEENGINE_BASICMATHLIBRARY_H

#include "../NE_Node_Basic.h"

class NE_Node;
class NE_NodeInput;
class NE_NodeOutput;

class AddNode : public NE_Node
{
    Q_OBJECT
public:
    explicit Q_INVOKABLE AddNode();
    int run_node() override;
protected:
};

class SubtractNode : public NE_Node
{
Q_OBJECT
public:
    explicit Q_INVOKABLE SubtractNode();
    int run_node() override;
protected:
};

class MultiplyNode : public NE_Node
{
Q_OBJECT
public:
    explicit Q_INVOKABLE MultiplyNode();
    int run_node() override;
protected:
};

class DivideNode : public NE_Node
{
Q_OBJECT
public:
    explicit Q_INVOKABLE DivideNode();
    int run_node() override;
protected:

};

#endif //NODEENGINE_BASICMATHLIBRARY_H
