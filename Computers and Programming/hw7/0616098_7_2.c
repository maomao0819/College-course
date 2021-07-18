#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Enter the value of N");
    int a;
    scanf("%d",&a);
    printf("Enter the numbers");
    int b[a];
    int i;
    for(i=0;i<a;i++)
    {
        scanf("%d",&b[i]);
    }
    int j,c;
    for(j=0;j<a-1;j++)
    {
        for(i=0;i<a-1;i++)
    {
        if(b[i]<b[i+1])
        {
            c=b[i];
            b[i]=b[i+1];
            b[i+1]=c;
        }
    }
    }
    printf("The 2nd largest number is = %d\n",b[1]);
    printf("The 2nd smallest number is = %d",b[a-2]);
    return 0;
}
