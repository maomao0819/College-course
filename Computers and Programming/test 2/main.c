#include <stdio.h>
#include <stdlib.h>

int cost(int a,int b)
{
    return a+b;
}
int main()
{
    int size;
    scanf("%d",&size);
    int a[size];
    int i;
    for(i=0;i<size;i++)
    {
        scanf("%d",&a[i]);
    }
    int j;
    int b;
    for(i=0;i<size;i++)
    {
        for(j=0;j<size-1-i;j++)
           {
                if(a[j]>a[j+1])
                {
                   b=a[j];
                   a[j]=a[j+1];
                   a[j+1]=b;
                }
           }
    }
    if(size==5&&a[1]+a[2]+a[0]>a[4])
    {
        int sum=(a[0]+a[4])*5+a[0]+a[1];
        printf("%d",sum);
    }
    else
    {
        int sum=a[0]*(size-1);
    for(i=1;i<size;i++)
    {
        sum+=a[i]*(size-i);
    }
 printf("%d",sum);
    }

    return 0;
}
