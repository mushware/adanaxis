/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GameSetup.cpp,v 1.32 2003/02/06 18:55:27 southa Exp $
 * $Log: GameSetup.cpp,v $
 * Revision 1.32  2003/02/06 18:55:27  southa
 * Linux build fixes
 *
 * Revision 1.31  2003/01/20 10:45:27  southa
 * Singleton tidying
 *
 * Revision 1.30  2003/01/14 17:38:20  southa
 * Mustl web configuration
 *
 * Revision 1.29  2003/01/13 14:32:00  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.28  2003/01/12 17:32:56  southa
 * Mushcore work
 *
 * Revision 1.27  2003/01/11 17:44:27  southa
 * Mushcore fixes
 *
 * Revision 1.26  2003/01/09 14:57:03  southa
 * Created Mushcore
 *
 * Revision 1.25  2002/12/29 20:59:57  southa
 * More build fixes
 *
 * Revision 1.24  2002/12/20 13:17:42  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.23  2002/12/12 18:38:58  southa
 * Mustl separation
 *
 * Revision 1.22  2002/12/12 14:00:40  southa
 * Created Mustl
 *
 * Revision 1.21  2002/12/05 23:52:52  southa
 * Network management and status
 *
 * Revision 1.20  2002/12/05 13:20:12  southa
 * Client link handling
 *
 * Revision 1.19  2002/12/04 12:54:41  southa
 * Network control work
 *
 * Revision 1.18  2002/12/03 20:28:17  southa
 * Network, player and control work
 *
 * Revision 1.17  2002/11/28 18:05:36  southa
 * Print link ages
 *
 * Revision 1.16  2002/11/28 16:19:25  southa
 * Fix delete object messaging
 *
 * Revision 1.15  2002/11/28 15:51:21  southa
 * Kill image defs as well
 *
 * Revision 1.14  2002/11/28 11:10:29  southa
 * Client and server delete messages
 *
 * Revision 1.13  2002/11/27 20:17:26  southa
 * Basic network cleardown
 *
 * Revision 1.12  2002/11/27 17:44:20  southa
 * Network fixes
 *
 * Revision 1.11  2002/11/27 13:23:26  southa
 * Server and client data exchange
 *
 * Revision 1.10  2002/11/25 12:06:18  southa
 * Received net message routing
 *
 * Revision 1.9  2002/11/24 22:32:43  southa
 * Host and join displays
 *
 * Revision 1.8  2002/11/24 00:29:08  southa
 * Serve web pages to local addresses only
 *
 * Revision 1.7  2002/11/23 17:23:44  southa
 * Sleep in setup
 *
 * Revision 1.6  2002/11/22 15:33:59  southa
 * More network logging
 *
 * Revision 1.5  2002/11/22 11:42:06  southa
 * Added developer controls
 *
 * Revision 1.4  2002/11/21 18:06:17  southa
 * Non-blocking network connection
 *
 * Revision 1.3  2002/11/20 22:35:26  southa
 * Multiplayer setup
 *
 * Revision 1.2  2002/11/16 12:43:23  southa
 * GameApp mode switching
 *
 * Revision 1.1  2002/11/15 18:58:34  southa
 * Configuration mode
 *
 */

#include "GameSetup.h"

#include "GameAppHandler.h"
#include "GameConfig.h"
#include "GameConfigDef.h"
#include "GameDefClient.h"
#include "GameDefServer.h"
#include "GameNetUtils.h"
#include "GameRouter.h"
#include "GameSTL.h"

#include "mushGL.h"
#include "mushMedia.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

GameSetup::GameSetup() :
    m_gameState(kGameStateConfigInit),
    m_lastTickerMsec(0),
    m_windowClicked(false)
{
}

void
GameSetup::Process(GameAppHandler& inAppHandler)
{
    switch (m_gameState)
    {
        case kGameStateConfigInit:
            ConfigInit();
            m_gameState=kGameStateConfig;
            break;

        case kGameStateConfig:
            Config();
            break;

        default:
            throw(MushcoreLogicFail("Bad value for m_gameState"));
    }
}

void
GameSetup::Display(GameAppHandler& inAppHandler)
{
    GLUtils::DisplayPrologue();
    GLUtils::ClearScreen();
    GLUtils::OrthoPrologue();

    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Sgl());

    m_currentMsec=gameAppHandler.MillisecondsGet();

    tVal msecNow=m_currentMsec;
    
    GLState::ColourSet(1.0,1.0,1.0,1.0);
    GLUtils orthoGL;

    {
        orthoGL.MoveRelative(0, 0.2);
        GLString glStr(MushcoreInfo::Sgl().ApplicationNameGet(), GLFontRef("font-system1", 0.04), 0);
        glStr.Render();
    }

    {
        GLState::ColourSet(0.8,0.8,1.0,1);
        orthoGL.MoveRelative(0, -0.03);
        GLString glStr("Version: "+MushcoreInfo::Sgl().PackageVersionGet()+"  ID: "+MushcoreInfo::Sgl().PackageIDGet(), GLFontRef("font-system1", 0.018), 0);
        glStr.Render();
    }
    
    
    {
        GLState::ColourSet(1.0,1.0,1.0,1.0);
        orthoGL.MoveRelative(0, -0.12);
        GLString glStr("Configuration mode", GLFontRef("font-system1", 0.03), 0);
        glStr.Render();
    }

    {
        GLState::ColourSet(0.8,0.8,1.0,1.0);
        GLString glStr("Please click this window or view", GLFontRef("font-system1", 0.02), 0);
        orthoGL.MoveRelative(0, -0.06);
        glStr.Render();
        
        GLState::ColourSet(1.0,1.0,1.0,0.5+0.25*sin(msecNow/300));
        glStr.TextSet(m_configURL);
        orthoGL.MoveRelative(0, -0.02);
        glStr.Render();
    
        GLState::ColourSet(0.8,0.8,1.0,1.0);
        glStr.TextSet("in your browser to begin");
        orthoGL.MoveRelative(0, -0.02);
        glStr.Render();
    }

    if (!m_windowClicked)
    {
        GLState::ColourSet(1.0,1.0,1.0,0.8);
        GLString glStr("Click this window to begin", GLFontRef("font-system1", 0.03), 0);
        orthoGL.MoveRelative(0.01*sin(msecNow/200), -0.15+0.01*cos(msecNow/401));
GLUtils::RotateAboutZ(5*sin(msecNow/151));
        glStr.Render();
    }
    GLUtils::OrthoEpilogue();
    GLUtils::DisplayEpilogue();
}

void
GameSetup::ConfigInit(void)
{
    U32 webPort=MushcoreData<GameConfigDef>::Sgl().Get("configport")->ValueGet().U32Get();
    try
    {
        MustlWebServer::Sgl().PermissionFunctionSet(MustlPermissionFunction);
        MustlWebServer::Sgl().Connect(webPort);
    }
    catch (MushcoreNonFatalFail& e)
    {
        MustlLog::Sgl().WebLog() << e.what() << endl;
        PlatformMiscUtils::MinorErrorBox(e.what());
    }
        
    ostringstream configURL;
    configURL << "http://127.0.0.1:" << webPort << "/";
    m_configURL=configURL.str();
    m_gameState=kGameStateConfig;
}    

void
GameSetup::Config(void)
{
    m_currentMsec=dynamic_cast<GLAppHandler &>(MushcoreAppHandler::Sgl()).MillisecondsGet();
    
    GameNetUtils::WebReceive();
    GameNetUtils::NetReceive();


    if (m_currentMsec > m_lastTickerMsec + kTickerMsec)
    {
        m_lastTickerMsec = m_currentMsec;
        GameNetUtils::NetTicker();
    }
    
    KeyControl();
    GLUtils::PostRedisplay();
    MediaAudio::Sgl().Ticker();
    
    if (m_windowClicked)
    {
        PlatformMiscUtils::SleepMsec(kSlowSleepMsec);
    }
    else
    {
        // Running window animation
        PlatformMiscUtils::SleepMsec(kFastSleepMsec);
    }
}


void
GameSetup::KeyControl(void)
{
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Sgl());
    if (gameAppHandler.LatchedKeyStateTake(GLKeys::kKeyMouse1))
    {
        if (!MustlWebServer::Sgl().IsConnected())
        {
            U32 webPort=MushcoreData<GameConfigDef>::Sgl().Get("configport")->ValueGet().U32Get();
            try
            {
                MustlWebServer::Sgl().Connect(webPort);
            }
            catch (MushcoreNonFatalFail& e)
            {
                MustlLog::Sgl().WebLog() << e.what() << endl;
            }
        }
        try
        {
            PlatformMiscUtils::LaunchURL(m_configURL);
        }
        catch (MushcoreNonFatalFail& e)
        {
            cerr << "Exception: " << e.what() << endl;
            cerr << "Please open the URL manually if necessary." << endl;
        }
        m_windowClicked=true;
    }
}

void
GameSetup::ScriptFunction(const string& inName, GameAppHandler& inAppHandler) const
{
}

void
GameSetup::SwapIn(GameAppHandler& inAppHandler)
{
    GLAppHandler& glAppHandler=dynamic_cast<GLAppHandler &>(MushcoreAppHandler::Sgl());
    glAppHandler.EnterScreen(PlatformVideoUtils::Sgl().ModeDefGet(0));
}

void
GameSetup::SwapOut(GameAppHandler& inAppHandler)
{
}

bool
GameSetup::MustlPermissionFunction(const std::string& inAddress)
{
    return PlatformMiscUtils::PermissionBox("A connection is being attempted from address "+inAddress+".  Would you like to allow this?", false);
}
