#include <iostream>
#include <cstdlib>
using namespace std;
void quicksort(int a[], int le, int ri);
int partition(int a[], int le, int ri);
int main()
{

    int length,time;
    cin>>length>>time;
    int a[length];
    for(int i=0;i<length;i++)
        cin>>a[i];
    quicksort(a, 0, length-1);
    for(int i=0;i<length;i++)
        cout<<a[i]<<endl;
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
