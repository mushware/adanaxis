#ifndef GAMEAPPHANDLER_H
#define GAMEAPPHANDLER_H
/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GameAppHandler.h,v 1.14 2002/11/18 11:31:13 southa Exp $
 * $Log: GameAppHandler.h,v $
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

#include "mushCore.h"
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

    void SetupModeEnter(void);
    void GameModeEnter(bool inResume);
    void QuitModeEnter(void);
    void CurrentGameEnd(void);
    
protected:
    virtual void KeyboardSignal(const GLKeyboardSignal& inSignal);
        
    void PrepareNewGame(void);
    
private:
    enum tAppState
    {
        kAppStateInvalid,
        kAppStateStartup,
        kAppStateSetup,
        kAppStateGame,
        kAppStateQuit
    };
    
    GameBase *m_pSetup;
    GameBase *m_pGame;
    GameBase *m_pCurrent;
    tAppState m_appState;
};
#endif
