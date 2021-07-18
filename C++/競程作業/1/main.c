#include <stdio.h>
#include <stdlib.h>
int gcd(int a,int b);
int main()
{
    int n1,n2;
    scanf("%d%d",&n1,&n2);
    if(n1<0)
        n1=-n1;
    if(n2<0)
        n2=-n2;
    if(n1>n2)
        printf("%d",gcd(n1,n2));
    else
        printf("%d",gcd(n2,n1));
    return 0;
}
int gcd(int a,int b)
{
    if(a%b==0)
        return b;
    return gcd(b,a%b);
}
