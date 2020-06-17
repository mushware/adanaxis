//%includeGuardStart {
#ifndef GLPOINT_H
#define GLPOINT_H
//%includeGuardStart } ksFBt9y8oVQ4oABmPBOZJA
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLPoint.h
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
//%Header } uG0EKTge4bRoOXh3McDkgg
/*
 * $Id: GLPoint.h,v 1.27 2006/06/01 15:38:51 southa Exp $
 * $Log: GLPoint.h,v $
 * Revision 1.27  2006/06/01 15:38:51  southa
 * DrawArray verification and fixes
 *
 * Revision 1.26  2005/05/19 13:01:59  southa
 * Mac release work
 *
 * Revision 1.25  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.24  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.23  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.22  2003/08/21 23:08:24  southa
 * Fixed file headers
 *
 * Revision 1.21  2003/01/13 14:31:55  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.20  2003/01/11 17:07:50  southa
 * Mushcore library separation
 *
 * Revision 1.19  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.18  2003/01/09 14:56:58  southa
 * Created Mushcore
 *
 * Revision 1.17  2002/12/29 20:30:52  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.16  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.15  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.14  2002/10/12 15:24:58  southa
 * Facet renderer
 *
 * Revision 1.13  2002/10/12 11:22:21  southa
 * GraphicModel work
 *
 * Revision 1.12  2002/10/10 13:51:16  southa
 * Speed fixes and various others
 *
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

#include "GLRenderable.h"
#include "GLStandard.h"
#include "mushMushcore.h"

class GLPoint : public GLRenderable
{
public:
    GLPoint () {}
    explicit GLPoint(Mushware::tVal inX, Mushware::tVal inY):
        x(inX),
        y(inY)
        {}

    virtual ~GLPoint() {}
    virtual GLPoint *Clone(void) const { return new GLPoint(*this); }
    virtual void Render(void) const;

    void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    void Unpickle(MushcoreXML& inXML);
    void Unpickle(std::istream& ioIn);
    
    Mushware::U32 U32XGet(void) const { return static_cast<Mushware::U32>(x); }
    Mushware::U32 U32YGet(void) const { return static_cast<Mushware::U32>(y); }
    void RotateAboutZ(const GLPoint& inPoint, Mushware::tVal inAngle)
    {
        Mushware::tVal xtemp=x;
        x = inPoint.x + (x - inPoint.x) * cos(inAngle) + (y - inPoint.y) * sin(inAngle);
        y = inPoint.y + (y - inPoint.y) * cos(inAngle) - (xtemp - inPoint.x) * sin(inAngle);
    }
    void RotateAboutZ(Mushware::tVal inAngle)
    {
        Mushware::tVal xtemp = x;
        x = x * cos(inAngle) + y * sin(inAngle);
        y = y * cos(inAngle) - xtemp * sin(inAngle);
    }
    Mushware::tVal MagnitudeSquared(void) const { return x*x+y*y; }
    Mushware::tVal Magnitude(void) const { return sqrt(MagnitudeSquared()); }
    void ConstrainMagnitude(Mushware::tVal inMagnitude)
    {
        Mushware::tVal magnitude=Magnitude();
        if (magnitude > inMagnitude)
        {
            x *= inMagnitude/magnitude;
            y *= inMagnitude/magnitude;
        }
    }
    void MakeInteger(void)
    {
        double temp;
        std::modf(x, &temp);
        x=temp;
        std::modf(y, &temp);
        y=temp;
    }

    void ConvertTo(GLfloat outArray[2])
    {
        outArray[0]=x;
        outArray[1]=y;
    };
    const GLPoint& operator+=(const GLPoint& inPoint) {x+=inPoint.x; y+=inPoint.y; return *this;}
    const GLPoint& operator-=(const GLPoint& inPoint) {x-=inPoint.x; y-=inPoint.y; return *this;}
    const GLPoint& operator*=(const GLPoint& inPoint) {x*=inPoint.x; y*=inPoint.y; return *this;}
    const GLPoint& operator/=(const GLPoint& inPoint) {x/=inPoint.x; y/=inPoint.y; return *this;}
    const GLPoint& operator*=(const Mushware::tVal inOper) {x*=inOper; y*=inOper; return *this;}
    const GLPoint& operator/=(const Mushware::tVal inOper) {x/=inOper; y/=inOper; return *this;}

    Mushware::tVal x;
    Mushware::tVal y;
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

inline const GLPoint operator*(const GLPoint& a, Mushware::tVal inOper)
{
    GLPoint retPoint(a);
    return retPoint*=inOper;
}

inline const GLPoint operator/(const GLPoint& a, Mushware::tVal inOper)
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

inline std::ostream& operator<<(std::ostream &s, const GLPoint& inPoint)
{
    inPoint.Pickle(s);
    return s;
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
