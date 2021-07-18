#include <iostream>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int n, m;
	cin>>n>>m;
	int a[m];
	int i;
	for(i = 0; i < m; i++)
		cin>>a[i];
	long long int ans[n + 1];
	for(i = 0; i <= n; i++)
		ans[i] = 0;
	for(i = 1; i <= n; i++)
	{
	    int j;
		for(j = 0; j < m; j++)
		{
			if(i > a[j])
				ans[i] += ans[i - a[j]];
			else if(i == a[j])
                ans[i] += 1;
            if(ans[i] >= 1000000007)
                ans[i] %= 1000000007;
		}
	}
    cout<<ans[n];
	return 0;
}
