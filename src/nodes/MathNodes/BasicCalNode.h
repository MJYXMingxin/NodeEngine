//
// Created by 12603 on 2023/7/18.
//

#ifndef NODEENGINE_BASICCALNODE_H
#define NODEENGINE_BASICCALNODE_H

#include "../../NE_Node_Basic.h"

class NE_Node;
class NE_NodeInput;
class NE_NodeOutput;

class AddNode : public NE_Node
{
public:
    explicit AddNode();
    int run_node() override;
protected:

};


#endif //NODEENGINE_BASICCALNODE_H
