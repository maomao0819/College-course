#include <stdio.h>
void main()
{
    int n;
    float c, r, Value=0,Discount;
    scanf("%d", &n);
    scanf("%f", &c);
    scanf("%f", &r);
    for(int i = 1; i <= n; i++)
    {
        Discount = 1;
        for(int j = 1; j <= i; j++)
            Discount = Discount / (1 + r);
        Value = Value + Discount * c;
        if(i==n)
            Value=Value+Discount*100;
    }
    printf("BondValue = %f", Value);
}
