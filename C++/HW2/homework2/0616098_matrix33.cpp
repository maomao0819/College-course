#include "0616098_matrix33.h"
#include <iostream>

		matrix33::matrix33()
		{
		    setmatrix(vector3(),vector3(),vector3());
		}
		matrix33::matrix33(vector3 a,vector3 b=vector3(),vector3 c=vector3())
		{
			setmatrix(a,b,c);
		}
		matrix33::matrix33(const matrix33 &m)
		{
			setmatrix(m.v1,m.v2,m.v3);
		}
		vector3&        matrix33::operator [] (unsigned int index)
		{
			if(index==0)return v1;
			else if(index==1)return v2;
			else if(index==2)return v3;
		}
		const vector3&  matrix33::operator [] (unsigned int index) const
		{
			if(index==0)return v1;
			else if(index==1)return v2;
			else if(index==2)return v3;
		}
		matrix33&       matrix33::operator = (const matrix33 &m)
        {
            v1=m.v1;
            v2=m.v2;
            v3=m.v3;
            return *this;
        }
        matrix33& 	    matrix33::operator += (const matrix33 &m)
        {
            v1+=m.v1;
            v2+=m.v2;
            v3+=m.v3;
            return *this;
        }
        matrix33& 	    matrix33::operator -= (const matrix33 &m)
        {
            v1-=m.v1;
            v2-=m.v2;
            v3-=m.v3;
            return *this;
        }
		matrix33&       matrix33::operator *= (float f)
		{
			v1*=f;
			v2*=f;
			v3*=f;
			return *this;
		}
		matrix33&       matrix33::operator /= (float f)
		{
			v1/=f;
			v2/=f;
			v3/=f;
			return *this;
		}
		bool            operator == (const matrix33 &m1,const matrix33 &m2)
		{
			return (m1.v1==m2.v1&&m1.v2==m2.v2&&m1.v3==m2.v3);
		}
		bool            operator != (const matrix33 &m1,const matrix33 &m2)
		{
			return (m1.v1!=m2.v1||m1.v2!=m2.v2||m1.v3!=m2.v3);
		}
		matrix33        operator - (const matrix33 &m)
        {
            return (-m.v1,-m.v2,-m.v3);
        }
		matrix33        operator + (const matrix33 &m1,const matrix33 &m2)
		{
			return matrix33(m1.v1+m2.v1,m1.v2+m2.v2,m1.v3+m2.v3);
		}
		matrix33        operator - (const matrix33 &m1,const matrix33 &m2)
		{
			return matrix33(m1.v1-m2.v1,m1.v2-m2.v2,m1.v3-m2.v3);
		}
		matrix33        operator * (float f,const matrix33 &m)
		{
			return matrix33(f*m.v1,f*m.v2,f*m.v3);
		}
		matrix33        operator *(const matrix33 &m,float f)
		{
			return matrix33(m.v1*f,m.v2*f,m.v3*f);
		}
		matrix33        operator * (const matrix33 &m1,const matrix33 &m2)
		{
			vector3 a,b,c,d,e,f,vec1,vec2,vec3;
			a=m1.v1,b=m1.v2,c=m1.v3,d=m2.v1,e=m2.v2,f=m2.v3;

			vec1.x=a.x*d.x+b.x*d.y+c.x*d.z;
            vec2.x=a.x*e.x+b.x*e.y+c.x*e.z;
			vec3.x=a.x*f.x+b.x*f.y+c.x*f.z;
			vec1.y=a.y*d.x+b.y*d.y+c.y*d.z;
			vec2.y=a.y*e.x+b.y*e.y+c.y*e.z;
			vec3.y=a.y*f.x+b.y*f.y+c.y*f.z;
			vec1.z=a.z*d.x+b.z*d.y+c.z*d.z;
			vec2.z=a.z*e.x+b.z*e.y+c.z*e.z;
			vec3.z=a.z*f.x+b.z*f.y+c.z*f.z;

			return matrix33(vec1,vec2,vec3);
		}
		matrix33        operator / (const matrix33 &m,float f)
		{
			return matrix33(m.v1/f,m.v2/f,m.v3/f);
		}
		matrix33 matrix33::transpose()
		{
		    int temp=v1.y;
		    v1.y=v2.x;
		    v2.x=temp;
		    temp=v1.z;
		    v1.z=v3.x;
		    v3.x=temp;
		    temp=v2.z;
		    v2.z=v3.y;
		    v3.y=temp;
		}
		matrix33 matrix33::identity()
		{
			v1=vector3(1,0,0);
			v2=vector3(0,1,0);
			v3=vector3(0,0,1);
		}
		float matrix33::determinant()const
		{
			float det=v1.x*(v2.y*v3.z-v2.z*v3.y)+v1.y*(v2.z*v3.x-v2.x*v3.z)+v1.z*(v2.x*v3.y-v2.y*v3.x);
			return det;
		}
		matrix33 matrix33::invert()const
		{
			float det=determinant();
			vector3 a,b,c;
			a=v1,b=v2,c=v3;

			a.x=(1/det)*(v2.y*v3.z-v2.z*v3.y);
			a.y=-(1/det)*(v1.y*v3.z-v3.y*v1.z);
			a.z=(1/det)*(v1.y*v2.z-v2.y*v1.z);
			b.x=-(1/det)*(v2.x*v3.z-v2.z*v3.x);
			b.y=(1/det)*(v1.x*v3.z-v3.x*v1.z);
			b.z=-(1/det)*(v1.x*v2.z-v2.x*v1.z);
			c.x=(1/det)*(v2.x*v3.y-v2.y*v3.x);
			c.y=-(1/det)*(v1.x*v3.y-v3.x*v1.y);
			c.z=(1/det)*(v1.x*v2.y-v2.x*v1.y);

			return matrix33(a,b,c);
		}
		void matrix33::setmatrix(vector3 v1In,vector3 v2In,vector3 v3In)
        {
            v1=v1In;
            v2=v2In;
            v3=v3In;
        }
		void matrix33::printMatrix()
		{
			std::cout<<v1.x<<" "<<v2.x<<" "<<v3.x<<" \n";
			std::cout<<v1.y<<" "<<v2.y<<" "<<v3.y<<" \n";
			std::cout<<v1.z<<" "<<v2.z<<" "<<v3.z<<" \n";
		}
