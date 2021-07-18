#include <iostream>
#include<stdio.h>
using namespace std;

int main()
{
    long long int dp[301][301];
    for(int i=0;i<301;i++)
    {
        dp[i][0]=0;
        dp[0][i]=1;
        dp[i][1]=1;
        dp[1][i]=1;
    }
    for(int i=2;i<301;i++)
    {
        for(int j=2;j<301;j++)
        {
            if(i>=j)
                dp[i][j]=dp[i-j][j]+dp[i][j-1];
            else
                dp[i][j]=dp[i][i];
        }
    }
    char str[15];
    int n,L1,L2;
    while(gets(str))
    {
        int defaut=-1;
        L1=defaut;
        L2=defaut;
        sscanf(str,"%d%d%d",&n,&L1,&L2);
        if(L1>300)
            L1=300;
        if(L2>300)
            L2=300;
        if(L1==defaut)
			cout<<dp[n][n]<<endl;
        else if(L2==defaut)
			cout<<dp[n][L1]<<endl;
        else
        {
            if(L1==1)
			 cout<<dp[n][L2]<<endl;
            else
			 cout<<dp[n][L2]-dp[n][L1-1]<<endl;
        }
    }
    return 0;
}
