#include <iostream>
#include <cstdlib>
using namespace std;
void quicksort(int a[][2], int le, int ri);
int partition(int a[][2], int le, int ri);
int main()
{

    int length,time;
    cin>>length>>time;
    //a[i][0]:value a[i][1]:index
    int a[length][2]={0};
    for(int i=0;i<length;i++)
    {
        cin>>a[i][0];
        a[i][1]=i;
    }
    quicksort(a, a[0]a[0], length-1);
    for(int i=0;i<length;i++)
    {
        cout<<a[i][0]<<endl;
    }
    while(time--)
    {
        int r,l;
        cin>>r>>l;
        r--;
        l--;
        for(int i=0;i<length;i++)
            if(a[i][1]>=r&&a[i][1]<=l)
            {
                cout<<a[i][1]+1;
                break;
            }

    }
    return 0;
}
void quicksort(int a[][2], int le, int ri)
{
    if(le>ri)
    {
        int p=partition(a, le, ri);
        quicksort(a, le, p-1);
        quicksort(a, p+1, ri);
    }
}
int partition(int a[][2], int le, int ri)
{
    int pivot=a[ri][0];
    int big=le-1;
    int temp;
    for(int i=le;i<ri;i++)
    {
        if(a[i][0]>=pivot)
        {
            big++;
            temp=a[i][0];
            a[i][0]=a[big][0];
            a[big][0]=temp;
            temp=a[i][1];
            a[i][1]=a[big][1];
            a[big][1]=temp;
        }
    }
    temp=a[big+1][0];
    a[le][0]=a[big+1][0];
    a[big+1][0]=temp;
    temp=a[big+1][1];
    a[le][1]=a[big+1][1];
    a[big+1][1]=temp;
    return big+1;
}
