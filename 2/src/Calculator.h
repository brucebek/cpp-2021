#ifndef CPP_2021_CALCULATOR_H
#define CPP_2021_CALCULATOR_H
#include <cstdint>
#include <unordered_map>
#include <string>
#include <iostream>

#include "Stack.h"


class Calculator{
public:
    Stack stack;
    std::unordered_map<std::string, std::int64_t> vars;
    void perform(const std::string &raw_command);
};


#endif //CPP_2021_CALCULATOR_H
