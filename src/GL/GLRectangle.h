#ifndef GLRECTANGLE_H
#define GLRECTANGLE_H
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
 * $Id: GLRectangle.h,v 1.2 2002/07/06 18:04:17 southa Exp $
 * $Log: GLRectangle.h,v $
 * Revision 1.2  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.1  2002/07/02 18:36:56  southa
 * Selection in designer, mouse buttons
 *
 */

#include "mushCore.h"

#include "GLPoint.h"

class GLRectangle
{
public:
    GLRectangle(tVal inMinX=0, tVal inMinY=0, tVal inMaxX=0, tVal inMaxY=0);
    GLRectangle(const GLPoint& inMin, const GLPoint& inMax);
    void Clip(const GLRectangle& inClip);
    void ConstrainPoint(GLPoint& ioPoint) const;
    bool IsWithin(const GLPoint& inPoint) const;
    tVal XSize(void);
    tVal YSize(void);
    GLPoint Size(void);
    GLPoint MinPoint(void) const { return GLPoint(xmin, ymin); }
    void FixUp(void);
    tVal xmin;
    tVal ymin;
    tVal xmax;
    tVal ymax;
};
#endif
