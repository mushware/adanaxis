/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

#include "GameBase.h"

class GameQuit : public GameBase
{
public:
    GameQuit();
    virtual void Process(void);
    virtual void Display(void);
    virtual void ScriptFunction(const string& inName) const;
    virtual void SwapIn(void);
    virtual void SwapOut(void);

protected:
    
private:
    void Init(void);
    void Timing(void);
        
    enum tGameState
    {
        kGameStateInvalid,
        kGameStateInit,
        kGameStateTiming
    };

    enum
    {
        kQuitHangTime=500, // msec to hang around regardless
        kQuitTimeout=5000  // msec to wait for web links
    };

    tGameState m_gameState;
    U32 m_startMsec;
};
