#include <iostream>
using namespace std;
class RationalO
{
    friend ostream &operator << (ostream &o,const RationalO &r);
    public:
        RationalO()
        {
            Numerator=0;
            Denominator=1;
        }
        RationalO(long n,long d=1)
        {
            Numerator=n;
            Denominator=d;
        }
        RationalO(const RationalO &r)
        {
            Numerator=r.Numerator;
            Denominator=r.Denominator;
        }
        void setNumerator(long n)
        {
            Numerator=n;
        }
        void setDenominator(long d)
        {
            Denominator=d;
        }
        long getNumerator()
        {
            return Numerator;
        }
        long getDenominator()
        {
            return Denominator;
        }
        RationalO operator + (RationalO &r)
        {
            RationalO result;
            result.Numerator=this->Numerator*r.Denominator+r.Numerator*this->Denominator;
            result.Denominator=this->Denominator*r.Denominator;
            return result;
        }
        RationalO operator - (RationalO &r)
        {
            RationalO result;
            result.Numerator=this->Numerator*r.Denominator-r.Numerator*this->Denominator;
            result.Denominator=this->Denominator*r.Denominator;
            return result;
        }
        RationalO operator * (RationalO &r)
        {
            RationalO result;
            result.Numerator=this->Numerator*r.Numerator;
            result.Denominator=this->Denominator*r.Denominator;
            return result;
        }
        RationalO operator / (RationalO &r)
        {
            RationalO result;
            result.Numerator=this->Numerator*r.Denominator;
            result.Denominator=this->Denominator*r.Numerator;
            return result;
        }
        RationalO &operator = (const RationalO &r)
        {
            if (&r != this)
            {
                setNumerator(r.Numerator);
                setDenominator(r.Denominator);
            }
            return *this;
        }
        bool operator == (const RationalO &r)
        {
            return  (Numerator==r.Numerator&&Denominator==r.Denominator);
        }
        bool operator != (const RationalO &r)
        {
            return *this==r;
        }
        bool operator < (const RationalO &r)
        {
            if((Numerator/Denominator)<(r.Numerator/r.Denominator))
                return true;
            else
                return false;
        }
        bool operator > (const RationalO &r)
        {
            if((Numerator/Denominator)>(r.Numerator/r.Denominator))
                return true;
            else
                return false;
        }
        void Reduce()
        {
            long gcd=Gcd(Numerator,Denominator);
            Numerator/=gcd;
            Denominator/=gcd;
        }
        long Gcd(long a,long b)
        {
            if(a<0)
                a*=-1;
            if(b<0)
                b*=-1;
            if(a<b)
            {
                int temp=a;
                a=b;
                b=temp;
            }
            if(a%b==0)
                return a;
            while(a%b)
            {
                int temp=b;
                b=a%b;
                a=temp;
            }
            return a;
        }
        long Lcm(long a,long b)
        {
            return a*b/Gcd(a,b);
        }
    private:
        long Numerator;
        long Denominator;
};
ostream &operator << (ostream &o,const RationalO &r)
{
    o << r.Numerator << " / " << r.Denominator;
    return o;
}
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
