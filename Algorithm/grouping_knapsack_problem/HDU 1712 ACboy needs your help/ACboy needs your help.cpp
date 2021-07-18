#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>
#include<queue>
#include<stack>
#include<set>
#include<map>
#define ll long long
using namespace std;
const int INF = ( 2e9 ) + 2;
const ll maxn = 110;
int val[maxn][maxn];
int dp[maxn];
int solve(int n,int m)
{
    for(int k=1;k<=n;k++)// n Ве
    {
        for(int v=m;v>=0;v--)
        for(int i=1;i<=m;i++)
        if(v-i>=0)
        dp[v]=max(dp[v],dp[v-i]+val[k][i]);
    }
    return dp[m];
}
int main()
{
    int n,m;
    while(~scanf("%d%d",&n,&m)&&(n+m))
    {
        for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        scanf("%d",&val[i][j]);
        memset(dp,0,sizeof(dp));
        printf("%d\n",solve(n,m));
    }
}
