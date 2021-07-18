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
        if(max<a[i])
            max=a[i];
    }
    int CSa[max+3]={0};
    for(int i=0;i<length;i++)
        CSa[a[i]]++;
    for(int i=0;i<max+2;i++)
        CSa[i+1]+=CSa[i];
    while(time--)
    {
        int r,l;
        scanf("%d",&l);
        scanf("%d",&r);
        if(r>max)
            r=max;
        if(l>max)
            l=max+1;
        printf("%d",CSa[r]-CSa[l-1]);
        printf("\n");
    }
    return 0;
}
