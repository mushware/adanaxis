#ifndef GLQUAD_H
#define GLQUAD_H
/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: GLQuad.h,v 1.9 2003/01/11 13:03:11 southa Exp $
 * $Log: GLQuad.h,v $
 * Revision 1.9  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.8  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/27 08:56:19  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/07 13:36:47  southa
 * Conditioned source
 *
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

#include "Mushcore.h"

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
    void RotateAboutCentre(Mushware::tVal inAngle);
    const GLPoint& PointGet(Mushware::U32 inWhich) const;
    void PointSet(Mushware::U32 inWhich, const GLPoint &inPoint);
    void BoundingRectangleGet(GLRectangle& outRect) const;
    
    const GLQuad& operator+=(const GLPoint& inPoint);

private:
    GLPoint m_points[4];
};
#endif
