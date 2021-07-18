#include <iostream>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m;
    cin>>n>>m;
    char maze[n][m];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin>>maze[i][j];
    int count[n][m];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            count[i][j]=0;
    for(int i=0;i<n;i++)
    {
        if(maze[i][0]=='x')
            break;
        count[i][0]=1;
    }
    for(int i=0;i<m;i++)
    {
        if(maze[0][i]=='x')
            break;
        count[0][i]=1;
    }
    for(int i=1;i<n;i++)
        for(int j=1;j<m;j++)
            if(maze[i][j]=='.')
                count[i][j]=count[i-1][j]||count[i][j-1];
    if(count[n-1][m-1])
        cout<<"Yes";
    else
        cout<<"No";
    return 0;
}
