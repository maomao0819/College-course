#include <iostream>
#include <stdio.h>
using namespace std;
int main()
{
    int n;
    int a[1000]={0};
    while((scanf("%d",&n))!=EOF)
    {
        for(int i=0;i<n;i++)
        {
            cin>>a[i];
        }
        int time=0;
        for(int i=0;i<n-1;i++)
        {
            for(int j=0;j<n-i-1;j++)
                if(a[j]>a[j+1])
                {
                    time++;
                    int temp=a[j+1];
                    a[j+1]=a[j];
                    a[j]=temp;
                }
        }
        cout<<"Minimum exchange operations : "<<time<<endl;
    }
}
