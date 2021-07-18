#include <iostream>

using namespace std;
int isprime(int n);
int MinFact(int n);
int main()
{
    cout<<"Please input an integer:";
    int n;
    cin>>n;
    while(n<2||n>32767)
    {
        cout<<"Wrong input!\nPlease input another integer(2~32767):";
        cin>>n;
    }
    cout<<"The prime factorization of "<<n<<"."<<endl<<n<<"=";
    if(isprime(n))
        cout<<n;
    else
    {
        cout<<MinFact(n);
        n/=MinFact(n);
        for(int i=2;i<=n;i++)
        {
            while(n%i==0&&isprime(i))
            {
                cout<<"*"<<i;
                n/=i;
            }
        }
    }

    return 0;
}
int isprime(int n)
{
    for(int i=2;i*i<=n;i++)
    {
        if(n%i==0)
            return 0;
    }
    return 1;
}
int MinFact(int n)
{
    for(int i=2;i*i<=n;i++)
    {
        if(n%i==0&&isprime(i))
            return i;
    }
    return 1;
}
