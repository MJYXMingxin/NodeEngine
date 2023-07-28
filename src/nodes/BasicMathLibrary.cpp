//
// Created by 12603 on 2023/7/18.
//

#include "BasicMathLibrary.h"

AddNode::AddNode()
: NE_Node("Add",
          "Basic calculate : add",
          {new NE_NodeInput("num1",Float,"data",true,{Float,Int}),
           new NE_NodeInput("num2",Float,"data",true,{Float,Int})},
          {new NE_NodeOutput("sum",Float,"data",true)},
          true,
          Pure){}

int AddNode::run_node()
{
    float sum = 0.0f;
    foreach(NE_Pin* pin, input_pins){
        pin->RenewClass();
        switch(pin->PinClass()){
            case Float: sum += *pin->getVal<float>();break;
            case Int: sum += static_cast<float>(*pin->getVal<int>());break;
            default:return 0;
        }
    }
    output_pins[0]->setVal(&sum);
    return 1;
}

SubtractNode::SubtractNode()
: NE_Node("Subtract",
          "Basic calculate : subtract",
          {new NE_NodeInput("num1",Float,"data",true,{Float,Int}),
           new NE_NodeInput("num2",Float,"data",true,{Float,Int})},
           {new NE_NodeOutput("res",Float,"data",true)},
           true,
           Pure){}

int SubtractNode::run_node()
{
    float subtrahend = 0.0f;
    float minuend = 0.0f;
    for (int i = 0; i < input_pins.size(); ++i) {
        input_pins[i]->RenewClass();
        if(!i) {
            switch (input_pins[i]->PinClass()) {
                case Float: subtrahend = *input_pins[i]->getVal<float>(); break;
                case Int: subtrahend = static_cast<float>(*input_pins[i]->getVal<int>()); break;
                default: return 0;
            }
        } else {
            switch (input_pins[i]->PinClass()) {
                case Float: minuend = *input_pins[i]->getVal<float>(); break;
                case Int: minuend = static_cast<float>(*input_pins[i]->getVal<int>()); break;
                default: return 0;
            }
        }
    }
    float res = subtrahend - minuend;
    output_pins[0]->setVal(&res);
    return 1;
}

MultiplyNode::MultiplyNode()
: NE_Node("Multiply",
          "Basic calculate : multiply",
          {new NE_NodeInput("num1",Float,"data",true,{Float,Int}),
           new NE_NodeInput("num2",Float,"data",true,{Float,Int})},
           {new NE_NodeOutput("res",Float,"data",true)},
           true,
           Pure){}

int MultiplyNode::run_node() {
    float res = 1.0f;
    foreach(NE_Pin* pin, input_pins){
        pin->RenewClass();
        switch (pin->PinClass()) {
            case Float:res *= *pin->getVal<float>(); break;
            case Int: res *= static_cast<float>(*pin->getVal<int>()); break;
            default:return 0;
        }
    }
    output_pins[0]->setVal(&res);
    return 1;
}

DivideNode::DivideNode()
: NE_Node("Divide",
          "Basic calculate : divide",
          {new NE_NodeInput("num1",Float,"data",true,{Float,Int}),
           new NE_NodeInput("num2",Float,"data",true,{Float,Int})},
           {new NE_NodeOutput("res",Float,"data",true)},
           true,
           Pure){}

int DivideNode::run_node() {
    float dividend = 0.0f;
    float divisor = 0.0f;
    for (int i = 0; i < input_pins.size(); ++i) {
        input_pins[i]->RenewClass();
        if(!i) {
            switch (input_pins[i]->PinClass()) {
                case Float: dividend = *input_pins[i]->getVal<float>(); break;
                case Int: dividend = static_cast<float>(*input_pins[i]->getVal<int>()); break;
                default: return 0;
            }
        } else {
            switch (input_pins[i]->PinClass()) {
                case Float:divisor = *input_pins[i]->getVal<float>(); break;
                case Int: divisor = static_cast<float>(*input_pins[i]->getVal<int>()); break;
                default: return 0;
            }
        }
    }
    float res = dividend / divisor;
    output_pins[0]->setVal(&res);
    return 1;
}
