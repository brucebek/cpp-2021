//
// Created by brucebek on 04.01.2022.
//

#ifndef CPP_2021_EXCEPTIONS_H
#define CPP_2021_EXCEPTIONS_H
#include <exception>


class CalculatorException : public std::exception {
public:
    int code = 1;
    const char * what() const noexcept override;
};


class UnexpectedArgumentsException : public CalculatorException {
public:
    int code = 2;
    const char * what() const noexcept override;

};

class UnexpectedCommand: public CalculatorException {
public:
    int code = 3;
    const char * what() const noexcept override;

};


class EmptyStack : public CalculatorException {
public:
    int code = 4;
    const char * what() const noexcept override;
};

#endif //CPP_2021_EXCEPTIONS_H
