#include <iostream>
using namespace std;

int main()
{
    string str;
    cin>>str;
    int c;
    int a[26]={0};
    for(int i=0;i<str.length();i++)
    {
        c=str[i];
        a[c-65]++;
    }
    int max=a[0];
    for(int i=1;i<26;i++)
    {
        if(a[i]>max)
            max=a[i];
    }
    for(int i=max;i>0;i--)
    {
        for(int j=0;j<26;j++)
        {
            if(a[j]==i)
                cout<<j+65<<" "<<a[j]<<endl;
        }
    }
    return 0;
}
