/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

#include "GLPoint.h"

class GLLine
{
public:
    GLLine(const GLPoint& inStart, const GLPoint& inEnd);
    void CentreGet(GLPoint& outPoint) const;
    void RotateAboutCentre(tVal inAngle);
    const GLPoint& GetStart(void) const;
    const GLPoint& GetEnd(void) const;
    void Render(void) const;

private:
    GLPoint m_start;
    GLPoint m_end;
};
