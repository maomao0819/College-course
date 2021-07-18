#include <iostream>
#include <vector>
#include <queue>
using namespace std;
vector<int> v[100003];
queue<int> q;
struct robin
{
	int color;
	int distance;
};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int n,max=0;
	cin>>n;
	robin arr[n];
	for(int i=0;i<n-1;i++)
    {
		//v[i].clear();
		int a,b;
		cin>>a;
		cin>>b;
        v[a].push_back(b);
        v[b].push_back(a);
	}
	for(int i=0;i<n;i++)
    {
        arr[i].color=0;
        arr[i].distance=0;
    }
	arr[0].color=1;
	q.push(0);
	vector<int>::iterator it;
	while(q.size()!=0)
	{
		int i=q.front();
		for(it=v[i].begin();it!=v[i].end();it++)
		{
			if(arr[*it].color==0)
			{
				arr[*it].color=1;
				arr[*it].distance=arr[i].distance+1;
				q.push(*it);
			}
		}
		q.pop();
	}
    int temp=0; ///find the index of the temp max distance
    for(int i=0;i<n;i++)
    {
        if(max<=arr[i].distance)
        {
            max=arr[i].distance;
            temp=i;
        }
    }
    //find again
    for(int i=0;i<n;i++)
    {
        arr[i].color=0;
        arr[i].distance=0;
    }
    arr[temp].color=1;
    q.push(temp);
    while(q.size()!=0)
    {
        int i=q.front();
        for(it=v[i].begin();it!=v[i].end();it++)
        {
            if(arr[*it].color==0)
            {
                arr[*it].color=1;
                arr[*it].distance=arr[i].distance+1;
                q.push(*it);
            }
        }
        q.pop();
	}
    temp=0;
    for(int i=0;i<n;i++)
    {
        if(max<=arr[i].distance)
        {
            max=arr[i].distance;
            temp=i;
        }
    }
    cout<<max;
    return 0;
}







