#include<iostream>
using namespace std;

int sum[2750000];

bool isprime(int n)
{
	if(n==2)
        return true;
	if(n%2==0)
        return false;
	for(int i=3;i*i<=n;i+=2)        //��Ƴֹ̤j2�]��2�����Ƥ��i��
        if(n%i==0)
            return false;
	return true;
}

int main()
{
	for(int i=0;i<2750000;i++)
        sum[i]=0;
	for(int i=2;i<2750000;i++)      //��n����n����]�Ƽƶq
	{
		if(isprime(i))
		{
			long long m=i;
			while(m<2750000)
			{
				for(int j=m;j<2750000;j+=m)
                    sum[j]++;
				m*=i;
			}
		}
	}
	for(int i=1;i<2750000;i++)      //��n��=��n-1��+n����]�Ƽƶq
        sum[i]+=sum[i-1];
	int n,low,high,mid;
	int cas=1;
	while(cin>>n)
	{
		if(n<0)
            break;
		cout<<"Case "<<cas++<<": ";
		low=0,high=2749999;
		while(low<high-1)       //�G���k
		{
			mid=(low+high)/2;
			if(sum[mid]<n)
                low=mid;
			else if(sum[mid]>n)
                high=mid;
			else break;
		}
		if(n==0)
            mid=0;
		if(sum[mid]==n)
            cout<<mid<<"!\n";
		else
            cout<<"Not possible.\n";
	}
	return 0;
}
