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
    int step[n][2];
    for(int i=0;i<n;i++)
        for(int j=0;j<2;j++)
            step[i][j]=0;
    int l[n],r[n];
    for(int i=0;i<n;i++)
        l[i]=-1;
    for(int i=0;i<n;i++)
        r[i]=-1;
    l[0]=0;
    r[0]=0;
    int now_l=0;
    int now_r=0;
    for(int j=1;j<m-1;j++)
    {
        if(maze[0][m-1-j]=='x')
        {
            r[0]=m-1-j;
            now_r=r[0];
            now_l=r[0];
            l[0]=r[0];
            step[0][0]+=now_r;
            step[0][1]+=now_r;
            break;
        }
    }
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(maze[i][j]=='x'&&l[i]<0)
                l[i]=j;
            if(maze[i][m-1-j]=='x'&&r[i]<0)
                r[i]=m-1-j;
            if(l[i]>0&&r[i]>0)
                break;
        }
    }
    int mark=0;
    int index=0;
    //cout<<"now_l="<<now_l<<"  "<<"now_r="<<now_r<<"step[0][0]="<<step[0][0]<<"  "<<"step[0][1]="<<step[0][1]<<endl;
    for(int i=1;i<n;i++)
    {
        if(l[i]==-1)
        {
            mark++;
            step[i][0]+=step[index][0];
            step[i][1]+=step[index][1];
        }
        else
        {
            step[i][0]=(step[index][0]+(m-1-now_l)+1+(m-1-l[i])+mark)<(step[index][1]+(m-1-now_r)+1+(m-1-l[i])+mark)?(step[index][0]+(m-1-now_l)+1+(m-1-l[i])+mark):(step[index][1]+(m-1-now_r)+1+(m-1-l[i])+mark);
            step[i][1]=(step[index][0]+now_l+r[i]+1+mark)<(step[index][1]+now_r+r[i]+1+mark)?(step[index][0]+now_l+r[i]+1+mark):(step[index][1]+now_r+r[i]+1+mark);
            now_l=l[i];
            now_r=r[i];
            mark=0;
        }
        if(mark==0)
            index=i;
        //cout<<"mark="<<mark<<"  index="<<index<<"  now_l="<<now_l<<"  "<<"now_r="<<now_r<<"  step[i][0]="<<step[i][0]<<"  "<<"step[i][1]="<<step[i][1]<<endl;
    }
    int ans=(step[n-1][0]<step[n-1][1])?step[n-1][0]:step[n-1][1];
    cout<<ans;
    return 0;
}
