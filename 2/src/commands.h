#ifndef CPP_2021_COMMANDS_H
#define CPP_2021_COMMANDS_H

#include "Calculator.h"


class Command {
protected:
    Calculator &_ctx;
    explicit Command(Calculator &ctx);
public:
    virtual void run() = 0;
};


class Comment : public Command {
public:
    Comment(Calculator &ctx);
    void run() override;
};


class Pop : public Command {
public:
    explicit Pop(Calculator &ctx);
    void run() override;
};


class Push : public Command {
private:
    const std::string &_arg;
public:
    Push(Calculator &ctx, const std::string &arg);
    void run() override;
};


class Peek : public Command {
private:
    const std::string &_var;
public:
    Peek(Calculator &ctx, const std::string &var);
    void run() override;
};

class Abs : public Command {
public:
    explicit Abs(Calculator &ctx);
    void run() override;
};

class Plus : public Command {
public:
    explicit Plus(Calculator &ctx);
    void run() override;
};


class Minus : public Command {
public:
    explicit Minus(Calculator &ctx);
    void run() override;
};


class Mul : public Command {
public:
    explicit Mul(Calculator &ctx);
    void run();
};


class Div : public Command {
public:
    explicit Div(Calculator &ctx);
    void run() override;
};


class Print : public Command {
public:
    explicit Print(Calculator &ctx);
    void run() override;
};


class Read : public Command {
public:
    explicit Read(Calculator &ctx);
    void run() override;
};

Command* make_command(Calculator &calculator, const std::string &command, const std::string &arg);

void run_commands(std::istream &input);
#endif //CPP_2021_COMMANDS_H
