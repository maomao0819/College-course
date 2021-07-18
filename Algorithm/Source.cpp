#include<bits/stdc++.h>
using namespace std;
bool com(pair<int,int> a,pair< int,int> b)
{
	return a > b;
}
int main()
{
	ios_base::sync_with_stdio(false);

	cin.tie(NULL);

	int n, m;
	cin >> n >> m;
	vector<pair<int, int>>vec;
	int a;
	for (int i = 0; i < n; i++)
	{
		cin >> a;
		vec.push_back(pair<int, int>(a, i + 1));
	}
	sort(vec.begin(), vec.end(),com);
	int intervalL, intervalR;
	for (int i = 0; i < m; i++)
	{
		cin >> intervalL>>intervalR;
		int temp = -1e9;
		for (int j= 0; j < n; j++)
		{
			if (vec[j].second >=intervalL&&vec[j].second<=intervalR)
			{
				temp = vec[j].second;
				while (++j)
				{
					if (vec[j].first != vec[j - 1].first) {
						cout << temp << '\n';
						break;
					}
					else if (vec[j].second >= intervalL && vec[j].second <= intervalR)
					{
						temp = vec[j].second;
					}
				}
				break;
			}
		}
	}
	return 0;
}
