/*
 * $Id: GameTest.cpp,v 1.1 2002/05/10 15:35:27 southa Exp $
 * $Log: GameTest.cpp,v $
 * Revision 1.1  2002/05/10 15:35:27  southa
 * Added Game group
 *
 */

#include "GameTest.h"
#include "mushCore.h"
// #include "mushGL.h"

void
GameTest::Process(bool &outDoQuit, bool &outRedraw)
{
    switch (m_state)
    {
        case kInit:
            Init();
            m_state=kRunning;
            break;
    }
}

void
GameTest::Init(void)
{
    cerr << "GameTest inited" << endl;
}
