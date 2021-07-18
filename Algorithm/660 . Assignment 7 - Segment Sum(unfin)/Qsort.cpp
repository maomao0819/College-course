#include <iostream>
#include <cstdlib>
#include <stdio.h>
using namespace std;
void quicksort(int a[], int le, int ri);
int partition(int a[], int le, int ri);
int main()
{

    int length,time;
    scanf("%d",&length);
    scanf("%d",&time);
    int a[length];
    for(int i=0;i<length;i++)
        scanf("%d",&a[i]);
    int len=0;
    quicksort(a, 0, length-1);
    /*for(int i=0;i<length;i++)
        cout<<a[i]<<endl;*/
    int arr[length+1][2]={0};
    for(int i=0;i<length+1;i++)
    {
        if(arr[len][0]!=a[i])
        {
            len++;
            arr[len][0]=a[i];
            arr[len][1]+=arr[len-1][1]+1;
        }
        else
            arr[len][1]++;
    }
    //for(int i=0;i<len;i++)
       // cout<<arr[i][0]<<" "<<arr[i][1]<<endl;
    while(time--)
    {
        int l,r;
        scanf("%d",&l);
        scanf("%d",&r);
        int temp=0;
        for(;l>arr[temp][0];temp++);
        l=temp;
        //cout<<"l="<<l<<endl;
        temp=len;
        for(;r<arr[temp][0];temp--);
        r=temp;
        //cout<<"r="<<r<<endl;
        printf("%d",arr[r][1]-arr[l-1][1]);
        printf("\n");
    }
    return 0;
}
void quicksort(int a[], int le, int ri)
{
    if(le<ri)
    {
        int p=partition(a, le, ri);
        quicksort(a, le, p-1);
        quicksort(a, p+1, ri);
    }
}
int partition(int a[], int le, int ri)
{
    int pivot=a[ri];
    int p=le-1;
    int temp;
    for(int i=le;i<ri;i++)
    {
        if(a[i]<=pivot)
        {
            p++;
            temp=a[i];
            a[i]=a[p];
            a[p]=temp;
        }
    }
    temp=a[p+1];
    a[p+1]=a[ri];
    a[ri]=temp;
    return p+1;
}
