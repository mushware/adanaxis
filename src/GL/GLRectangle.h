//%includeGuardStart {
#ifndef GLRECTANGLE_H
#define GLRECTANGLE_H
//%includeGuardStart } 5DIpHkNBSwIEKNwYbyTZnA
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLRectangle.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } s7ziow5sNdz02YuA5B5mGQ
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
