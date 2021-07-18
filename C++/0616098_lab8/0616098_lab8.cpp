#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    int loop;
    cin>>loop;
    for(int i=0;i<loop;i++)
    {
        string str;
        cin>>str;
        char str2[35];
        strcpy(str2,str.c_str());
        int num[12]={0};
        int c1=0;
        int c2=0;
        int oper[11]={1};//oper=1 when'+' ; oper=2 when'*'
        for(int j=0;j<strlen(str2);j++)
        {
            if(str[j]>='0'&&str2[j]<='9')
            {
                if(str[j+1]>='0'&&str2[j+1]<='9')
                {
                    num[c1++]=(str2[j]-'0')*10+(str2[j+1]-'0');
                    j++;
                }
                else
                    num[c1++]=str2[j]-'0';
            }
            else if(str2[j]=='+')
                oper[c2++]=1;
            else if(str2[j]=='*')
                oper[c2++]=2;
        }
        long long int num2[13]={0};
        for(int j=0;j<12;j++)
        {
            num2[j]=num[j];
        }
        //mini先乘後加
        long long int mini=0;
        for(int j=0;j<11;j++)
        {
            if(oper[j]==2)
            {
                num2[j+1]*=num2[j];
                num2[j]=0;
            }
        }
        for(int j=0;j<13;j++)
        {
            mini+=num2[j];
        }
        //maxi先加後乘
        long long int maxi=1;
        for(int j=0;j<11;j++)
        {
            if(oper[j]==1)
            {
                num[j+1]+=num[j];
                num[j]=1;
            }
            if(num[j]==0)
                num[j]=1;
        }
        if(num[11]==0)
            num[11]=1;
        for(int j=0;j<12;j++)
        {
            maxi*=num[j];
        }
        cout<<"The maximum and minimum are "<<maxi<<" and "<<mini<<"."<<endl;
    }
    return 0;
}
