#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isprime(unsigned int i)
{
    int divisor;
    if(i<=1)
        return false;
    for(divisor=2;divisor*divisor<=i;divisor++)
        if(i%divisor==0)
        return false;
    return true;
}
int main(void)
{
    printf("Enter a positive integer: ");
    int a;
    scanf("%d",&a);
    int b;
    int num=0;
    for(b=1;b*b<=a;b++)
    {
        if(isprime(b))
        {
            if(a%b==0)
            {
                num++;
            }
        }
    }
    printf("%d has %d prime factors:",a,num);
    int c;
    int n=0;
    for(c=1;c*c<=a;c++)
    {
        if(isprime(c))
        {
            if(a%c==0)
            {
                if(n>0)
                    printf(",");
                printf(" %d",c);
                n++;
            }
        }
    }
    return 0;
}
