/*
���w���@�ӧ��p�e�A�ӧ��p�e�i�b�{�b��o9702�����q
�b�Ĥ@�������ɻݤ�I19700���A�ĤG���p�e�����ɡA�i�A��o10000��
���g�{���ϥΤG���k�PNewton method�D�������q�v
*/


#include <iostream>
using namespace std;

int main()
{
	//-----------bisection----------------
	float low = 0, high = 1, middle, PV, vertex;

	//�D�ߪ��u���I ,y = 9702x^2 -296x + 2 ; ���I�y�Ъ�x�b����: - b / 2a
	vertex = 296.0 / (9702 * 2); //Remember:at least one of the ints must be explicitly casted to a double

	//�k��ߪ��u�ײv����
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


	//����ߪ��u�ײv���t
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
	//�k��
	double x = 1, a, b;
	while (9702 + (-19700) / (1 + x) + (10000 / (1 + x) / (1 + x)) >= 0.0001)
	{
		a = 9702 + (-19700) / (1 + x) + (10000 / (1 + x) / (1 + x));
		b = (19700 / (1 + x) / (1 + x)) - 20000 / (1 + x) / (1 + x) / (1 + x);  // b = a ���L��
		x = x - (a / b);
	}
	cout << "By Newton:" << endl << x << endl;


	//����
	x = 0, a, b;
	while (9702 + (-19700) / (1 + x) + (10000 / (1 + x) / (1 + x)) >= 0.0001)
	{
		a = 9702 + (-19700) / (1 + x) + (10000 / (1 + x) / (1 + x));
		b = (19700 / (1 + x) / (1 + x)) - 20000 / (1 + x) / (1 + x) / (1 + x);  // b = a ���L��
		x = x - (a / b);
	}
	cout << x<<endl;

    return 0;
}
