#include <iostream>
#include <string.h>
#include <string>
using namespace std;

bool compare(string s,string t,int len);
int main()
{
    string s;   //s���Ĥ@�Ӧr��
    cin>>s;
    string t;   //t���ĤG�Ӧr��
    cin>>t;
    int s_len=s.length();
    int t_len=t.length();
    if(s_len!=t_len)    //�������
        cout<<"NO";
    else
    {
        if(compare(s,t,s_len)==true)
            cout<<"YES";
        else
            cout<<"NO";
    }
    return 0;
}
bool compare(string s,string t,int len) //len�O�r�����
{
    if(len==2)
    {
        if((s[0]==t[0]&&s[1]==t[1])||(s[0]==t[1]&&s[1]==t[0]))
            return true;
        return false;
    }
    bool check=true;    //�����]��Ӧr��@��
    for(int i=0;i<len;i++)  //�_�ƪ��ת��@�����N�^��FALSE
    {
        if(s[i]!=t[i])
        {
            if(len%2==1)
                return false;
            check=false;
            break;
        }
    }
    if(check)
        return true;
    len/=2;
    string sl;
    string sr;
    string tl;
    string tr;
    sl.assign(s,0,len);      //��s�qindex0�����len��sr
    sr.assign(s,len,len);
    tl.assign(t,0,len);
    tr.assign(t,len,len);
    return ((compare(sl,tr,len)&&compare(sr,tl,len))||(compare(sr,tr,len)&&compare(sl,tl,len)));
}
