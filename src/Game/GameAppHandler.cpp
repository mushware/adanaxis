/*
 * $Id: GameAppHandler.cpp,v 1.16 2002/06/21 18:50:16 southa Exp $
 * $Log: GameAppHandler.cpp,v $
 * Revision 1.16  2002/06/21 18:50:16  southa
 * SDLAppHandler added
 *
 * Revision 1.15  2002/06/20 15:50:30  southa
 * Subclassed GLAppHandler
 *
 * Revision 1.14  2002/06/20 11:06:14  southa
 * Updated for cygwin
 *
 * Revision 1.13  2002/06/13 15:15:55  southa
 * New directory structure, FPS printing, load command
 *
 * Revision 1.12  2002/06/10 15:16:59  southa
 * Integration of MP3 player
 *
 * Revision 1.11  2002/06/04 20:27:35  southa
 * Pickles for game traits and graphics.  Removed mac libraries from archive.
 *
 * Revision 1.10  2002/06/02 16:41:18  southa
 * Rotated sprite plotting
 *
 * Revision 1.9  2002/05/31 15:18:16  southa
 * Keyboard reading
 *
 * Revision 1.8  2002/05/30 16:21:53  southa
 * Pickleable GameContract
 *
 * Revision 1.7  2002/05/27 12:58:43  southa
 * GameContract and global configs added
 *
 * Revision 1.6  2002/05/26 16:08:48  southa
 * CoreXML loader
 *
 * Revision 1.5  2002/05/25 17:16:14  southa
 * CoreXML implementation
 *
 * Revision 1.4  2002/05/24 16:23:07  southa
 * Config and typenames
 *
 * Revision 1.3  2002/05/10 22:38:22  southa
 * Checkpoint
 *
 * Revision 1.2  2002/05/10 16:39:34  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/05/10 15:35:27  southa
 * Added Game group
 *
 */

#include "GameAppHandler.h"

#include "mushCore.h"
#include "mushGL.h"

#include "GameContract.h"
#include "GameGlobalConfig.h"
#include "GameFloorMap.h"
#include "GameData.h"
#include "mushMedia.h"

void
GameAppHandler::Initialise(void)
{
    CoreEnv::Instance().PushConfig(GameGlobalConfig::Instance());
    string appPath(CoreGlobalConfig::Instance().Get("APPLPATH").StringGet());
    GameGlobalConfig::Instance().Set("MAPPATH", appPath+"/spaces");
    GameGlobalConfig::Instance().Set("IMAGEPATH", appPath+"/pixels");
    GameGlobalConfig::Instance().Set("CONTRACTPATH", appPath+"/pixels");
    try
    {
        MediaAudio::Instance().PlayMusic(CoreGlobalConfig::Instance().Get("APPLPATH").StringGet()+"/waves/loop_test.ogg");
    }
    catch (DeviceFail& e)
    {
        cerr << "Audio failed : " << e << endl;
    }
    // CoreApp::Instance().Process("loadcontract('game1',$MAPPATH+'/Contract.xml')");

    m_pGame=GameData::Instance().ContractGet("contract1");
    m_pGame->ScriptFunction("load");
    
    EnterScreen(kWindow);

    GLUtils::CheckGLError();
}

void
GameAppHandler::Display(void)
{
    COREASSERT(m_pGame != NULL);
    m_pGame->Display();
}

void
GameAppHandler::Idle(void)
{
    COREASSERT(m_pGame != NULL);
    try
    {
        m_pGame->Process();
    }
    catch (exception& e)
    {
        cerr << "In idle handler: " << e.what() << endl;
        std::exit(1);
    }
}
