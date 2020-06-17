//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLLine.cpp
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
//%Header } 60Jvq+Fc52NEhtKLnKuLag
/*
 * $Id: GLLine.cpp,v 1.16 2006/06/01 15:38:51 southa Exp $
 * $Log: GLLine.cpp,v $
 * Revision 1.16  2006/06/01 15:38:51  southa
 * DrawArray verification and fixes
 *
 * Revision 1.15  2005/05/19 13:01:59  southa
 * Mac release work
 *
 * Revision 1.14  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.13  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.12  2003/08/21 23:08:23  southa
 * Fixed file headers
 *
 * Revision 1.11  2003/01/13 14:31:54  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.10  2002/12/29 20:59:52  southa
 * More build fixes
 *
 * Revision 1.9  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.8  2002/10/22 20:42:00  southa
 * Source conditioning
 *
 * Revision 1.7  2002/10/17 15:50:58  southa
 * Config saving, pause and quit
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

#include "GLLine.h"

#include "GLStandard.h"
#include "GLState.h"
#include "GLUtils.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

GLLine::GLLine(const GLPoint& inStart, const GLPoint& inEnd):
    m_start(inStart),
    m_end(inEnd)
{
}

void
GLLine::CentreGet(GLPoint& outPoint) const
{
    outPoint=(m_start+m_end)/2;
}

void
GLLine::RotateAboutCentre(tVal inAngle)
{
    GLPoint centre;
    CentreGet(centre);

    m_start.RotateAboutZ(centre, inAngle);
    m_end.RotateAboutZ(centre, inAngle);    
}

const GLPoint&
GLLine::GetStart(void) const
{
    return m_start;
}

const GLPoint&
GLLine::GetEnd(void) const
{
    return m_end;
}

bool
GLLine::IsIntersecting(const GLLine& inLine) const
{
    // This function has been rearranged to avoid a MacOS X compiler bug
    GLPoint a(m_start);
    GLPoint b(m_end);
    GLPoint c(inLine.GetStart());
    GLPoint d(inLine.GetEnd());

    b-=a;
    d-=c;
    
    tVal f = b.x*d.y - b.y*d.x;

    tVal m = d.y*(c.x-a.x)+d.x*(a.y-c.y);
    tVal n = b.y*(c.x-a.x)+b.x*(a.y-c.y);
    
    bool isIntersecting;
    if (f < 0)
    {
        isIntersecting = (m<=0 && m>f && n<=0 && n>f);
    }
    else
    {
        isIntersecting = (m>=0 && m<f && n>=0 && n<f);
    }
    if (isIntersecting)
    {
        return true;
    }
    return false;
}

void
GLLine::Render(void) const
{
    GLState::TextureDisable();
    glBegin(GL_LINES);
    GLUtils::Vertex(m_start.x, m_start.y);
    GLUtils::Vertex(m_end.x, m_end.y);
    glEnd();
}
