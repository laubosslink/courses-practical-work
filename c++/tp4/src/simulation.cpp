#include <cstdlib>
#include <ctime>
#include <iostream>

#include <Planche.h>

int main()
{
	std::srand(std::time(0));

	Planche p(5);
	p.simulation(1000);

//	p.~Planche();

	return 0;
}
