#include "exceptions.h"

const char * CalculatorException::what() const noexcept
{
    return "Oops error of the calculator.";
}

const char * UnexpectedArgumentsException::what() const noexcept
{
    return "Unexpected number of arguments.";
}

const char * UnexpectedCommand::what() const noexcept
{
    return "Unexpected command of the calculator.";
}

const char * InvalidArgument::what() const noexcept
{
    return "The calculator cannot recognize this argument.";
}

const char * EmptyStack::what() const noexcept
{
    return "The stack of the calculator is empty.";
}

const char * IntOverflow::what() const noexcept
{
    return "Calculator cannot contain a big number.";
}

const char * DivByZero::what() const noexcept
{
    return "Calculator got zero as denominator.";
}

void CalculatorSafeIntExceptionHandler::SafeIntOnOverflow()
{
    throw IntOverflow();
}


void CalculatorSafeIntExceptionHandler::SafeIntOnDivZero()
{
    throw DivByZero();
}