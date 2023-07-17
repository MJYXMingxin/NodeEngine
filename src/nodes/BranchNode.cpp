//
// Created by 12603 on 2023/7/16.
//

#include "BranchNode.h"

BranchNode::BranchNode()
                       : NE_Node("Branch",
                       "Execute based on input condition",
                       {new NE_NodeInput("Exec",Exec,"exec"),
                                new NE_NodeInput("condition",Bool,"data")},
                       {new NE_NodeOutput("True",Exec,"exec"),
                                 new NE_NodeOutput("False",Exec,"exec")},
                       false)
{
}

int BranchNode::run_node()
{
    return 1;
}