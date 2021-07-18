#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b;
    for(a=1;a<4;a++)
    {
        for(b=0;b<a*2-1;b++)
        printf("*");
        printf("\n");
    }
    for(a=3;a>1;a--)
    {
        for(b=a*2-3;b>0;b--)
        printf("*");
        printf("\n");
    }
    return 0;
    system("pause");
}
