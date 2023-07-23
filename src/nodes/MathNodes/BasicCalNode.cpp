//
// Created by 12603 on 2023/7/18.
//

#include "BasicCalNode.h"

AddNode::AddNode()
: NE_Node("Add",
          "Basic calculate : add",
          {new NE_NodeInput("num1",Float,"data",true,{Float,Int}),
           new NE_NodeInput("num2",Float,"data",true,{Float,Int})},
          {new NE_NodeOutput("sum",Float,"data",true)},
          true,
          Pure)
{
}

int AddNode::run_node()
{
    float sum = 0.0f;
    foreach(NE_Pin* pin, input_pins){
        pin->RenewClass();
        switch(pin->PinClass()){
            case Float: sum += *pin->getVal<float>();break;
            case Int: sum += static_cast<float>(*pin->getVal<int>());break;
            default:break;
        }
    }
    output_pins[0]->setVal(&sum);
    return 1;
}