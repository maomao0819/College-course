#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a;
    scanf("%d",&a);
    int b[a];
    int c=0;
    int i;
    for(i=0;i<a;i++)
    {
        b[i]=0;
    }
    for(i=0;i<a;i++)
    {
        scanf("%d",&b[i]);
        c=c+b[i];
    }
    printf("%d",c);
    return 0;
}
