#include <iostream>
#include <stdio.h>

using namespace std;
#define MAX 5000
int Fib[MAX+1][500]={0};
int main()
{
    Fib[1][0]=1;
    for(int i=2;i<=MAX;i++)
    {
        for(int j=0;j<500;j++)
        {
            Fib[i][j]=Fib[i][j]+Fib[i-1][j]+Fib[i-2][j];
            short int carry=Fib[i][j]/1000;
            Fib[i][j]%=1000;
            Fib[i][j+1]+=carry;
        }
    }
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        cout<<"The Fibonacci number for "<<n<<" is ";
        if(n==0)
			cout<<"0"<<endl;
        else
		{
            short int i=500;
            while(Fib[n][--i]==0);
            cout<<Fib[n][i--];
            for(;i>=0;i--)
                cout<<Fib[n][i];
            cout<<endl;
        }
    }
	return 0;
}
