#include "pch.h"
#include "Date.h"
#include <iostream>
using namespace std;
Date::Date( int mn, int dy, int yr)
{
	if (mn && mn <= 12)
		month = mn;
	else
		month = 1;
	year = yr;
	if(dy && dy <= 31)
		day = dy;
	else 
		day = 1;
}


Date::~Date()
{
}

void Date::print() const
{
	cout << month << '/' << day << '/' << year << endl;
}