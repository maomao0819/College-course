#include <stdio.h>

int main()
{
    float c, x, Discount;
    float Low = 0, High = 1;
    int n;
    scanf("%f", &c);
    scanf("%f", &x);
    scanf("%d", &n);
    while(High - Low >= 0.0001)
    {
        float Middle = (Low + High) / 2;
        float Value = 0;
        for (int i = 1; i <= n; i = i + 1)
        {
            Discount = 1;
            for(int j = 1; j <= i; j++)
            {
                Discount = Discount / (1 + Middle);
            }
            Value = Value + Discount * c;
        }
        Value = Value - x;
    if(Value > 0)
        { Low = Middle;}
    else
        {High = Middle;}
    }
    printf("Yield rate=%f",High);
    return 0;
}
