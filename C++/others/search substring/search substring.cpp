#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cctype>
using namespace std;
int main()
{
    string str;
    cout<<"Please input text(at most 10 lines) :\n";
    getline(cin,str);
    string str2;
    transform(str.begin(),str.end(),back_inserter(str2),::tolower);
    string sub;
    cout<<"Please input pattern:"<<endl;
    cin>>sub;
    string sub2;
    transform(sub.begin(),sub.end(),back_inserter(sub2),::tolower);
    size_t position;
    int check=0;
    if(position!=str2.npos)
    {
        position=0;
        while((position=str2.find(sub2,position))!=str2.npos)
        {
            check++;
            if(check==1)
            cout<<"Found at\n";
            size_t position2=position+1;
            int l=1;
            while(position2>120)
            {
                position2-=120;
                l++;
            }
            cout<<"Line "<<l<<" Col "<<position2<<endl;
            position++;
        }
    }
    if(!check)
        cout<<"Not found.";
    return 0;
}
