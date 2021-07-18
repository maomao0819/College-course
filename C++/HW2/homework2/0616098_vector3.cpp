#include "0616098_vector3.h"
#include <iostream>
#include <math.h>

    vector3::vector3()
    {
        set(0.0,0.0,0.0);
    }
    vector3::vector3(float inX, float inY=0, float inZ=0)
    {
        set(inX,inY,inZ);
    }
    vector3::vector3(const vector3 &v)
    {
        set(v.x,v.y,v.z);
    }
    float&                 vector3::operator [] (unsigned int index)
    {
        if(index==0)
            return x;
        else if(index==1)
            return y;
        else if(index==2)
            return z;
    }
	const float&           vector3::operator [] (unsigned int index) const
	{
        if(index==0)
            return x;
        else if(index==1)
            return y;
        else if(index==2)
            return z;
	}

	vector3&               vector3::operator =  (const vector3 &v)
	{
	    x=v.x;
	    y=v.y;
	    z=v.z;
	    return *this;
	}
	vector3&               vector3::operator += (const vector3 &v)
	{
	    x+=v.x;
	    y+=v.y;
	    z+=v.z;
	    return *this;
	}
	vector3&               vector3::operator -= (const vector3 &v)
	{
	    x-=v.x;
	    y-=v.y;
	    z-=v.z;
	    return *this;
	}
	vector3&               vector3::operator *= (float f)
	{
	    x*=f;
	    y*=f;
	    z*=f;
	    return *this;
	}
	vector3&               vector3::operator /= (float f)
	{
	    x/=f;
	    y/=f;
	    z/=f;
	    return *this;
	}
	bool                  operator == (const vector3 &a, const vector3 &b)
	{
	    return (a.x == b.x && a.y == b.y && a.z == b.z);
	}
	bool                  operator != (const vector3 &a, const vector3 &b)
	{
	    return (a.x!=b.x||a.y!=b.y||a.z!=b.z);
	}
	vector3               operator - (const vector3 &a)
	{
	    float x=-a.x;
	    float y=-a.y;
	    float z=-a.z;
	    vector3 tmp(x, y, z);
	    return tmp;
	}
	vector3               operator + (const vector3 &a, const vector3 &b)
	{
	    float x=a.x+b.x;
	    float y=a.y+b.y;
	    float z=a.z+b.z;
	    vector3 tmp(x, y, z);
	    return tmp;
	}
	vector3              operator - (const vector3 &a, const vector3 &b)
	{
	    float x=a.x-b.x;
	    float y=a.y-b.y;
	    float z=a.z-b.z;
	    vector3 tmp(x, y, z);
	    return tmp;
	}
	vector3              operator * (const vector3 &v, float f)
	{
	    float x=v.x*f;
	    float y=v.y*f;
	    float z=v.z*f;
	    vector3 tmp(x, y, z);
	    return tmp;
	}
	vector3             operator * (float f, const vector3 &v)
	{
	    float x=f*v.x;
	    float y=f*v.y;
	    float z=f*v.z;
	    vector3 tmp(x, y, z);
	    return tmp;
	}
	vector3             operator / (const vector3 &v, float f)
	{
	    float x=v.x/f;
	    float y=v.y/f;
	    float z=v.z/f;
	    vector3 tmp(x, y, z);
	    return tmp;
	}

	void vector3::set(float xIn, float yIn, float zIn)
	{
	    x=xIn;
	    y=yIn;
	    z=zIn;
	}
    float vector3::length()const
    {
        float a = x;
        float b = y;
        float c = z;
        return sqrt(a*a+b*b+c*c);
    }

    void vector3::printVector3() const
    {
        std::cout<<"("<<x<<", "<<y<<", "<<z<<")"<<std::endl;
    }
