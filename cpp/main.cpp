#include <iostream>

#include "Delegate.hpp"


void invoke(void(*f)())
{
	f();
}

class Sample
	: MultipleDelegator<void()>
{
	void callback() override
	{
		std::cout << "call";
	}
};

Sample sample;

int main()
{
	invoke(MultipleDelegator<void()>::Execute);
}
