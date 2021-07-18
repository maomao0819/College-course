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
    int step=0;
    int l[n],r[n];
    for(int i=0;i<n;i++)
        l[i]=-1;
    for(int i=0;i<n;i++)
        r[i]=-1;
    int now=0;
    for(int j=1;j<m-1;j++)
    {
        if(maze[0][m-1-j]=='x')
        {
            r[0]=m-1-j;
            now=r[0];
            step+=now;
            break;
        }
    }
    int mark=0;
    for(int i=1;i<n;i++)
    {
        for(int j=1;j<m-1;j++)
        {
            if(maze[i][j]=='x'&&l[i]<0)
                l[i]=j;
            if(maze[i][m-1-j]=='x'&&r[i]<0)
                r[i]=m-1-j;
            if(l[i]>0&&r[i]>0)
                break;
        }
    }
    for(int i=1;i<n;i++)
    {
        if(l[i]==-1)
            mark++;
        else if(now+r[i]+1<m-1-now+1+m-1-l[i])
        {
            step+=((now+r[i]+1)+mark);
            now=r[i];
            mark=0;
        }
        else if(now+r[i]+1>m-1-now+1+m-1-l[i])
        {
            step+=((m-1-now+1+m-1-l[i])+mark);
            now=l[i];
            mark=0;
        }
        else
        {
            step+=((now+r[i]+1)+mark);
            mark=0;
            int temp_i=i;
            int j=temp_i+1;
            while(r[j]==-1)
                j++;
            int time=0;
            while(l[temp_i]+r[j]+1==m-1-r[i]+1+m-1-l[temp_i]&&j<n)
            {
                temp_i=j;
                int j=temp_i+1;
                while(r[j]==-1)
                    j++;
                time++;
            }
            if(l[temp_i]+r[j]+1<m-1-r[temp_i]+1+m-1-l[j])
            {
                if(time%2)
                    now=r[i];
                else
                    now=l[i];
            }
            else if(l[temp_i]+r[j]+1>m-1-r[temp_i]+1+m-1-l[j])
            {
                if(time%2)
                    now=l[i];
                else
                    now=r[i];
            }
        }
    }
    cout<<step;
    return 0;
}
