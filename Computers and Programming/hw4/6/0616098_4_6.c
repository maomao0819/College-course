#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Input different integers (end with 0): ");
    int a,b,min,max;
    scanf("%d",&a);
        min=a;
        max=a;
    while(1)
    {
        scanf("%d",&b);
        if(b==0)
            break;
        if(b<min)
            min=b;
        else if(b>max)
            max=b;
    }
    printf("Smallest is %d\n",min);
    printf("Largest is %d",max);
    return 0;
}
