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
 * $Id: GLPoint.h,v 1.11 2002/08/27 08:56:19 southa Exp $
 * $Log: GLPoint.h,v $
 * Revision 1.11  2002/08/27 08:56:19  southa
 * Source conditioning
 *
 * Revision 1.10  2002/08/18 12:20:40  southa
 * Movement tweaks
 *
 * Revision 1.9  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.8  2002/08/01 16:47:09  southa
 * First multi-box collsion checking
 *
 * Revision 1.7  2002/07/31 16:27:15  southa
 * Collision checking work
 *
 * Revision 1.6  2002/07/19 15:44:39  southa
 * Graphic optimisations
 *
 * Revision 1.5  2002/07/18 13:53:48  southa
 * Tuned player motion
 *
 * Revision 1.4  2002/07/18 11:40:34  southa
 * Overplotting and movement
 *
 * Revision 1.3  2002/07/16 17:48:07  southa
 * Collision and optimisation work
 *
 * Revision 1.2  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.1  2002/07/02 18:36:56  southa
 * Selection in designer, mouse buttons
 *
 */

#include "mushCore.h"
#include "GLRenderable.h"

class GLPoint : public GLRenderable
{
public:
    GLPoint () {}
    explicit GLPoint(tVal inX, tVal inY):
        x(inX),
        y(inY)
        {}

    virtual ~GLPoint() {}
    virtual GLPoint *Clone(void) const { return new GLPoint(*this); }
    virtual void Render(void) const;
    
    U32 U32XGet(void) const { return static_cast<U32>(x); }
    U32 U32YGet(void) const { return static_cast<U32>(y); }
    void RotateAboutZ(const GLPoint& inPoint, tVal inAngle)
    {
        tVal xtemp=x;
        x = inPoint.x + (x - inPoint.x) * cos(inAngle) + (y - inPoint.y) * sin(inAngle);
        y = inPoint.y + (y - inPoint.y) * cos(inAngle) - (xtemp - inPoint.x) * sin(inAngle);
    }
    void RotateAboutZ(tVal inAngle)
    {
        tVal xtemp = x;
        x = x * cos(inAngle) + y * sin(inAngle);
        y = y * cos(inAngle) - xtemp * sin(inAngle);
    }
    tVal MagnitudeSquared(void) const { return x*x+y*y; }
    tVal Magnitude(void) const { return sqrt(MagnitudeSquared()); }
    void ConstrainMagnitude(tVal inMagnitude)
    {
        tVal magnitude=Magnitude();
        if (magnitude > inMagnitude)
        {
            x *= inMagnitude/magnitude;
            y *= inMagnitude/magnitude;
        }
    }
    void MakeInteger(void)
    {
        double temp;
        modf(x, &temp);
        x=temp;
        modf(y, &temp);
        y=temp;
    }
    void Print(ostream& inOstream) const { inOstream << "(" << x << "," << y << ")"; }
    
    const GLPoint& operator+=(const GLPoint& inPoint) {x+=inPoint.x; y+=inPoint.y; return *this;}
    const GLPoint& operator-=(const GLPoint& inPoint) {x-=inPoint.x; y-=inPoint.y; return *this;}
    const GLPoint& operator*=(const GLPoint& inPoint) {x*=inPoint.x; y*=inPoint.y; return *this;}
    const GLPoint& operator/=(const GLPoint& inPoint) {x/=inPoint.x; y/=inPoint.y; return *this;}
    const GLPoint& operator*=(const tVal inOper) {x*=inOper; y*=inOper; return *this;}
    const GLPoint& operator/=(const tVal inOper) {x/=inOper; y/=inOper; return *this;}

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

inline bool operator==(const GLPoint& a, const GLPoint& b)
{
    return a.x == b.x && a.y == b.y;
}

inline bool operator!=(const GLPoint& a, const GLPoint& b)
{
    return a.x != b.x || a.y != b.y;
}

inline ostream& operator<<(ostream &s, const GLPoint& inPoint)
{
    inPoint.Print(s);
    return s;
}
#endif
