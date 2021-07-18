/*
假定有一個投資計畫，該投資計畫可在現在獲得9702元收益
在第一期結束時需支付19700元，第二期計畫結束時，可再獲得10000元
撰寫程式使用二分法與Newton method求內部收益率
*/


#include <iostream>
using namespace std;

int main()
{
	//-----------bisection----------------
	float low = 0, high = 1, middle, PV, vertex;

	//求拋物線頂點 ,y = 9702x^2 -296x + 2 ; 頂點座標的x軸公式: - b / 2a
	vertex = 296.0 / (9702 * 2); //Remember:at least one of the ints must be explicitly casted to a double

	//右方拋物線斜率為正
	while (high - vertex >= 0.0001)
	{
		middle = (vertex + high) / 2;
		PV = 9702 + (-19700) / (1 + middle) + 10000 / (1 + middle) / (1 + middle);
		if (PV > 0)
			high = middle;
		else
			vertex = middle;
	}
	cout << "By bisection:"<<endl<< high << endl;


	//左方拋物線斜率為負
	while (vertex - low >= 0.0001)
	{
		middle = (low + vertex) / 2;
		PV = 9702 + (-19700) / (1 + middle) + 10000 / (1 + middle) / (1 + middle);
		if (PV > 0)
			low = middle;
		else
			vertex = middle;
	}
	cout << vertex << endl<<endl;


	//---------newton method-------------
	//右根
	double x = 1, a, b;
	while (9702 + (-19700) / (1 + x) + (10000 / (1 + x) / (1 + x)) >= 0.0001)
	{
		a = 9702 + (-19700) / (1 + x) + (10000 / (1 + x) / (1 + x));
		b = (19700 / (1 + x) / (1 + x)) - 20000 / (1 + x) / (1 + x) / (1 + x);  // b = a 的微分
		x = x - (a / b);
	}
	cout << "By Newton:" << endl << x << endl;


	//左根
	x = 0, a, b;
	while (9702 + (-19700) / (1 + x) + (10000 / (1 + x) / (1 + x)) >= 0.0001)
	{
		a = 9702 + (-19700) / (1 + x) + (10000 / (1 + x) / (1 + x));
		b = (19700 / (1 + x) / (1 + x)) - 20000 / (1 + x) / (1 + x) / (1 + x);  // b = a 的微分
		x = x - (a / b);
	}
	cout << x<<endl;

    return 0;
}
