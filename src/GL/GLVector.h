#ifndef GLVECTOR_H
#define GLVECTOR_H
/*****************************************************************************
*
* (Mushware file header version 1.0)
*
* This file contains original work by Andy Southgate.  Contact details can be
* found at http://www.mushware.co.uk.  This file was placed in the Public
* Domain by Andy Southgate and Mushware Limited in 2002.
*
* This software carries NO WARRANTY of any kind.
*
****************************************************************************/

/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"
#include "GLRenderable.h"

class GLVector : public GLRenderable
{
public:
    GLVector () {}
    explicit GLVector(tVal inX, tVal inY, tVal inZ):
    x(inX),
    y(inY),
    z(inZ)
{}

    virtual GLVector *Clone(void) const { return new GLVector(*this); }
    virtual void Render(void) const;

    U32 U32XGet(void) const { return static_cast<U32>(x); }
    U32 U32YGet(void) const { return static_cast<U32>(y); }
    U32 U32ZGet(void) const { return static_cast<U32>(z); }
    void RotateAboutZ(const GLVector& inVector, tVal inAngle)
    {
        tVal xtemp=x;
        x = inVector.x + (x - inVector.x) * cos(inAngle) + (y - inVector.y) * sin(inAngle);
        y = inVector.y + (y - inVector.y) * cos(inAngle) - (xtemp - inVector.x) * sin(inAngle);
    }
    void RotateAboutZ(tVal inAngle)
    {
        tVal xtemp = x;
        x = x * cos(inAngle) + y * sin(inAngle);
        y = y * cos(inAngle) - xtemp * sin(inAngle);
    }
    tVal MagnitudeSquared(void) const { return x*x+y*y+z*z; }
    tVal Magnitude(void) const { return sqrt(MagnitudeSquared()); }
    void ConstrainMagnitude(tVal inMagnitude)
    {
        tVal magnitude=Magnitude();
        if (magnitude > inMagnitude)
        {
            x *= inMagnitude/magnitude;
            y *= inMagnitude/magnitude;
            z *= inMagnitude/magnitude;
        }
    }
    void MakeInteger(void)
    {
        double temp;
        modf(x, &temp);
        x=temp;
        modf(y, &temp);
        y=temp;
        modf(z, &temp);
        z=temp;
    }
    void Print(ostream& inOstream) const { inOstream << "(" << x << "," << y << "," << z << ")"; }

    const GLVector& operator+=(const GLVector& inVector) {x+=inVector.x; y+=inVector.y; z+=inVector.z; return *this;}
    const GLVector& operator-=(const GLVector& inVector) {x-=inVector.x; y-=inVector.y; z-=inVector.z; return *this;}
    const GLVector& operator*=(const GLVector& inVector) {x*=inVector.x; y*=inVector.y; z*=inVector.z; return *this;}
    const GLVector& operator/=(const GLVector& inVector) {x/=inVector.x; y/=inVector.y; z/=inVector.z; return *this;}
    const GLVector& operator*=(const tVal inOper) {x*=inOper; y*=inOper; z*=inOper; return *this;}
    const GLVector& operator/=(const tVal inOper) {x/=inOper; y/=inOper; z/=inOper; return *this;}

    tVal x;
    tVal y;
    tVal z;
};

inline const GLVector operator+(const GLVector& a, const GLVector& b)
{
    GLVector retVector(a);
    return retVector+=b;
}

inline const GLVector operator-(const GLVector& a, const GLVector& b)
{
    GLVector retVector(a);
    return retVector-=b;
}

inline const GLVector operator*(const GLVector& a, const GLVector& b)
{
    GLVector retVector(a);
    return retVector*=b;
}

inline const GLVector operator/(const GLVector& a, const GLVector& b)
{
    GLVector retVector(a);
    return retVector/=b;
}

inline const GLVector operator*(const GLVector& a, tVal inOper)
{
    GLVector retVector(a);
    return retVector*=inOper;
}

inline const GLVector operator/(const GLVector& a, tVal inOper)
{
    GLVector retVector(a);
    return retVector/=inOper;
}

inline bool operator==(const GLVector& a, const GLVector& b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

inline bool operator!=(const GLVector& a, const GLVector& b)
{
    return a.x != b.x || a.y != b.y || a.z != b.z;
}

inline ostream& operator<<(ostream &s, const GLVector& inVector)
{
    inVector.Print(s);
    return s;
}
#endif

