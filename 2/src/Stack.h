#ifndef CPP_2021_STACK_H
#define CPP_2021_STACK_H
#include <vector>
#include <cstdint>

class Stack {
private:
    std::vector<int64_t> stack;
public:
    int64_t pop();
    int64_t top();
    void push(int64_t);
};


#endif //CPP_2021_STACK_H
