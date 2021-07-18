#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Enter ten positive integers : ");
    int x[10];
    int a,b,c,d;
    for(a=0;a<10;a++)
    {
        scanf("%d",&x[a]);
    }
    for(b=0;b<10;b++)
    {
        for(c=0;c<10;c++)
        {
            if(x[b]<x[c])
            {
                d=x[b];
                x[b]=x[c];
                x[c]=d;
            }
        }
    }
    for(a=0;a<10;a++)
    {
        printf(" %d",x[a]);
    }
    return 0;
}
