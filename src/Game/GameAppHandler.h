//%includeGuardStart {
#ifndef GAMEAPPHANDLER_H
#define GAMEAPPHANDLER_H
//%includeGuardStart } wBmcsG1CoSpxwZO+dBp4YA
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameAppHandler.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 5wVaQrecIxMy9gNkVg+RNw
/*
 * $Id: GameAppHandler.h,v 1.23 2004/01/02 21:13:06 southa Exp $
 * $Log: GameAppHandler.h,v $
 * Revision 1.23  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.22  2003/10/04 15:32:08  southa
 * Module split
 *
 * Revision 1.21  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
 * Revision 1.20  2003/08/21 23:08:34  southa
 * Fixed file headers
 *
 * Revision 1.19  2003/01/11 13:03:12  southa
 * Use Mushcore header
 *
 * Revision 1.18  2002/12/20 13:17:37  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.17  2002/12/05 13:20:10  southa
 * Client link handling
 *
 * Revision 1.16  2002/12/03 20:28:15  southa
 * Network, player and control work
 *
 * Revision 1.15  2002/11/18 18:55:57  southa
 * Game resume and quit
 *
 * Revision 1.14  2002/11/18 11:31:13  southa
 * Return to game mode
 *
 * Revision 1.13  2002/11/17 13:38:30  southa
 * Game selection
 *
 * Revision 1.12  2002/11/16 12:43:21  southa
 * GameApp mode switching
 *
 * Revision 1.11  2002/11/15 18:58:33  southa
 * Configuration mode
 *
 * Revision 1.10  2002/10/22 20:42:02  southa
 * Source conditioning
 *
 * Revision 1.9  2002/08/27 08:56:22  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/07 13:36:48  southa
 * Conditioned source
 *
 * Revision 1.7  2002/07/06 18:04:18  southa
 * More designer work
 *
 * Revision 1.6  2002/06/27 12:36:06  southa
 * Build process fixes
 *
 * Revision 1.5  2002/06/21 18:50:16  southa
 * SDLAppHandler added
 *
 * Revision 1.4  2002/06/20 15:50:30  southa
 * Subclassed GLAppHandler
 *
 * Revision 1.3  2002/05/31 15:18:16  southa
 * Keyboard reading
 *
 * Revision 1.2  2002/05/10 16:39:34  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/05/10 15:35:27  southa
 * Added Game group
 *
 */

#include "mushMushcore.h"
#include "mushGL.h"

class GameBase;

class GameAppHandler : public SDLAppHandler
{
public:
    GameAppHandler();
    virtual ~GameAppHandler();
    virtual void Initialise(void);
    virtual void Display(void);
    virtual void Idle(void);

    virtual void SetupModeEnter(void);
    virtual void GameModeEnter(bool inResume) = 0;
    virtual void QuitModeEnter(void);
    virtual void CurrentGameEnd(void) = 0;

    bool ServerPresent(void) const { return m_gameType == kGameTypeServer; }
    bool NetworkActive(void) const { return m_gameType == kGameTypeServer || m_gameType == kGameTypeClient; }
    bool MultiplayerIs(void) const { return m_gameType == kGameTypeServer || m_gameType == kGameTypeClient; }
    bool GameRunningIs(void) const { return m_appState == kAppStateGame; }
    
protected:
    virtual void KeyboardSignal(const GLKeyboardSignal& inSignal);
    virtual void PrepareNewGame(void) = 0;
    
    bool StateGameIs(void) const { return (m_appState != kAppStateGame); }
    void StateGameSet(void) { m_appState=kAppStateGame; }
    void CurrentSwapOut(void);
    void CurrentSwapIn(GameBase *inpGame);
    void GameTypeDetermine(void); // Not sure about exporting this
        
private:
    enum tAppState
    {
        kAppStateInvalid,
        kAppStateStartup,
        kAppStateSetup,
        kAppStateGame,
        kAppStateQuit
    };

    enum tGameType
    {
        kGameTypeInvalid,
        kGameTypeServer,
        kGameTypeClient,
        kGameTypeSingle
    };
        
    GameBase *m_pSetup;
    GameBase *m_pCurrent;
    tAppState m_appState;
    tGameType m_gameType;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
