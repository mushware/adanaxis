/*
 * $Id: GLQuad.h,v 1.2 2002/07/18 11:40:34 southa Exp $
 * $Log: GLQuad.h,v $
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
    GLQuad(const GLRectangle& inRectangle);
    
    virtual GLQuad *Clone(void) const { return new GLQuad(*this); }
    virtual void Render(void) const;
    
    void CentreGet(GLPoint& outPoint) const;
    void RotateAboutCentre(tVal inAngle);
    const GLPoint& GetPoint(U32 inWhich) const;

    const GLQuad& operator+=(const GLPoint& inPoint);

private:
    GLPoint m_points[4];
};
