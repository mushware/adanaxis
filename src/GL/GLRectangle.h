//%includeGuardStart {
#ifndef GLRECTANGLE_H
#define GLRECTANGLE_H
//%includeGuardStart } 5DIpHkNBSwIEKNwYbyTZnA
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLRectangle.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } nvrbZFDV7YheQ90YFwIWJA
/*
 * $Id: GLRectangle.h,v 1.14 2003/08/21 23:08:26 southa Exp $
 * $Log: GLRectangle.h,v $
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
 * Added GameMotion
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

#include "Mushcore.h"

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
