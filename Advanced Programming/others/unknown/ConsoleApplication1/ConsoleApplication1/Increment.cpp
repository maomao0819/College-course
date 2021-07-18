#include "pch.h"
#include "Increment.h"
#include <iostream>
using namespace std;


Increment::Increment(int c = 0, int i = 1)
	:increment(i)
{
	count = c;
}


Increment::~Increment()
{
}

void Increment::print() const
{
	cout << count << endl << increment << endl;
}