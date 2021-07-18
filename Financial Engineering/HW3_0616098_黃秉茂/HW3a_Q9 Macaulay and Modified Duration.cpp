// Calculate Macaulay Duration of Bond
// Calculate Modified duration of Bond
// Calculate price change when yield increase a basis point
// Modified duration = Macaulay Duration / (1 + r)
// A basis point=0.01%

#include<iostream>
using namespace std;
#define FACE_VALUE 100
#define BASIS_POINT 0.0001
int main()
{
	int n_term = 0;
	float coupon = 0, yield = 0, Value = 0;
	float Discount = 0, Macaulay_Duration = 0;
	cout << ("Enter the number of periods: ");
	cin >> n_term;
	cout << ("Enter the Coupon of each period: ");
	cin >> coupon;
	cout << ("Enter the Market Yield: ");
	cin >> yield;
	for (int i = 1; i <= n_term; i++)
	{
		Discount = 1;
		//calculate discount factor
		for (int j = 1; j <= i; j++)
			Discount /= (1 + yield);
		Macaulay_Duration += i * Discount * coupon;
		Value += Discount * coupon;
        //consider face value
		if (i == n_term)
		{
			Value += Discount * FACE_VALUE;
			Macaulay_Duration += n_term * Discount * FACE_VALUE;
		}
	}
	Macaulay_Duration = Macaulay_Duration / Value;
	cout << "Macaulay Duration:" << Macaulay_Duration << " years." << endl;
	float Modified_Duration = Macaulay_Duration / (1 + yield);
	cout << "Modified Duration:" << Modified_Duration << " years." << endl;
	cout << "Price change when yield increases a basis point: " << -1 * Modified_Duration * BASIS_POINT * 100 << "%" << endl;

	return 0;
}
