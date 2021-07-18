#include "pch.h"
#include "CPhoneNumber.h"
#include <iostream>
ostream& operator<< (ostream &output, const CPhoneNumber &x)
{
	output << "(+" << x.CountryCode << ")-" << x.RegionCode;
	output << "-" << x.number << endl;
	return output;
}
istream& operator >> (istream&input, CPhoneNumber &x)
{
	cout << "Input CountryCode : ";
	input >> x.CountryCode;
	cout << "Input RegionCode : ";
	input >> x.RegionCode;
	cout << "Input PhoneNumber : ";
	input >> x.number;
	return input;
}
CPhoneNumber::CPhoneNumber(int c, int r, int n)
{
	CountryCode = c;
	RegionCode = r;
	number = n;
}


CPhoneNumber::~CPhoneNumber()
{
}
