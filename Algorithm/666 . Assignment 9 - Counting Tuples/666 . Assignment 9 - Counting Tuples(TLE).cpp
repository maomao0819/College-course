#include <iostream>

using namespace std;
void quicksort(long long int a[], int le, int ri);
int partition(long long int a[], int le, int ri);
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin>>n;
    long long int x,sum[2][n*n];
    int a[4][n];
    cin>>x;
    for(int i=0;i<4;i++)
        for(int j=0;j<n;j++)
            cin>>a[i][j];
    int k=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            sum[0][k]=a[0][i]+a[1][j];
            sum[1][k++]=a[2][i]+a[3][j];
        }
    }
    quicksort(sum[0],0,n*n-1);
    int len=0;
    long long int sortsum[n*n][2]={0};
    sortsum[len][0]=sum[0][0];
    sortsum[len][1]=1;
    for(int i=1;i<n*n;i++)
    {
        if(sum[0][i]!=sum[0][i-1])
            sortsum[++len][0]=sum[0][i];
        sortsum[len][1]++;
    }
    long long int time=0;
    for(int i=0;i<=len;i++)
        for(int j=0;j<k;j++)
            if(sortsum[i][0]+sum[1][j]==x)
                time+=sortsum[i][1];
    cout<<time;
    return 0;
}
void quicksort(long long int a[], int le, int ri)
{
    if(le<ri)
    {
        int p=partition(a, le, ri);
        quicksort(a, le, p-1);
        quicksort(a, p+1, ri);
    }
}
int partition(long long int a[], int le, int ri)
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
