/*
 * $Id: GameTest.cpp,v 1.2 2002/05/10 16:39:34 southa Exp $
 * $Log: GameTest.cpp,v $
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