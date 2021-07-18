#include <iostream>
#include <stdio.h>
using namespace std;
int main()
{
    int length,time;
    scanf("%d",&length);
    scanf("%d",&time);
    int a[length];
    for(int i=0;i<length;i++)
        scanf("%d",&a[i]);
    int CSa[1000001]={0};
    for(int i=0;i<length;i++)
        CSa[a[i]]++;
    for(int i=0;i<1000001;i++)
        CSa[i+1]+=CSa[i];
    while(time--)
    {
        int r,l;
        scanf("%d",&r);
        scanf("%d",&l);
        printf("%d",CSa[l]-CSa[r-1]);
        printf("\n");
    }
    return 0;
}
