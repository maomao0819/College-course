#include <iostream>
using namespace std;
void RadixSort(int arr[],int n);
void CountSort(int arr[],int n,int exp,int output[]);
int main()
{
    while(1)
    {
        int len;
        cout<<"input length:";
        cin>>len;
        int a[len];
        int ans[len]={0};
        for(int i=0;i<len;i++)
            cin>>a[i];
        RadixSort(a,len);
        for(int i=0;i<len;i++)
            cout<<a[i]<<" ";
        cout<<"\n";
    }
    return 0;
}
void CountSort(int arr[],int n,int exp,int output[])
{
    int i,count[10]={0};
    for(i=0;i<n;i++)
        count[(arr[i]/exp)%10]++;
    for(i=1;i<10;i++)
        count[i]+=count[i-1];
    for(i=n-1;i>=0;i--)
    {
        output[count[(arr[i]/exp)%10]-1]=arr[i];
        count[(arr[i]/exp)%10]--;
    }
    for(i=0;i<n;i++)
        arr[i]=output[i];
}
void RadixSort(int arr[],int n)
{
    int max=arr[0];
    for(int i=1;i<n;i++)
        if(max<arr[i])
            max=arr[i];
    int output[n];
    for (int exp=1;max/exp>0;exp*= 10)
        CountSort(arr,n,exp,output);
}


