#include <stdio.h>
int main()
{
    int n;
    float c, r, Value = 0, Discount, Duration = 0;
    printf("請輸入期數：");
    scanf("%d", &n);
	printf("請輸入債息：");
    scanf("%d", &c);
    printf("請輸入利率：");
    scanf("%d", &r);
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
			Value = Value + Discount * 100;
			Duration = Duration + n * Discount * 100;
		}
	}
	Duration = Duration / Value;
	printf("Duration=%f", Duration);

	return 0;
}
