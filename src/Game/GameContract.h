/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

#include "GameBase.h"

class GameMap;

class GameContract: public GameBase
{
public:
    GameContract();
    virtual ~GameContract();
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
    GameMap *m_gameMap;
};
