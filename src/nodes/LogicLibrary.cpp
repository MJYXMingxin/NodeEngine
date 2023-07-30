//
// Created by 12603 on 2023/7/16.
//

#include "LogicLibrary.h"

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

GreaterNode::GreaterNode()
: NE_Node("Greater",
          "Logical judgment : greater",
          {new NE_NodeInput("",Float,"data",true,{Float,Int}),
           new NE_NodeInput("",Float,"data",true,{Float,Int})},
           {new NE_NodeOutput("",Bool,"data",true)},
           true,
           Math){}

int GreaterNode::run_node() {
    float param1 = 0.0f;
    float param2 = 0.0f;
    for (int i = 0; i < input_pins.size(); ++i) {
        input_pins[i]->RenewClass();
        if(!i) {
            switch (input_pins[i]->PinClass()) {
                case Float: param1 = *input_pins[i]->getVal<float>(); break;
                case Int: param1 = static_cast<float>(*input_pins[i]->getVal<int>()); break;
                default: return 0;
            }
        } else {
            switch (input_pins[i]->PinClass()) {
                case Float: param2 = *input_pins[i]->getVal<float>(); break;
                case Int: param2 = static_cast<float>(*input_pins[i]->getVal<int>());break;
                default: return 0;
            }
        }
    }
    bool res;
    static_cast<bool>(param1-param2) ? res = true : res = false;
    output_pins[0]->setVal(&res);
    return 1;
}
