/*
 * $Id: GameTest.h,v 1.2 2002/05/10 16:39:34 southa Exp $
 * $Log: GameTest.h,v $
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
    Val m_playerx;
    Val m_playerxv;
    Val m_playery;
    Val m_playeryv;
    
    Val m_leftlim;
    Val m_rightlim;
};