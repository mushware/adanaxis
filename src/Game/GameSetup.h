/*
 * $Id: GameSetup.h,v 1.1 2002/11/15 18:58:34 southa Exp $
 * $Log: GameSetup.h,v $
 * Revision 1.1  2002/11/15 18:58:34  southa
 * Configuration mode
 *
 */

#include "mushCore.h"

#include "GameBase.h"

class GameSetup : public GameBase
{
public:
    GameSetup();
    virtual void Process(void);
    virtual void Display(void);
    virtual void ScriptFunction(const string& inName) const;
    virtual void SwapIn(void);
    virtual void SwapOut(void);

protected:
    void ConfigInit(void);
    void Config(void);
    void KeyControl(void);
    
private:
    enum tGameState
    {
        kGameStateInvalid,
        kGameStateConfigInit,
        kGameStateConfig
    };

    tGameState m_gameState;
    string m_configURL;
    bool m_windowClicked;
};
