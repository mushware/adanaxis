#ifndef GLVECTOR_H
#define GLVECTOR_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GLVector.h,v 1.8 2003/01/09 14:56:59 southa Exp $
 * $Log: GLVector.h,v $
 * Revision 1.8  2003/01/09 14:56:59  southa
 * Created Mushcore
 *
 * Revision 1.7  2002/12/29 20:30:53  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.6  2002/12/20 13:17:37  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/10/22 20:42:02  southa
 * Source conditioning
 *
 * Revision 1.4  2002/10/12 15:25:11  southa
 * Facet renderer
 *
 * Revision 1.3  2002/10/12 11:22:21  southa
 * GraphicModel work
 *
 * Revision 1.2  2002/10/08 21:44:09  southa
 * 3D maps
 *
 * Revision 1.1  2002/10/07 17:49:45  southa
 * Multiple values per std::map element
 *
 */

#include "GLRenderable.h"
#include "GLStandard.h"
#include "Mushcore.h"

class GLVector : public GLRenderable
{
public:
    GLVector () {}
    explicit GLVector(Mushware::tVal inX, Mushware::tVal inY, Mushware::tVal inZ):
    x(inX),
    y(inY),
    z(inZ)
{}

    virtual GLVector *Clone(void) const { return new GLVector(*this); }
    virtual void Render(void) const;
    
    void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    void Unpickle(MushcoreXML& inXML);
    void Unpickle(std::istream& ioIn);
    
    Mushware::U32 U32XGet(void) const { return static_cast<U32>(x); }
    Mushware::U32 U32YGet(void) const { return static_cast<U32>(y); }
    Mushware::U32 U32ZGet(void) const { return static_cast<U32>(z); }
    void RotateAboutZ(const GLVector& inVector, Mushware::tVal inAngle)
    {
        Mushware::tVal xtemp=x;
        x = inVector.x + (x - inVector.x) * cos(inAngle) + (y - inVector.y) * sin(inAngle);
        y = inVector.y + (y - inVector.y) * cos(inAngle) - (xtemp - inVector.x) * sin(inAngle);
    }
    void RotateAboutZ(Mushware::tVal inAngle)
    {
        Mushware::tVal xtemp = x;
        x = x * cos(inAngle) + y * sin(inAngle);
        y = y * cos(inAngle) - xtemp * sin(inAngle);
    }
    Mushware::tVal MagnitudeSquared(void) const { return x*x+y*y+z*z; }
    Mushware::tVal Magnitude(void) const { return sqrt(MagnitudeSquared()); }
    void ConstrainMagnitude(Mushware::tVal inMagnitude)
    {
        Mushware::tVal magnitude=Magnitude();
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

    void ConvertTo(GLfloat outArray[3])
    {
        outArray[0]=x;
        outArray[1]=y;
        outArray[2]=z;
    };
    
    const GLVector& operator+=(const GLVector& inVector) {x+=inVector.x; y+=inVector.y; z+=inVector.z; return *this;}
    const GLVector& operator-=(const GLVector& inVector) {x-=inVector.x; y-=inVector.y; z-=inVector.z; return *this;}
    const GLVector& operator*=(const GLVector& inVector) {x*=inVector.x; y*=inVector.y; z*=inVector.z; return *this;}
    const GLVector& operator/=(const GLVector& inVector) {x/=inVector.x; y/=inVector.y; z/=inVector.z; return *this;}
    const GLVector& operator*=(const Mushware::tVal inOper) {x*=inOper; y*=inOper; z*=inOper; return *this;}
    const GLVector& operator/=(const Mushware::tVal inOper) {x/=inOper; y/=inOper; z/=inOper; return *this;}

    Mushware::tVal x;
    Mushware::tVal y;
    Mushware::tVal z;
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

inline const GLVector operator*(const GLVector& a, Mushware::tVal inOper)
{
    GLVector retVector(a);
    return retVector*=inOper;
}

inline const GLVector operator/(const GLVector& a, Mushware::tVal inOper)
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

inline std::ostream& operator<<(std::ostream &s, const GLVector& inVector)
{
    inVector.Pickle(s);
    return s;
}
#endif

