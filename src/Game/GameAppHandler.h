/*
 * $Id$
 * $Log$
 */

#include "mushCore.hp"
#include "mushGL.hp"

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
