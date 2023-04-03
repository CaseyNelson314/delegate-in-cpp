#include <iostream>
#include "Delegate.hpp"

void Invoke(void(*f)())
{
	f();
}

class TwoWire
{
	void(*f)(int);
public:
	void update()
	{
		f(100);
	}
	void onReceive(void(*cb)(int))
	{
		f = cb;
	}
};

#include <functional>

struct Sample
{
	Delegator<Sample, void()> onReceive;
	int value;

	Sample(TwoWire& wire, int value)
		: onReceive(this, &Sample::cb)
		, value(value)
	{
		wire.onReceive([](int) {
			});
	}

	void cb()
	{
		std::cout << "call" << value;
	}

};




class S
{

};

TwoWire Wire;
TwoWire Wire1;


Sample samle(Wire, 1);
Sample samle1(Wire1, 2);



int main()
{

	Wire.onReceive([](int) {
		std::cout << "hogehoge";
		});

	Wire.update();
	Wire1.update();

}