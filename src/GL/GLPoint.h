#ifndef GLPOINT_H
#define GLPOINT_H
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
 * $Id: GLPoint.h,v 1.2 2002/07/06 18:04:17 southa Exp $
 * $Log: GLPoint.h,v $
 * Revision 1.2  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.1  2002/07/02 18:36:56  southa
 * Selection in designer, mouse buttons
 *
 */

#include "mushCore.h"

class GLPoint
{
public:
    GLPoint(tVal inX=0, tVal inY=0):
        x(inX),
        y(inY)
        {}

    U32 U32XGet(void) const { return static_cast<U32>(x); }
    U32 U32YGet(void) const { return static_cast<U32>(y); }
    void RotateAboutPoint(const GLPoint& inPoint, tVal inAngle)
    {
        x = inPoint.x + (x - inPoint.x) * cos(inAngle) + (y - inPoint.y) * sin(inAngle);
        y = inPoint.y + (y - inPoint.y) * cos(inAngle) - (x - inPoint.x) * sin(inAngle);
    }
    tVal MagnitudeSquared(void) const { return x*x+y*y; }
    void MakeInteger(void)
    {
        double temp;
        modf(x, &temp);
        x=temp;
        modf(y, &temp);
        y=temp;
    }
    void Print(ostream& inOstream) const { inOstream << "(" << x << "," << y << ")"; }
    GLPoint& operator+=(const GLPoint& inPoint) {x+=inPoint.x; y+=inPoint.y; return *this;}
    GLPoint& operator-=(const GLPoint& inPoint) {x-=inPoint.x; y-=inPoint.y; return *this;}
    GLPoint& operator*=(const GLPoint& inPoint) {x*=inPoint.x; y*=inPoint.y; return *this;}
    GLPoint& operator/=(const GLPoint& inPoint) {x/=inPoint.x; y/=inPoint.y; return *this;}
    GLPoint& operator*=(const tVal inOper) {x*=inOper; y*=inOper; return *this;}
    GLPoint& operator/=(const tVal inOper) {x/=inOper; y/=inOper; return *this;}
    tVal x;
    tVal y;
};

inline const GLPoint operator+(const GLPoint& a, const GLPoint& b)
{
    GLPoint retPoint(a);
    return retPoint+=b;
}

inline const GLPoint operator-(const GLPoint& a, const GLPoint& b)
{
    GLPoint retPoint(a);
    return retPoint-=b;
}

inline const GLPoint operator*(const GLPoint& a, const GLPoint& b)
{
    GLPoint retPoint(a);
    return retPoint*=b;
}

inline const GLPoint operator/(const GLPoint& a, const GLPoint& b)
{
    GLPoint retPoint(a);
    return retPoint/=b;
}

inline const GLPoint operator*(const GLPoint& a, tVal inOper)
{
    GLPoint retPoint(a);
    return retPoint*=inOper;
}

inline const GLPoint operator/(const GLPoint& a, tVal inOper)
{
    GLPoint retPoint(a);
    return retPoint/=inOper;
}

inline ostream& operator<<(ostream &s, const GLPoint& inPoint)
{
    inPoint.Print(s);
    return s;
}
#endif
