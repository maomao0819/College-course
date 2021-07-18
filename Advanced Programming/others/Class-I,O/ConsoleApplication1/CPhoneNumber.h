#pragma once
#include <iostream>
using namespace std;
class CPhoneNumber
{
	friend ostream& operator << (ostream&, const CPhoneNumber&);
	friend istream& operator >> (istream&, CPhoneNumber&);
public:
	CPhoneNumber(int, int, int);
	~CPhoneNumber();
private:
	int CountryCode;
	int RegionCode;
	int number;
};

