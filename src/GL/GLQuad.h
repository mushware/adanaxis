/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

#include "GLPoint.h"

class GLRectangle;

class GLQuad
{
public:
    GLQuad(const GLRectangle& inRectangle);
    void CentreGet(GLPoint& outPoint) const;
    void RotateAboutCentre(tVal inAngle);
    const GLPoint& GetPoint(U32 inWhich) const;
    void Render(void) const;

private:
    GLPoint m_points[4];
};
