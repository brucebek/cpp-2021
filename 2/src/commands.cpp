#include <iostream>
#include "commands.h"
#include "exceptions.h"
#include "SafeInt.hpp"

Command::Command(Calculator &ctx) : _ctx{ctx}
{
}

Comment::Comment(Calculator &ctx) : Command{ctx}
{
}
void Comment::run()
{
}


Pop::Pop(Calculator &ctx) : Command{ctx}
{
}
void Pop::run()
{
    _ctx.stack.pop();
}


bool is_number(const std::string &s)
{
    for(uint32_t i = 0; i < s.size(); i++)
    {
        if(i == 0 && (s[i] == '-' || s[i] == '+') && s.size() != 1) continue;
        if(s[i] < 48 || s[i] > 57) return false;
    }
    return true;
}

bool is_varname(const std::string &s)
{
    for(const char &c: s)
    {
        if(c < 65 || (c > 90  && c < 97) || c > 122) return false;
    }
    return true;
}


Push::Push(Calculator &ctx, const std::string &arg) : Command{ctx}, _arg{arg}
{
}
void Push::run()
{
    if(is_number(_arg))
    {
        try
        {
            _ctx.stack.push(std::stoll(_arg));
        }
        catch (std::out_of_range)
        {
            throw IntOverflow();
        }

    }
    else if (is_varname(_arg))
    {
        _ctx.stack.push(_ctx.vars.at(_arg));
    }
    else
    {
        throw InvalidArgument();
    }
}


Peek::Peek(Calculator &ctx, const std::string &var) : Command{ctx}, _var{var}
{
}
void Peek::run()
{
    if(is_varname(_var)){
        _ctx.vars[_var] = _ctx.stack.top();
    }
    else
    {
        throw InvalidArgument();
    }

}


Abs::Abs(Calculator &ctx) : Command{ctx}
{
}
void Abs::run()
{
    _ctx.stack.push(std::abs(_ctx.stack.pop()));
}


Plus::Plus(Calculator &ctx) : Command{ctx}
{
}
void Plus::run()
{
    _ctx.stack.push(SafeInt<int64_t, CalculatorSafeIntExceptionHandler>(_ctx.stack.pop()) + _ctx.stack.pop());
}


Minus::Minus(Calculator &ctx) : Command{ctx}
{
}
void Minus::run()
{
    int64_t a = _ctx.stack.pop();
    int64_t b = _ctx.stack.pop();
    _ctx.stack.push(SafeInt<int64_t, CalculatorSafeIntExceptionHandler>(b) - a);
}


Mul::Mul(Calculator &ctx) : Command{ctx}
{
}
void Mul::run()
{
    _ctx.stack.push(SafeInt<int64_t, CalculatorSafeIntExceptionHandler>(_ctx.stack.pop()) * _ctx.stack.pop());
}


Div::Div(Calculator &ctx) : Command{ctx}
{
}
void Div::run()
{
    a = _ctx.stack.pop();
    int64_t b = _ctx.stack.pop();
    _ctx.stack.push(SafeInt<int64_t, CalculatorSafeIntExceptionHandler>(b) / a);
}


Print::Print(Calculator &ctx) : Command{ctx}
{
}
void Print::run()
{
    std::cout << _ctx.stack.top() << std::endl;
}


Read::Read(Calculator &ctx) : Command{ctx}
{
}
void Read::run()
{
    std::string temp;
    std::cin >> temp;
    if(is_number(temp))
    {
        try
        {
            _ctx.stack.push(std::stoll(temp));
        }
        catch (std::out_of_range)
        {
            throw IntOverflow();
        }
    }
    else
    {
        throw InvalidArgument();
    }
}


Command* make_command(Calculator &calculator, const std::string &command, const std::string &arg)
{
    if (command == "POP")
    {
        return new Pop(calculator);
    }
    else if (command == "PUSH")
    {
        return new Push(calculator, arg);
    }
    else if (command == "PEEK")
    {
        return new Peek(calculator, arg);
    }
    else if (command == "ABS")
    {
        return new Abs(calculator);
    }
    else if (command == "PLUS")
    {
        return new Plus(calculator);
    }
    else if (command == "MINUS")
    {
        return new Minus(calculator);
    }
    else if (command == "MUL")
    {
        return new Mul(calculator);
    }
    else if (command == "DIV")
    {
        return new Div(calculator);
    }
    else if (command == "PRINT")
    {
        return new Print(calculator);
    }
    else if (command == "READ")
    {
        return new Read(calculator);
    }
    else if(command.find('#') != std::string::npos)
    {
        return new Comment(calculator);
    }
    throw UnexpectedCommand();
}


void run_commands(std::istream &input)
{
    Calculator calculator;
    std::string raw_command;
    while(std::getline(input, raw_command))
    {
        calculator.perform(raw_command);
    }

}