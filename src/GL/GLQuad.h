#ifndef GLQUAD_H
#define GLQUAD_H
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
 * $Id: GLQuad.h,v 1.4 2002/08/01 16:47:10 southa Exp $
 * $Log: GLQuad.h,v $
 * Revision 1.4  2002/08/01 16:47:10  southa
 * First multi-box collsion checking
 *
 * Revision 1.3  2002/07/23 14:10:46  southa
 * Added GameMotion
 *
 * Revision 1.2  2002/07/18 11:40:34  southa
 * Overplotting and movement
 *
 * Revision 1.1  2002/07/16 17:48:07  southa
 * Collision and optimisation work
 *
 */

#include "mushCore.h"

#include "GLPoint.h"
#include "GLRenderable.h"

class GLRectangle;

class GLQuad : public GLRenderable
{
public:
    GLQuad() {}
    GLQuad(const GLRectangle& inRectangle);
    
    virtual GLQuad *Clone(void) const { return new GLQuad(*this); }
    virtual void Render(void) const;
    
    void CentreGet(GLPoint& outPoint) const;
    void RotateAboutCentre(tVal inAngle);
    const GLPoint& PointGet(U32 inWhich) const;
    void PointSet(U32 inWhich, const GLPoint &inPoint);
    void BoundingRectangleGet(GLRectangle& outRect) const;
    
    const GLQuad& operator+=(const GLPoint& inPoint);

private:
    GLPoint m_points[4];
};
#endif
