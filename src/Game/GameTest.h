#ifndef GAMETEST_H
#define GAMETEST_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GameTest.h,v 1.9 2002/10/22 20:42:06 southa Exp $
 * $Log: GameTest.h,v $
 * Revision 1.9  2002/10/22 20:42:06  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/27 08:56:26  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.6  2002/07/06 18:04:19  southa
 * More designer work
 *
 * Revision 1.5  2002/06/27 12:36:07  southa
 * Build process fixes
 *
 * Revision 1.4  2002/05/24 16:23:07  southa
 * Config and typenames
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

#include "mushCore.h"

#include "GameBase.h"

class GameTest: public GameBase
{
public:
    GameTest(): m_state(kInit) {}
    virtual ~GameTest() {}
    virtual void Process(bool& outDoQuit, bool& outRedraw);
    virtual void Display(void);

protected:
    enum State
    {
        kInit,
        kRunning
    };

    virtual void Init(void);
    virtual void Running(bool &outRedraw);

private:
    State m_state;
    Mushware::tVal m_playerx;
    Mushware::tVal m_playerxv;
    Mushware::tVal m_playery;
    Mushware::tVal m_playeryv;
    
    Mushware::tVal m_leftlim;
    Mushware::tVal m_rightlim;
};
#endif
