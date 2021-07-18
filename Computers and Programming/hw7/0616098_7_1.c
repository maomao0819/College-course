#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Enter a, b respectively: ");
    int a,b,*p,*q;
    p=&a;
    q=&b;
    scanf("%d %d",&a,&b);
    printf("Value before swapping:\na = %d\nb = %d\n",*p,*q);
    int *r;
    r=p;
    p=q;
    q=r;
    printf("Value after swapping:\na = %d\nb = %d",*p,*q);
    return 0;
}
