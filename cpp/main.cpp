#include <iostream>

#include "Delegate.hpp"


void invoke(void(*f)())
{
	f();
}

class Sample
	: MultipleCastDelegator<void()>
{
	void callback() override
	{
		std::cout << "call";
	}
};

Sample sample;

int main()
{
	invoke(MultipleCastDelegator<void()>::Execute);
}
