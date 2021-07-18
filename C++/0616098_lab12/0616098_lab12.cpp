#include <iostream>
#include <math.h>
using namespace std;
int nopf(int a);                                            //numberofprimefactor
int cp(int a);                                              //checkprime
int main()
{
    int time=1;
    int N;
    cin>>N;
    while(time<1001&&N>=0)
    {
        int out=-1;
        if(N==0)
            out=0;
        else if(N==1)
            out=2;
        else if(N==2)
            out=3;
        else if(N==4)
            out=4;
        else
        {
            int num=4;                                    //numofprimefactor
            int X=5;
            while(N>num)
            {
                if(cp(X)==1)
                {
                    num++;
                    X++;
                }
                else
                    num+=nopf(X++);
            }
            if(N==num)
                out=X-1;
            else
                out=-1;
        }
        cout<<"Case "<<time++<<": ";
        if(out>=0)
            cout<<out<<"!";
        else
            cout<<"Not possible.";
        cout<<endl;
        cin>>N;
    }
    return 0;
}
int cp(int a)
{
    for(int i=2;i<=sqrt(a);i++)
        if(a%i==0)
            return 0;
    return 1;
}
int nopf(int a)
{
    int num=0;
    while(a%2==0)
    {
        a/=2;
        num++;
    }
    while(a%3==0)
    {
        a/=3;
        num++;
    }
    while(a%5==0)
    {
        a/=5;
        num++;
    }
    for(int i=7;i<=sqrt(a);i++)
    {
        if(a==1)
            break;
        if(cp(i)==1)
        {
            while(a%i==0)
            {
                a/=i;
                num++;
            }
        }
    }
    if(a>1)
        num++;
    return num;
}
