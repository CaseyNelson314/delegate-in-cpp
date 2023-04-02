#include <iostream>

#include "Delegate.hpp"


void invoke(void(*f)())
{
	f();
}

class Sample
	: Delegator<void()>
{
	void callback() override
	{
		std::cout << "call";
	}
};

Sample sample;

int main()
{
	invoke(Delegator<void()>::Execute);
}
