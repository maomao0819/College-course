#include <stdio.h>
#include <stdlib.h>

int main()
{
    char str[100];
    scanf("%s",&str);
    short i;
    short n0=0,n1=0;
    for(i=0;i<100;i++)
    {
        if(str[i]==48)
            n0++;
        else if(str[i]==49)
            n1++;
    }
    printf("%d %d",n0,n1);
    return 0;
}
