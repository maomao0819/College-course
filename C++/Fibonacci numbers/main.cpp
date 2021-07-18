#include <iostream>

using namespace std;

int main()
{
    int n;
    cin>>n;
    long long int a=1,b=1;
    long long int temp;
    for(int i=0;i<n-2;i++)
    {
        temp=a+b;
        a=b;
        b=temp;
    }
    cout<<"The Fibonacci number for "<<n<<" is "<<temp;
    return 0;
}
