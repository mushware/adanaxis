#ifndef GLLINE_H
#define GLLINE_H
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
 * $Id: GLLine.h,v 1.3 2002/08/01 16:47:09 southa Exp $
 * $Log: GLLine.h,v $
 * Revision 1.3  2002/08/01 16:47:09  southa
 * First multi-box collsion checking
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
    bool IsIntersecting(const GLLine& inLine) const;
    
private:
    GLPoint m_start;
    GLPoint m_end;
};
#endif
