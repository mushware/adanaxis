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
 * $Id: GLPoint.h,v 1.1 2002/07/02 18:36:56 southa Exp $
 * $Log: GLPoint.h,v $
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
    void Print(ostream& inOstream) const { inOstream << "(" << x << "," << y << ")"; }
    GLPoint& operator+=(const GLPoint inPoint) {x+=inPoint.x;y+=inPoint.y;  return *this;}
    tVal x;
    tVal y;
};

inline GLPoint operator+(const GLPoint& a, const GLPoint& b)
{
    GLPoint retPoint(a);
    return retPoint+=b;
}

inline ostream& operator<<(ostream &s, const GLPoint& inPoint)
{
    inPoint.Print(s);
    return s;
}
#endif
