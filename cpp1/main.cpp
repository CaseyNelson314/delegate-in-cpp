#include <iostream>
#include "Delegate.hpp"

void Invoke(void(*f)())
{
	f();
}

struct Sample
{
	Delegator<Sample, void()> onReceive;

	Sample()
		: onReceive(this, &Sample::cb)
	{
		//Invoke();
	}

	void cb()
	{
		std::cout << "call";
	}

};

Sample samle;

int main()
{
	Delegator<Sample, void()>::Execute();
}