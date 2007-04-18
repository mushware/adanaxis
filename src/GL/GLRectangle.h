//%includeGuardStart {
#ifndef GLRECTANGLE_H
#define GLRECTANGLE_H
//%includeGuardStart } 5DIpHkNBSwIEKNwYbyTZnA
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLRectangle.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } oySi9yzy17577G34Ae5mpg
/*
 * $Id: GLRectangle.h,v 1.20 2006/06/01 15:38:52 southa Exp $
 * $Log: GLRectangle.h,v $
 * Revision 1.20  2006/06/01 15:38:52  southa
 * DrawArray verification and fixes
 *
 * Revision 1.19  2005/05/19 13:01:59  southa
 * Mac release work
 *
 * Revision 1.18  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.17  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.16  2003/10/04 12:22:58  southa
 * File renaming
 *
 * Revision 1.15  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.14  2003/08/21 23:08:26  southa
 * Fixed file headers
 *
 * Revision 1.13  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.12  2003/01/09 14:56:58  southa
 * Created Mushcore
 *
 * Revision 1.11  2002/12/29 20:30:52  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.10  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.9  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/27 08:56:19  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.6  2002/08/01 16:47:10  southa
 * First multi-box collsion checking
 *
 * Revision 1.5  2002/07/23 14:10:46  southa
 * Added InfernalMotion
 *
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

#include "mushMushcore.h"

#include "GLPoint.h"
#include "GLRenderable.h"

class GLLine;

class GLRectangle : public GLRenderable
{
public:
    GLRectangle(Mushware::tVal inMinX=0, Mushware::tVal inMinY=0, Mushware::tVal inMaxX=0, Mushware::tVal inMaxY=0);
    GLRectangle(const GLPoint& inMin, const GLPoint& inMax);

    virtual GLRectangle *Clone(void) const { return new GLRectangle(*this); }
    virtual void Render(void) const;

    void Clip(const GLRectangle& inClip);
    void ConstrainPoint(GLPoint& ioPoint) const;
    bool IsWithin(const GLPoint& inPoint) const;
    bool IsIntersecting(const GLLine& inLine) const;
    Mushware::tVal XSize(void) const;
    Mushware::tVal YSize(void) const;
    GLPoint Size(void) const;
    GLPoint MinPoint(void) const { return GLPoint(xmin, ymin); }
    void FixUp(void);
    void MakeInteger(void);
    void Expand(Mushware::tVal inExpansion);
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(MushcoreXML& inXML);

    const GLRectangle& operator+=(const GLPoint& inPoint);
    
    Mushware::tVal xmin;
    Mushware::tVal ymin;
    Mushware::tVal xmax;
    Mushware::tVal ymax;
};

inline std::ostream& operator<<(std::ostream &s, const GLRectangle& inRect)
{
    inRect.Pickle(s);
    return s;
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
