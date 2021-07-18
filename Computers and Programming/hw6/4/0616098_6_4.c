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
        printf("Their lowest common multiple is %d.",a*b/gcd(a,b));
    }
    else
    {
        printf("Their lowest common multiple is %d.",a*b/gcd(b,a));
    }
    return 0;
}
