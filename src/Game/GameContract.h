/*
 * $Id: GameContract.h,v 1.1 2002/05/27 12:58:43 southa Exp $
 * $Log: GameContract.h,v $
 * Revision 1.1  2002/05/27 12:58:43  southa
 * GameContract and global configs added
 *
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
    virtual void InitDisplay(void);
    virtual void RunningDisplay(void);

private:
    State m_state;
    GameMap *m_gameMap;
};
