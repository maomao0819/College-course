#include <iostream>
#include <math.h>
using namespace std;

int main()
{
	while(1)
	{
		char op;
		float res;
		float x;
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
		cout<<"The answer is: "<<res<<endl;
	}
	return 0;
 }
