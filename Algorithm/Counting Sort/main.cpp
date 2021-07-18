#include <iostream>
using namespace std;
void CountingSort(int a[], int length, int max, int ans[]);
int main()
{
    while(1)
    {
        int len;
        cout<<"input length:";
        cin>>len;
        int max;
        cout<<"input max:";
        cin>>max;
        int a[len];
        int ans[len]={0};
        for(int i=0;i<len;i++)
            cin>>a[i];
        CountingSort(a, len, max, ans);
        for(int i=0;i<len;i++)
            cout<<ans[i];
        cout<<"\n";
    }
    return 0;
}
void CountingSort(int a[], int length, int max, int ans[])
{
    int CSa[max+1]={0};
    for(int i=0;i<length;i++)
        CSa[a[i]]++;
    for(int i=0;i<=max;i++)
        CSa[i+1]+=CSa[i];
    for(int i=length-1;i>=0;i--)
    {
        ans[CSa[a[i]]-1]=a[i];
        CSa[a[i]]--;
    }
}


