/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: GameTest.cpp,v 1.12 2003/01/13 14:32:00 southa Exp $
 * $Log: GameTest.cpp,v $
 * Revision 1.12  2003/01/13 14:32:00  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.11  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.10  2002/12/29 20:59:57  southa
 * More build fixes
 *
 * Revision 1.9  2002/12/20 13:17:43  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.8  2002/10/22 20:42:06  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/27 08:56:26  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.5  2002/07/06 18:04:19  southa
 * More designer work
 *
 * Revision 1.4  2002/06/27 12:36:07  southa
 * Build process fixes
 *
 * Revision 1.3  2002/05/10 22:38:22  southa
 * Checkpoint
 *
 * Revision 1.2  2002/05/10 16:39:34  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/05/10 15:35:27  southa
 * Added Game group
 *
 */

#include "GameTest.h"

#include "GameSTL.h"

#include "Mushcore.h"
#include "mushGL.h"

using namespace Mushware;
using namespace std;

void
GameTest::Process(bool &outDoQuit, bool &outRedraw)
{
    switch (m_state)
    {
        case kInit:
            Init();
            m_state=kRunning;
            break;

        case kRunning:
            Running(outRedraw);
            break;
    }
}

void
GameTest::Display(void)
{
    glDrawBuffer(GL_BACK);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    GLUtils::OrthoPrologue();

    glRasterPos2f(0, 0);

    glBegin(GL_TRIANGLES);
    glColor3f(0.5, 0.5, 0.5);
    glVertex2f(m_playerx-8,m_playery-4);
    glVertex2f(m_playerx, m_playery+4);
    glVertex2f(m_playerx+8, m_playery-4);
    glEnd();
    
    GLUtils::OrthoEpilogue();
    glutSwapBuffers();
}

void
GameTest::Init(void)
{
    cerr << "GameTest inited" << endl;
    m_leftlim=8;
    m_rightlim=640-8;
    m_playerx=(m_leftlim+m_rightlim)/2;
    m_playerxv=1;
    m_playery=8;
    m_playeryv=0;
}

void
GameTest::Running(bool &outRedraw)
{
    m_playerx += m_playerxv;
    m_playery += m_playeryv;
    if (m_playerx > m_rightlim) m_playerxv = -fabs(m_playerxv);
    if (m_playerx < m_leftlim) m_playerxv = fabs(m_playerxv);
    outRedraw=true;
}
