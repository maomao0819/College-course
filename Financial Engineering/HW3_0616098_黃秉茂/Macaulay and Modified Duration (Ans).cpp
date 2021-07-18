//Calculate Macaulay Duration(MD) of Bond
//Calculate Modified duration
//Modified duration = MD/(1+r)
//A basis point=0.01%

#include<iostream>
using namespace std;


int main()
{
	int n;
	float c, r, Value = 0, Discount, Duration = 0;
	cout << ("Enter number of periods:");
	cin >> n;
	cout << ("Enter Coupon of each period:");
	cin >> c;
	cout << ("Enter Market yield:");
	cin >> r;
	for (int i = 1; i <= n; i++)
	{
		Discount = 1;
		for (int j = 1; j <= i; j++)  //calculate discount factor
		{
			Discount = Discount / (1 + r);
		}
		Duration = Duration + i * Discount * c;
		Value = Value + Discount * c;

		if (i == n)  //consider face value
		{
			Value = Value + Discount * 1000;
			Duration = Duration + n * Discount * 1000;
			cout <<"CxDF="<< Value << endl;
			cout <<"CxDFxt="<< Duration << endl;
		}
	}
	Duration = Duration / Value;
	cout << "Macaulay Duration:" << Duration << endl;
	cout << "Modified Duration:" << Duration / (1 + r) << endl;
	cout << "Price change when yield increase a basis point:" << (Duration / (1 + r)) * 0.01 * (-1) << "%" << endl;

	return 0;
}
