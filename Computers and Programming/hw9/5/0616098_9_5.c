#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Sequence size :");
    int size;
    scanf("%d",&size);
    int a[size];
    printf("Input Sequence :");
    int i;
    for(i=0;i<size;i++)
    {
        scanf("%d",&a[i]);
    }
    int check=1;
    for(i=0;i<size-1;i++)
    {
        if(a[i]>a[i+1])
            check=0;
    }
    int add_size=size*(size-1)/2;
    int b[add_size];
    int j;
    int k=0;
    for(i=0;i<size;i++)
    {
        for(j=i+1;j<size;j++)
        {
            b[k++]=a[i]+a[j];
        }
    }
    int c;
    for(i=0;i<add_size;i++)
    {
        for(j=0;j<add_size-i;j++)
        {
            if(b[j]>b[j+1])
            {
                c=b[j];
                b[j]=b[j+1];
                b[j+1]=c;
            }
        }
    }
    for(i=0;i<add_size-1;i++)
    {
        if(b[i]==b[i+1])
            check=0;
    }
    if(check==0)
        printf("It is not a B2-Sequence.");
    else if(check==1)
        printf("It is a B2-Sequence.");
    return 0;
}
