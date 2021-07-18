#include <iostream>

using namespace std;

int max(int a, int b);
long long int knapSack(int W, int wt[], int val[], int n);
int main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int n,T;
	cin>>n>>T;
	int time[n],val[n];
	for(int i=0;i<n;i++)
        cin>>time[i]>>val[i];
	cout<<knapSack(T, time, val, n);
	return 0;
}
int max(int a, int b)
{
    return (a > b) ? a : b;
}
long long int knapSack(int W, int wt[], int val[], int n)
{
    long long int K[n+1][W+1];
    for(int i=0;i<=n;i++)
        for(int j=0;j<=W;j++)
            K[i][j]=0;
    for(int i=0;i<=n;i++)
    {
        for(int w=0;w<=W;w++)
        {
            if(i==0||w==0)
                K[i][w]=0;
            else if(wt[i-1]<=w)
                K[i][w]=max(val[i-1]+K[i-1][w-wt[i-1]],K[i-1][w]);
            else
                K[i][w]=K[i-1][w];
        }
    }
    return K[n][W];
}

