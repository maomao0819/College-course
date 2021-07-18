#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

char s[1002];
int cnt[300];

int main()
{
	scanf("%s", s);
	for (int i = 0; s[i]; i++)
		cnt[s[i]]++;
	vector<pair<int, int>> v;
	for (int i = 0; i < 300; i++)
		if (cnt[i])
			v.push_back(pair<int, int>(cnt[i], -i));
	sort(v.rbegin(), v.rend());
	for (auto pa : v)
		printf("%d %d\n", -pa.second, pa.first);
}