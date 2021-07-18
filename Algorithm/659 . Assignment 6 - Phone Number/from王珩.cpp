#include<iostream>
#include<map>
#include<string>
using namespace std;
char hash_h[26]={'2','2','2','3','3','3','4','4','4','5','5','5','6','6','6','7','0','7','7','8','8','8','9','9','9','0'};
string get_standard_form(string s);
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    int n;
    int c;
    cin>>c;
    while(c--)
    {
        map<string,int> msi;
     	string s;
     	cin>>n;
		int count=0;
	    while(n--)
	    {
	         cin>>s;
	         msi[get_standard_form(s)]++;
	 	}
        map<string,int>::iterator i=msi.begin();
        int mark=0;
        while(i!=msi.end()&&mark<500)
        {

            mark++;
               cout<<i->first<<" "<<i->second<<" mark="<<mark<<"\n";
          	i++;
        }
        while(i!=msi.end())
        {
            if(i->second>1)
            {
               cout<<i->first<<" "<<i->second<<"\n";
               count++;
           	}
          	i++;
        }
		if(count==0)
			cout<<"No duplicate.\n";
		cout<<"\n";
     }
     return 0;
}
string get_standard_form(string s)
{
     string rs="";
     int size=s.size();
     for(int i=0;i<size;i++)
     {
          if(s[i]!='-')
               rs+=s[i];
     }
     size=rs.size();
     for(int i=0;i<size;i++)
     {
          if(rs[i]>='A'&&rs[i]<='Z')
               rs[i]=hash_h[rs[i]-'A'];
     }
     return rs.substr(0,3)+"-"+rs.substr(3);
}
