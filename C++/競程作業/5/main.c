#include <stdio.h>
#include <stdlib.h>

int main()
{
    int len,tim;
    scanf("%d %d",&len,&tim);
    short num[len];
    short i;
    for(i=0;i<len;i++)
    {
        num[i]=0;
    }
    for(i=0;i<len;i++)
    {
        scanf("%d",&num[i]);
    }
    for(i=0;i<tim;i++)
    {
        int l,r,k;
        scanf("%d %d %d",&l,&r,&k);
        short copy[r-l+1];
        short i2,i3=0;
        for(i2=0;i2<r-l+1;i2++)
        {
            copy[i2++]=0;
        }
        for(i2=l;i2<=r;i2++)
        {
            copy[i3++]=num[i2];
        }
        for(i2=0;i2<r-l+1;i2++)
        {
            printf("%d ",copy[i2]);
        }
        short temp;
        for(i2=0;i2<r-l+1-1;i2++)
        {
            for(i3=0;i3<r-l+1-1;i3++)
            {
                if(copy[i3]>copy[i3+1])
                {
                    temp=copy[i3];
                    copy[i3]=copy[i3+1];
                    copy[i3+1]=temp;for(i2=0;i2<r-l+1;i2++)
        {
            copy[i2++]=0;
        }
                }
            }
        }
        printf("\n");

    }
    return 0;
}
