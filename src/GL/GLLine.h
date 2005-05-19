//%includeGuardStart {
#ifndef GLLINE_H
#define GLLINE_H
//%includeGuardStart } PpRjgvE3gRYybgD8pFRDxA
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLLine.h
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } jy/iqZu8BrKA7HL/LmRwTg
/*
 * $Id: GLLine.h,v 1.13 2004/01/06 20:46:49 southa Exp $
 * $Log: GLLine.h,v $
 * Revision 1.13  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.12  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.11  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.10  2003/08/21 23:08:23  southa
 * Fixed file headers
 *
 * Revision 1.9  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.8  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
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

#include "mushMushcore.h"

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
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
