/*
 * $Id: GameAppHandler.h,v 1.1 2002/05/10 15:35:27 southa Exp $
 * $Log: GameAppHandler.h,v $
 * Revision 1.1  2002/05/10 15:35:27  southa
 * Added Game group
 *
 */

#include "mushCore.h"
#include "mushGL.h"

class GameBase;

class GameAppHandler : public GLAppHandler
{
public:
    GameAppHandler(): m_pGame(NULL) {}
    virtual void Initialise(void);
    virtual void Display(void);
    virtual void Idle(bool& outQuit, int& outUSleepFor);

protected:
private:
    static void IdleHandler(void);
    static void DisplayHandler(void) {Instance().Display();}
    GameBase *m_pGame;
};
