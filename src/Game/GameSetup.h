#ifndef GAMESETUP_H
#define GAMESETUP_H
/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: GameSetup.h,v 1.11 2003/03/10 21:57:11 southa Exp $
 * $Log: GameSetup.h,v $
 * Revision 1.11  2003/03/10 21:57:11  southa
 * ic2 revisions
 *
 * Revision 1.10  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.9  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.8  2002/12/20 13:17:42  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/12/05 23:52:52  southa
 * Network management and status
 *
 * Revision 1.6  2002/12/03 20:28:17  southa
 * Network, player and control work
 *
 * Revision 1.5  2002/11/28 18:05:36  southa
 * Print link ages
 *
 * Revision 1.4  2002/11/28 15:51:21  southa
 * Kill image defs as well
 *
 * Revision 1.3  2002/11/23 17:23:44  southa
 * Sleep in setup
 *
 * Revision 1.2  2002/11/16 12:43:23  southa
 * GameApp mode switching
 *
 * Revision 1.1  2002/11/15 18:58:34  southa
 * Configuration mode
 *
 */

#include "Mushcore.h"

#include "GameBase.h"

class GameSetup : public GameBase
{
public:
    GameSetup();
    virtual void Process(GameAppHandler& inAppHandler);
    virtual void Display(GameAppHandler& inAppHandler);
    virtual void ScriptFunction(const std::string& inName, GameAppHandler& inAppHandler) const;
    virtual void SwapIn(GameAppHandler& inAppHandler);
    virtual void SwapOut(GameAppHandler& inAppHandler);

protected:
    void ConfigInit(void);
    void Config(void);
    void Ticker(void);
    void KeyControl(void);

    static bool MustlPermissionFunction(const std::string& inAddress);
    
private:
    enum
    {
        kSlowSleepMsec=10,
        kFastSleepMsec=1,
        kTickerMsec=100
    };
    enum tGameState
    {
        kGameStateInvalid,
        kGameStateConfigInit,
        kGameStateConfig
    };

    tGameState m_gameState;
    std::string m_configURL;
    Mushware::U32 m_currentMsec;
    Mushware::U32 m_lastTickerMsec;
    bool m_windowClicked;
};
#endif
