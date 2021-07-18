#include <stdio.h>
#include <stdlib.h>
int gcd(x,y)
{
    if(y==0)
    {
        return x;
    }
    else
    {
        return gcd(y,x%y);
    }
}
int main()
{
    printf("Please enter 2 numbers: ");
    int a,b;
    scanf("%d %d",&a,&b);
    if(a>b)
    {
        printf("Their greatest common divisor is %d.",gcd(a,b));
    }
    else
    {
        printf("Their greatest common divisor is %d.",gcd(b,a));
    }

    return 0;
}
