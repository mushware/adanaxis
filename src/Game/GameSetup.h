/*
 * $Id$
 * $Log$
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
