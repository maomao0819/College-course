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
    cout<<"Please input an expression:";
    long s;
    cin>>s;
    RationalO Result(s);
    while(cin.eof()!=true)
    {
        char op=cin.get();
        switch(op)
        {
            case '+':
                long a;
                cin>>a;
                RationalO A(a);
                Result=Result+A;
                break;

            case '-':
                int b;
                cin>>b;
                RationalO B(b);
                Result=Result-B;
                break;

            case '*':
                int c;
                cin>>c;
                RationalO C(c);
                Result=Result*C;
                break;

            case '/':
                int d;
                cin>>d;
                RationalO D(d);
                Result=Result/D;
                break;

            case '\n':
					break;

            default:
					cout<<"wrong input!"<<endl;
					break;
        }
    }
    Result.Reduce();
    cout<<"The answer is "<<Result;
}

