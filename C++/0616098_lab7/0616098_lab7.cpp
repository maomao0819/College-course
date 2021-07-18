#include <iostream>

using namespace std;

int main()
{
    short int cn;
    cin>>cn;
    short int n;
    for(short int i=0;i<cn;i++)
    {
        cin>>n;
        short int a[n];
        for(short int j=0;j<n;j++)
        {
            cin>>a[j];
        }
        short int up=0,down=0;
        for(short int j=0;j<n-1;j++)
        {
            if(a[j]>a[j+1])
                down++;
            else if(a[j]<a[j+1])
                up++;
        }
        cout<<"Case "<<i+1<<": "<<up<<" "<<down<<endl;
    }
    return 0;
}
