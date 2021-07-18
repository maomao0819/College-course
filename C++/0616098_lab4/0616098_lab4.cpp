#include <iostream>

using namespace std;

int main()
{
    int time;
    cin>>time;
    int i;
    for(i=1;i<=time;i++)
    {
        char str;
        int n;
        cin>>str>>str>>n;
        long long int a[n][n];
        int j;
        int k;
        for(j=0;j<n;j++)
        {
            for(k=0;k<n;k++)
            {
                cin>>a[j][k];
            }
        }
        int check=1;
        for(j=0;j<n;j++)
        {
            for(k=0;k<n;k++)
            {
                if(a[j][k]!=a[n-1-j][n-1-k]||a[j][k]<0)
                    check=0;
            }
        }
        cout<<"Test #"<<i<<": ";
        if(check==1)
            cout<<"Symmetric.";
        else if(check==0)
            cout<<"Non-symmetric.";
        cout<<endl;
    }
    return 0;
}
