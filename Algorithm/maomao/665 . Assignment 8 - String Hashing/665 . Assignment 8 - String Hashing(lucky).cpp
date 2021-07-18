#include <iostream>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m;
    cin>>n>>m;
    char ch[n][m];
    int h[n]={0};
    int r=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin>>ch[i][j];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            h[i]+=ch[i][j]*(78313-j*217);

    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(h[i]==h[j])
            {
                for(int k=0;k<m;k++)
                    cout<<ch[i][k];
                break;
            }
        }
    }
    return 0;
}
