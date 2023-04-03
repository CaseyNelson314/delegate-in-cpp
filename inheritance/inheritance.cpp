
#include <iostream>

struct Base
{
    virtual void operator()() = 0;
};

template<class T>
struct Derived : Base
{

    void operator()() override
    {
        std::cout << "hogehoge";
    }
};

std::unique_ptr<Base> Register()
{
    return std::make_unique<Base>( new Derived<int>{} );
}

#include <memory>

std::unique_ptr<Base> a[] =
{
    std::make_unique<Base>(new Derived<int >{}),
    std::make_unique<Base>(new Derived<void>{}),
    std::make_unique<Base>(new Derived<char>{}),
    std::make_unique<Base>(new Derived<int >{}),
};


int main()
{
    for (auto&& it : a)
    {
        (*it)();
    }
}