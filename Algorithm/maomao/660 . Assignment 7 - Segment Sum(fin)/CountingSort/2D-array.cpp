#include <iostream>
#include <stdio.h>
using namespace std;
int main()
{
    int length,time;
    scanf("%d",&length);
    scanf("%d",&time);
    int a[length];
    int max=1;
    for(int i=0;i<length;i++)
    {
        scanf("%d",&a[i]);
        if(a[i]>max)
            max=a[i];
    }
    int CSa[max+3]={0};
    for(int i=0;i<length;i++)
        CSa[a[i]]++;
    int b[length+1][2]={0};
    int index=0;
    if(max-length<100)
        for(int i=0;i<max+2;i++)
            CSa[i+1]+=CSa[i];
    else
    {
        for(int i=1;i<max+2;i++)
        {
            if(CSa[i]>0)
            {
                index++;
                b[index][0]=i;
                b[index][1]=CSa[i]+b[index-1][1];
            }
        }
    }
    while(time--)
    {
        int l,r;
        scanf("%d",&l);
        scanf("%d",&r);
        if(r>max)
            r=max;
        if(l>max)
            l=max+1;
        if(max-length<100)
        {
            printf("%d",CSa[r]-CSa[l-1]);
            printf("\n");
        }
        else
        {
            int temp=0;
            for(;l>b[temp][0];temp++);
            l=temp;
            temp=index;
            for(;r<b[temp][0];temp--);
            r=temp;
            printf("%d",b[r][1]-b[l-1][1]);
            printf("\n");
        }
    }
    return 0;
}

