//
// Created by 12603 on 2023/7/16.
//

#ifndef NODEENGINE_BRANCHNODE_H
#define NODEENGINE_BRANCHNODE_H

#include "../../NE_Node_Basic.h"

class NE_Node;
class NE_NodeInput;
class NE_NodeOutput;

class BranchNode : public NE_Node
{
    Q_OBJECT
public:
    explicit BranchNode();
    int run_node() override;
protected:

};
#endif //NODEENGINE_BRANCHNODE_H
