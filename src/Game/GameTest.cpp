/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GameTest.cpp,v 1.7 2002/08/27 08:56:26 southa Exp $
 * $Log: GameTest.cpp,v $
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
#include "mushCore.h"
#include "mushGL.h"

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
