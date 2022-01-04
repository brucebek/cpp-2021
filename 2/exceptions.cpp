//
// Created by brucebek on 04.01.2022.
//
#include "exceptions.h"

const char * CalculatorException::what() const noexcept {
    return "Oops error of the calculator.";
}

const char * UnexpectedArgumentsException::what() const noexcept {
    return "Unexpected number of arguments.";
}

const char * UnexpectedCommand::what() const noexcept {
    return "Unexpected command of the calculator.";
}

const char * EmptyStack::what() const noexcept {
    return "The stack of the calculator is empty.";
}