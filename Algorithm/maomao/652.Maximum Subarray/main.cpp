#include <iostream>

using namespace std;

int main()
{
    int num;
    cin>>num;
    long long int arr[num];
    for(int i=0;i<num;i++)
        cin>>arr[i];
    long long int arr2[num];
    arr2[0]=arr[0];
    if(arr2[0]<0)
        arr2[0]=0;
    long long int max=arr[0];
    for(int i=1;i<num;i++)
    {
        arr2[i]=arr2[i-1]+arr[i];
        if(arr2[i]<0)
            arr2[i]=0;
        if(max<arr2[i])
            max=arr2[i];
    }
    cout<<max;
    return 0;
}
