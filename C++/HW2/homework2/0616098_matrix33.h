#ifndef _0616098_MATRIX33_H_
#define _0616098_MATRIX33_H_
#include "0616098_vector3.h"

class matrix33
{
	public:
		matrix33();
		matrix33(vector3 a,vector3 b,vector3 c);
		matrix33(const matrix33 &m);
		vector3                 &operator [](unsigned int);
		const vector3           &operator [] (unsigned int index) const;

		matrix33                &operator = (const matrix33 &m);
		matrix33 	            &operator += (const matrix33 &m);
		matrix33 	            &operator -= (const matrix33 &m);
        matrix33                &operator *= (float f);
		matrix33                &operator /= (float f);
		friend bool             operator == (const matrix33 &m1,const matrix33 &m2);
		friend bool             operator != (const matrix33 &m1,const matrix33 &m2);
		friend matrix33         operator - (const matrix33 &m);
		friend matrix33 	    operator + (const matrix33 &m1,const matrix33 &m2);
		friend matrix33 	    operator - (const matrix33 &m1,const matrix33 &m2);
		friend matrix33         operator * (float f,const matrix33 &m);
		friend matrix33         operator * (const matrix33 &m,float f);
		friend matrix33 	    operator * (const matrix33 &m1,const matrix33 &m2);
		friend matrix33         operator / (const matrix33 &m,float f);
		matrix33 transpose();
		matrix33 identity();
		float determinant()const;
		matrix33 invert()const;

		void setmatrix(vector3 v1In,vector3 v2In,vector3 v3In);
		void printMatrix();
		vector3 v1,v2,v3;
};

#endif
