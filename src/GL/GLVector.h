//%includeGuardStart {
#ifndef GLVECTOR_H
#define GLVECTOR_H
//%includeGuardStart } Qn8k4yBWQMlQk1Z7z9YMqw
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLVector.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } ezfOF66iq19fNcRD5pRcTg
/*
 * $Id: GLVector.h,v 1.16 2006/06/01 15:38:55 southa Exp $
 * $Log: GLVector.h,v $
 * Revision 1.16  2006/06/01 15:38:55  southa
 * DrawArray verification and fixes
 *
 * Revision 1.15  2005/05/19 13:02:01  southa
 * Mac release work
 *
 * Revision 1.14  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.13  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.12  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
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
#include "mushMushcore.h"

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
