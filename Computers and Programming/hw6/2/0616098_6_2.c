#include <stdio.h>
#include <stdlib.h>
int power(int x,int n)
{
    if(n==0)
        return 1;
    else
        return x*power(x,n-1);
}
int main()
{
    printf("Enter base and exponent: ");
    int a,b;
    scanf("%d %d",&a,&b);
    int p=power(a,b);
    printf("The power(%d, %d) is: %d",a,b,p);
    return 0;
}
