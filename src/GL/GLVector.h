//%includeGuardStart {
#ifndef GLVECTOR_H
#define GLVECTOR_H
//%includeGuardStart } Qn8k4yBWQMlQk1Z7z9YMqw
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLVector.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 1Np8XWRMUwif/0MnxBp61Q
/*
 * $Id: GLVector.h,v 1.11 2003/08/21 23:08:33 southa Exp $
 * $Log: GLVector.h,v $
 * Revision 1.11  2003/08/21 23:08:33  southa
 * Fixed file headers
 *
 * Revision 1.10  2003/01/11 17:07:51  southa
 * Mushcore library separation
 *
 * Revision 1.9  2003/01/11 13:03:12  southa
 * Use Mushcore header
 *
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

Mushware::U32 U32XGet(void) const { return static_cast<Mushware::U32>(x); }
    Mushware::U32 U32YGet(void) const { return static_cast<Mushware::U32>(y); }
    Mushware::U32 U32ZGet(void) const { return static_cast<Mushware::U32>(z); }
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

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
