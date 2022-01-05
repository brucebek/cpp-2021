#include "exceptions.h"
#include "commands.h"
#include <sstream>
#include <gtest/gtest.h>


TEST(Calculator, PUSHIntOverflow) {
    std::stringstream commands{"PUSH 9223372036854775808"};
    EXPECT_THROW(run_commands(commands), IntOverflow);
}

TEST(Calculator, PLUSIntOverflow) {
    std::stringstream commands{"PUSH 9223372036854775807\n"
                           "PUSH 1\n"
                           "PLUS"};
    EXPECT_THROW(run_commands(commands), IntOverflow);
}

TEST(Calculator, MINUSIntOverflow) {
    std::stringstream commands{"PUSH 9223372036854775800\n"
                           "PUSH 9223372036854775800\n"
                           "MINUS"};
    EXPECT_THROW(run_commands(commands), IntOverflow);
}

TEST(Calculator, MULIntOverflow) {
    std::stringstream commands{"PUSH 2\n"
                           "PUSH 9223372036854775806\n"
                           "MUL"};
    EXPECT_THROW(run_commands(commands), IntOverflow);
}

TEST(Calculator, DIVIntOverflow) {
    std::stringstream commands{"PUSH -9223372036854775808\n"
                           "PUSH -1\n"
                           "DIV"};
    EXPECT_THROW(run_commands(commands), IntOverflow);
}

TEST(Calculator, DIVDivZero) {
    std::stringstream commands{"PUSH -9223372036854775808\n"
                           "PUSH 0\n"
                           "DIV"};
    EXPECT_THROW(run_commands(commands), DivByZero);
}

TEST(Calculator, POPEmptyStack) {
    std::stringstream commands{"POP"};
    EXPECT_THROW(run_commands(commands), EmptyStack);
}

TEST(Calculator, PRINTEmptyStack) {
    std::stringstream commands{"PRINT"};
    EXPECT_THROW(run_commands(commands), EmptyStack);
}


TEST(Calculator, PUSHInvalidArgumentNotNum) {
    std::stringstream commands{"PUSH 123aasd"};
    EXPECT_THROW(run_commands(commands), InvalidArgument);
}


TEST(Calculator, PUSHInvalidArgumentNotVar) {
    std::stringstream commands{"PUSH aa_sd"};
    EXPECT_THROW(run_commands(commands), InvalidArgument);
}


TEST(Calculator, ChangeValueOfVar) {
    std::stringstream commands{"PUSH 10\n"
                               "PEEK x\n"
                               "PUSH 20\n"
                               "PEEK x\n"
                               "PUSH x\n"
                               "PRINT"};
    std::string res{"20\n"};
    testing::internal::CaptureStdout();
    run_commands(commands);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(res.c_str(), output.c_str());

}


TEST(Calculator, EmptyCommand) {
    std::stringstream commands{""};
    std::string res{""};
    testing::internal::CaptureStdout();
    run_commands(commands);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(res.c_str(), output.c_str());
}


TEST(Calculator, TestComplex3) {
    std::stringstream commands{"PUSH 4\n"
                               "PEEK a\n"
                               "POP\n"
                               "PUSH 6\n"
                               "PEEK c\n"
                               "POP\n"
                               "PUSH 2\n"
                               "PEEK d\n"
                               "POP\n"
                               "PUSH 36\n"
                               "PEEK e\n"
                               "POP\n"
                               "PUSH 11\n"
                               "PEEK f\n"
                               "POP\n"
                               "PUSH 2\n"
                               "PEEK g\n"
                               "POP\n"
                               "PUSH a\n"
                               "PUSH c\n"
                               "PLUS\n"
                               "PUSH d\n"
                               "MUL\n"
                               "PUSH e\n"
                               "PUSH f\n"
                               "PUSH g\n"
                               "MINUS\n"
                               "DIV\n"
                               "MINUS\n"
                               "PRINT"};
    std::string res{"16\n"};
    testing::internal::CaptureStdout();
    run_commands(commands);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(res.c_str(), output.c_str());
}
