#include<iostream>
using namespace std;

char s[1001];
int cnt[26];

int main()
{
	cin >> s;
	for (int i = 0; s[i] != '\0'; i++)
		cnt[s[i] - 'A']++;
	for (int i = 1000; i >= 1; i--)
		for (int j = 0; j < 26; j++)
			if (cnt[j] == i)
				cout << 'A' + j << ' ' << i << endl;
}