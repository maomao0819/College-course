#include <iostream>
#include <math.h>
using namespace std;

int main()
{
	while(1)
	{
		char op;
		float res,x;
		int y,flag=0;
		cout<<"Please input an expression: ";
		cin>>x>>op>>y;
		if (x<1||x>999||y<1||y>999)
		{
			cout<<"Wrong input!";
			break;
		}
		switch(op)
		{
			case'+':
			    res=x+y;
			    break;

			case'-':
				res=x-y;
				break;

			case'*':
				res=x*y;
				break;

			case'/':
				if(y==0)
					break;
				else
				{
                    res=x/y;
                    break;
				}

		default:
			cout<<"wrong input!"<<endl;
			flag=1;
			break;
		}
		while(1)
		{
			op=cin.get();
			switch(op)
			{
				case'+':
					cin>>y;
					res+=y;
					break;

				case'-':
					cin>>y;
					res-=y;
					break;

				case'*':
					cin>>y;
					res*=y;
					break;

				case'/':
					cin>>y;
					if(y==0)
						break;
					else
					{
                        res/=y;
                        break;
					}

				case'\n':
					break;

				default:
					cout<<"wrong input!"<<endl;
					flag=1;
					break;

			}
			if(op=='\n')
				break;
		}
		if(flag!=1)
        {
            cout<<"The answer is: ";
            int int_res=res;
            if(res==int_res)
                cout<<res<<"/1";
            else
            {
                int domi=2;
                float res2=res*2;
                int int_res2=res2;
                while(res2!=int_res2)
                {
                    domi++;
                    res2=res*domi;
                    int_res2=res2;
                }
                cout<<res2<<"/"<<domi;
            }
            cout<<endl;
        }
	}
	return 0;
 }
