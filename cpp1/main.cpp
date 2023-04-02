#include <iostream>


template<class, class> class Delegator;  // 前方宣言

/// @brief 単一のメンバ関数を管理するデリゲータ
template<class T, class R, class... Args>
class Delegator<T, R(Args...)>
{

    using Functor = R(T::*)(Args...);

    static T* p;
    static Functor f;

public:

    void add(T* object, Functor function)
    {
        p = object;
        f = function;
    }

    static R Execute(Args... args)
    {
        (p->*f)(args...);
    }
};

template<class T, class R, class... Args>
T* Delegator<T, R(Args...)>::p = nullptr;

template<class T, class R, class... Args>
typename Delegator<T, R(Args...)>::Functor Delegator<T, R(Args...)>::f;




void Invoke(void(*f)())
{
    f();
}

struct Sample
{
    Delegator<Sample, void()> delegate;

    Sample()
    {
        delegate.add(this, &Sample::cb);
        Invoke(Delegator<Sample, void()>::Execute);
    }

    void cb()
    {
        std::cout << "call";
    }

};

Sample samle;

int main()
{
}