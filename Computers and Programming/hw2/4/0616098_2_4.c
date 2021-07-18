#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b;
    scanf("%d %d",&a,&b);
    printf("The sum of the given numbers : %d\n",a+b);
    printf("The difference of the given numbers : %d\n",a-b);
    printf("The product of the given numbers : %d\n",a*b);
    printf("The quotient of the given numbers : %f\n",(float)a/b);
    return 0;
}
