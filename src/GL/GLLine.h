#ifndef GLLINE_H
#define GLLINE_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GLLine.h,v 1.7 2002/10/22 20:42:00 southa Exp $
 * $Log: GLLine.h,v $
 * Revision 1.7  2002/10/22 20:42:00  southa
 * Source conditioning
 *
 * Revision 1.6  2002/10/10 13:51:16  southa
 * Speed fixes and various others
 *
 * Revision 1.5  2002/08/27 08:56:19  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:47  southa
 * Conditioned source
 *
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
    virtual ~GLLine() {}
    virtual GLLine *Clone(void) const { return new GLLine(*this); }
    virtual void Render(void) const;

    void CentreGet(GLPoint& outPoint) const;
    void RotateAboutCentre(Mushware::tVal inAngle);
    const GLPoint& GetStart(void) const;
    const GLPoint& GetEnd(void) const;
    bool IsIntersecting(const GLLine& inLine) const;
    
private:
    GLPoint m_start;
    GLPoint m_end;
};
#endif
