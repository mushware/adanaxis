/*
 * $Id$
 * $Log$
 */

#include "GameTest.h"
#include "mushCore.hp"
// #include "mushGL.hp"

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
