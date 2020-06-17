//%includeGuardStart {
#ifndef INFERNALMAPAREA_H
#define INFERNALMAPAREA_H
//%includeGuardStart } mdIepkw3yvpB/bBMHiQxKQ
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalMapArea.h
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
//%Header } MgKT1FsXAC6UWJ6knt4bBw
/*
 * $Id: InfernalMapArea.h,v 1.6 2006/06/01 15:39:03 southa Exp $
 * $Log: InfernalMapArea.h,v $
 * Revision 1.6  2006/06/01 15:39:03  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/05/19 13:02:05  southa
 * Mac release work
 *
 * Revision 1.4  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.3  2004/01/02 21:13:08  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/04 12:44:35  southa
 * File renaming
 *
 * Revision 1.1  2003/10/04 12:23:06  southa
 * File renaming
 *
 * Revision 1.10  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.9  2003/08/21 23:08:48  southa
 * Fixed file headers
 *
 * Revision 1.8  2003/01/11 17:07:52  southa
 * Mushcore library separation
 *
 * Revision 1.7  2003/01/11 13:03:13  southa
 * Use Mushcore header
 *
 * Revision 1.6  2002/12/20 13:17:40  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.4  2002/10/10 13:51:17  southa
 * Speed fixes and various others
 *
 * Revision 1.3  2002/08/27 08:56:24  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.1  2002/07/16 17:48:08  southa
 * Collision and optimisation work
 *
 */

#include "mushMushcore.h"
#include "mushGL.h"

class InfernalMapArea
{
public:
    void RectangleAdd(const GLRectangle& inRectangle);
    void CircleAdd(const GLPoint& inPoint, Mushware::tVal inRadius);
    bool IsWithin(const GLPoint& inPoint) const;
    const GLPoint MinPointGet(void) const;
    const GLPoint MaxPointGet(void) const;
    const GLRectangle BoundingBoxGet(void) const;
    bool IsEmpty(void) const;
    
private:
    std::vector<GLRectangle> m_rectangles;
    std::vector<Mushware::tVal> m_radiiSquared;
    std::vector<GLPoint> m_points;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
