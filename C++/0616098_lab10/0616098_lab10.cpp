#include <iostream>
#include <string.h>
using namespace std;
int main()
{
    int time;
    cin>>time;
    //          t,n,b,s,w,e
    int die[6]={1,2,6,5,3,4};
    int die2[6]={1,2,6,5,3,4};
    while(time)
    {
        string str;
        cin>>str;
        int temp;
        if(str[0]=='n')
            {
                temp=die[3];
                die[3]=die[2];
                die[2]=die[1];
                die[1]=die[0];
                die[0]=temp;
            }
        else if(str[0]=='s')
            {
                temp=die[0];
                die[0]=die[1];
                die[1]=die[2];
                die[2]=die[3];
                die[3]=temp;
            }
        else if(str[0]=='e')
            {
                temp=die[0];
                die[0]=die[4];
                die[4]=die[2];
                die[2]=die[5];
                die[5]=temp;
            }
        else if(str[0]=='w')
            {
                temp=die[0];
                die[0]=die[5];
                die[5]=die[2];
                die[2]=die[4];
                die[4]=temp;
            }
        time--;
        if(time==0)
        {
            cout<<die[0]<<endl;
            cin>>time;
            for(int i=0;i<6;i++)
            {
                die[i]=die2[i];
            }
        }
    }
    return 0;
}
