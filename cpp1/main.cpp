#include <iostream>

struct
{
    void operator()() {
        std::cout << "call";
    }
} functor;


int main()
{

    auto f = []() { functor(); };

    void(*ff)() = []() {};

    std::cout << "Hello World!\n";
}