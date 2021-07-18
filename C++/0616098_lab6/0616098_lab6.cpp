#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{

    long long int a[10000];
    while (scanf("%lld",&a[0])!=EOF)
    {
        cout<<a[0]<<endl;
        while (scanf("%lld",&a[1])!=EOF)
        {
            cout<<(a[0]+a[1])/2<<"\n";
            if(a[0]>a[1])
            {
                long long int temp;
                temp=a[0];
                a[0]=a[1];
                a[1]=temp;
            }
            int index=2;
            for(int n=3;n<10000;n++)
            {
                while(scanf("%lld",&a[index])!=EOF)
                {
                    int position=0;
                    while(a[index]>a[position])
                        position++;
                    long long int temp=a[index];
                    for(int j=index;j>position;j--)
                            a[j]=a[j-1];
                    a[position]=temp;
                    if(index%2==0)
                        cout<<a[index/2]<<endl;
                    else
                        cout<<(a[index/2]+a[index/2+1])/2<<endl;
                    index++;
                }
            }
        }
    }
    return 0;
}
