#include <iostream>

using namespace std;
int gcd(int a,int b);
int IsPrimeToEach(int m,int n);
int main()
{
    cout<<"Please input an integer n:";
    int n;
    cin>>n;
    int sum=0;
    int i;
    for(i=1;i<n;i++)
    {
        sum+=IsPrimeToEach(n,i);
    }
    cout<<"Euler¡¦s phi function of 6 is "<<sum<<","<<endl;
    cout<<"where gcd("<<n<<",1)=1 ";
    for(i=2;i<n;i++)
    {
        if(gcd(i,n)==1)
            cout<<"and gcd("<<n<<","<<i<<")=1 ";
    }
    cout<<".";
    return 0;
}
int gcd(int a,int b)
{
    if(a%b==0)
        return b;
    return gcd(b,a%b);
}
int IsPrimeToEach(int m,int n)
{
    if(gcd(m,n)==1)
        return 1;
    return 0;
}
