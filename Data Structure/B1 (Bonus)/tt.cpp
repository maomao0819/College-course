#include <iostream>
#include <cmath>
using namespace std;
long long int pow_recurrsive(int base, int exponent);
long long int pow_for_loop(int base, int exponent);
long long int pow_square(int base, int exponent);
long long int pow_square_binary(int base, int exponent);
long long int po(int poly[], int n, int x);
long long int horner(int poly[], int n, int x);
int main()
{
	/*int base = 0;
	int exponent = 0;
	cin >> base >> exponent;
	cout << pow(base, exponent) << "\n";
	cout << pow_recurrsive(base, exponent) << "\n";
	cout << pow_for_loop(base, exponent) << "\n";
	cout << pow_square(base, exponent) << "\n";
	cout << pow_square_binary(base, exponent) << "\n";
	cout << "----------\n";*/
	int k = 0;
	int n = 0;
	cin >> k >> n;
	int * arg;
	arg = new int (k);
	for (int i = 0; i < k; i++)
        arg[i] = 0;
    for (int i = 0; i < k; i++)
        cin >> arg[i];
    for (int i = 1; i <= n; i++)
        cout << i << "  " << po(arg, k, i) << "\n";
    for (int i = 1; i <= n; i++)
        cout << i << "  " << horner(arg, k, i) << "\n";
	return 0;
}
long long int pow_recurrsive(int base, int exponent)
{
	if (exponent == 1)
		return base;
	else
		return base * pow_recurrsive(base, exponent - 1);
}

long long int pow_for_loop(int base, int exponent)
{
	long long int pow = 1;
	for (int i = 0; i < exponent; i++)
		pow *= base;
	return pow;
}
long long int pow_square(int base, int exponent)
{
	long long int pow = 1;
	long long int multi = base;
	while (exponent > 0)
	{
		if (exponent % 2 == 1)
		{
			pow *= multi;
			exponent--;
		}
		exponent /= 2;
		multi *= multi;
	}
	return pow;
}
long long int pow_square_binary(int base, int exponent)
{
	long long int pow = 1;
	long long int multi = base;
	while (exponent)
	{
		// 判斷是偶數還是奇數，和1進行與運算
		if(exponent & 1)
			// 如果此時的指數 為1則為奇數
			pow = pow * multi;
        //底數進行乘方
		multi *= multi;
		//指數減半
		exponent >>= 1;
	}
	return pow;
}

// returns value of poly[0]x(n-1) + poly[1]x(n-2) + .. + poly[n-1]
long long int po(int poly[], int n, int x)
{
    long long int result = poly[0];  // Initialize result

    // Evaluate value of polynomial using Horner's method
    for (int i = 1; i < n; i++)
    {
        // cout << i << " " << pow_square_binary(poly[i], i) << "\n";
        result += poly[i] * pow_square_binary(x, i);
    }
    return result;
}

// returns value of poly[0]x(n-1) + poly[1]x(n-2) + .. + poly[n-1]
long long int horner(int poly[], int n, int x)
{
    int a[n];
    for (int i = 0; i < n; i++)
        a[i] = poly[n - i - 1];
    long long int result = a[0];  // Initialize result

    // Evaluate value of polynomial using Horner's method
    for (int i = 1; i < n; i++)
        result = result * x + a[i];

    return result;
}





