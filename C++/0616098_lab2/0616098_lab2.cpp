#include <iostream>
#include <math.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
int main(int argc, char** argv) {
	while(1)
    {
        int a,b;
        cin>>a>>b;
        if(a==0&&b==0)
            break;
        int i;
        int c=0;
        for(i=1;i<=sqrt(b);i++)
        {
        	if(i*i<=b&&i*i>=a)
        		c+=1;
		}
        cout<<c<<endl;
    }
	return 0;
}

