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


class InvalidArgument: public CalculatorException {
public:
    int code = 4;
    const char * what() const noexcept override;
};


class EmptyStack : public CalculatorException {
public:
    int code = 5;
    const char * what() const noexcept override;
};


class IntOverflow : public CalculatorException {
public:
    int code = 6;
    const char * what() const noexcept override;
};


class DivByZero : public CalculatorException {
public:
    int code = 7;
    const char * what() const noexcept override;
};


class CalculatorSafeIntExceptionHandler
{
public:

    static void SafeIntOnOverflow();

    static void SafeIntOnDivZero();
};
#endif //CPP_2021_EXCEPTIONS_H
