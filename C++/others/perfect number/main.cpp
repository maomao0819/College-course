#include <iostream>

using namespace std;
int IsPerfect(int x);
int main()
{
    cout << "Please input an integer n:";
    int n;
    cin>>n;
    while(n>10000)
    {
        cout<<"Please input 2~10000 for n:";
        cin>>n;
    }
    if(IsPerfect(n))
        cout<<n<<" is a perfect number"<<endl;
    else
        cout<<n<<" isn't a perfect number"<<endl;
    cout<<"Perfect number(s) between 2 and "<<n<<":\n";
    int i,j,sum;
    for(i=2;i<=n;i++)
    {
        if(IsPerfect(i))
        {
            cout<<i<<"=1";
            for(j=2;j<i;j++)
            {
                if(i%j==0)
                    cout<<"+"<<j;
            }
            cout<<endl;
        }
    }
    return 0;
}
int IsPerfect(int x)
{
    int i,sum=0;
    for(i=1;i<x;i++)
    {
        if(x%i==0)
            sum+=i;
    }
    if(sum==x)
        return 1;
    return 0;
}
