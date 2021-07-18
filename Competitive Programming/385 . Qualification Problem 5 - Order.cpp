#include <iostream>
using namespace std;
void quicksort(int a[], int le, int ri);
int partition(int a[], int le, int ri);
int main()
{

    int len = 0;
    cin >> len;
    int query = 0;
    cin >> query;
    int arr[len];
    for(int i = 0; i < len; i++)
        cin >> arr[i];
    while(query--)
    {
        int l = 0;
        int r = 0;
        int k = 0;
        cin >> l >> r >> k;
        l--;
        r--;
        int arr2[r - l + 1];
        for(int i = 0; i < r - l + 1; i++)
            arr2[i] = arr[l + i];
        quicksort(arr2, 0, r - l);
        cout << arr2[k - 1] << endl;
    }
    return 0;
}
void quicksort(int a[], int le, int ri)
{
    if(le < ri)
    {
        int p = partition(a, le, ri);
        quicksort(a, le, p-1);
        quicksort(a, p+1, ri);
    }
}
int partition(int a[], int le, int ri)
{
    int pivot = a[ri];
    int p = le - 1;
    int temp;
    for(int i = le; i < ri; i++)
    {
        if(a[i] <= pivot)
        {
            p++;
            temp = a[i];
            a[i] = a[p];
            a[p] = temp;
        }
    }
    temp = a[p+1];
    a[p+1] = a[ri];
    a[ri] = temp;
    return p+1;
}

