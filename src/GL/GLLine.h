/*
 * $Id: GLLine.h,v 1.1 2002/07/16 17:48:07 southa Exp $
 * $Log: GLLine.h,v $
 * Revision 1.1  2002/07/16 17:48:07  southa
 * Collision and optimisation work
 *
 */

#include "mushCore.h"

#include "GLPoint.h"
#include "GLRenderable.h"

class GLLine : public GLRenderable
{
public:
    GLLine(const GLPoint& inStart, const GLPoint& inEnd);

    virtual GLLine *Clone(void) const { return new GLLine(*this); }
    virtual void Render(void) const;

    void CentreGet(GLPoint& outPoint) const;
    void RotateAboutCentre(tVal inAngle);
    const GLPoint& GetStart(void) const;
    const GLPoint& GetEnd(void) const;

private:
    GLPoint m_start;
    GLPoint m_end;
};
