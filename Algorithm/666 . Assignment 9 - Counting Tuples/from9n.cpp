#include<iostream>
#include<unordered_map>

using namespace std;
int a[1500], b[1500], c[1500], d[1500];
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	unordered_map<long long , int> m;
	int len;
	long long int x;
	cin >> len >> x;
	for(int i=0; i<len; i++)
		cin >> a[i];
	for(int i=0; i<len; i++)
		cin >> b[i];
	for(int i=0; i<len; i++)
		cin >> c[i];
	for(int i=0; i<len; i++)
		cin >> d[i];

	for(int i=0; i<len; i++)
	{
		for(int j=0; j<len; j++)
		{
			long long n = a[i]+b[j];
			m[n]++;
		}
	}
	unordered_map<long long, int>::iterator it;
	/*for(it = m.begin();it!=m.end();it++)
		cout << it->first << ' '<<it->second <<  '\n';*/
	long long int time=0;
	for(int i=0; i<len; i++)
	{
		for(int j=0; j<len; j++)
		{
			long long num = c[i]+d[j];
			it = m.find(x-num);
			if(it!=m.end())
				time+=it->second;
		}
	}
	cout << time << '\n';
}
