#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

char s[1001];
int cnt[26];

int main()
{
	scanf("%s", s);
	for (int i = 0; s[i] != '\0'; i++)
		cnt[s[i] - 'A']++;
	vector<pair<int, int>> v;
	for (int i = 0; i < 26; i++)
		if (cnt[i] > 0)
			v.push_back(pair<int, int>(-cnt[i], i + 'A'));
	sort(v.begin(), v.end());
	for (pair<int, int> pa : v)
		printf("%d %d\n", pa.second, -pa.first);
}