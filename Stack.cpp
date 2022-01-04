//
// Created by brucebek on 03.01.2022.
//

#include "Stack.h"
#include "exceptions.h"

int64_t Stack::pop()
{
    if(!stack.empty()){
        int64_t temp = stack.back();
        stack.pop_back();
        return temp;
    }
    throw EmptyStack();
};

int64_t Stack::top()
{
    if(!stack.empty()){
        return stack.back();
    }
    throw EmptyStack();
};

void Stack::push(int64_t x)
{
    stack.push_back(x);
};
