/*
 * $Id: GameTest.h,v 1.1 2002/05/10 15:35:27 southa Exp $
 * $Log: GameTest.h,v $
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
    void Process(bool& outDoQuit, bool& outRedraw);

protected:
    enum State
    {
        kInit,
        kRunning
    };

    void Init(void);

private:
    State m_state;
};