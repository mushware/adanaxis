/*
 * $Id$
 * $Log$
 */

#include "mushCore.hp"

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