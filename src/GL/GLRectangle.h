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
 * $Id: GLRectangle.h,v 1.4 2002/07/18 11:40:34 southa Exp $
 * $Log: GLRectangle.h,v $
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

#include "GLPoint.h"
#include "GLRenderable.h"

class GLRectangle : public GLRenderable
{
public:
    GLRectangle(tVal inMinX=0, tVal inMinY=0, tVal inMaxX=0, tVal inMaxY=0);
    GLRectangle(const GLPoint& inMin, const GLPoint& inMax);

    virtual GLRectangle *Clone(void) const { return new GLRectangle(*this); }
    virtual void Render(void) const;

    void Clip(const GLRectangle& inClip);
    void ConstrainPoint(GLPoint& ioPoint) const;
    bool IsWithin(const GLPoint& inPoint) const;
    tVal XSize(void) const;
    tVal YSize(void) const;
    GLPoint Size(void) const;
    GLPoint MinPoint(void) const { return GLPoint(xmin, ymin); }
    void FixUp(void);
    
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    
    tVal xmin;
    tVal ymin;
    tVal xmax;
    tVal ymax;
};

inline ostream& operator<<(ostream &s, const GLRectangle& inRect)
{
    inRect.Pickle(s);
    return s;
}
#endif
