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
                    false,
                    Inline)
{
}

int BranchNode::run_node()
{
    if(input_pins[1]->getVal<bool>())
        get_output_pin(0);
    else
        get_output_pin(1);
    return 1;
}
