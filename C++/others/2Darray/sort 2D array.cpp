#include <iostream>
#include <stdio.h>
using namespace std;

void m_sort(int data[][100], int n, int m, int order);
void ms_sort(int data[][100], int n, int m, int order);
int main()
{
	int n,m;
	cout<<"Please input n and m: ";
	cin>>n>>m;
	cout<<"Please input the elements of matrix n*m by row major:\n";
	int a[n][100]={0};
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			cin>>a[i][j];
		}
	}
	int shape;
	cout<<"Select sorted style: 1) top-down&left-right, 2) snake-like ( <ctrl>-d to exit):";
	cin>>shape;
	int order;
	cout<<"Select sorted order: 1) non-increasing order, 2) non-decreasing order ( <ctrl>-d to exit):";
	cin>>order;
	cout<<"The sorted matrix in the ";
    if(shape==1)
        m_sort(a,n,m,order);
    else if(shape==2)
        ms_sort(a,n,m,order);
    if(order==1)
        cout<<"non-increasing order:"<<endl;
    else if(order==2)
        cout<<"non-decreasing order:"<<endl;
    for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			cout<<a[i][j]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
void m_sort(int data[][100], int n, int m, int order)
{
    int b[n*m];
    int index=0;
    for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			b[index]=data[i][j];
			index++;
		}
	}
	if(order==1)
    {
        for(int i=0;i<n*m-1;i++)
        {
            for(int j=0;j<n*m-i-1;j++)
            {
                if(b[j]<b[j+1])
                {
                    int temp=b[j];
                    b[j]=b[j+1];
                    b[j+1]=temp;
                }
            }
        }
    }
	else if(order==2)
    {
        for(int i=0;i<n*m-1;i++)
        {
            for(int j=0;j<n*m-i;j++)
            {
                if(b[j]>b[j+1])
                {
                    int temp=b[j];
                    b[j]=b[j+1];
                    b[j+1]=temp;
                }
            }
        }
    }
    index=0;
    for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			data[i][j]=b[index];
			index++;
		}
	}
}
void ms_sort(int data[][100], int n, int m, int order)
{
    m_sort(data,n,m,order);
    for(int i=1;i<n;i+=2)
	{
		for(int j=0;j<(m/2);j++)
		{
			int temp;
			temp=data[i][j];
			data[i][j]=data[i][m-1-j];
			data[i][m-1-j]=temp;

		}
	}
}
