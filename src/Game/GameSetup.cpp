/*
 * $Id: GameSetup.cpp,v 1.9 2002/11/24 22:32:43 southa Exp $
 * $Log: GameSetup.cpp,v $
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
#include "GameDef.h"
#include "GameRouter.h"

#include "mushGL.h"
#include "mushMedia.h"
#include "mushPlatform.h"

GameSetup::GameSetup() :
    m_gameState(kGameStateConfigInit),
    m_windowClicked(false)
{
}

void
GameSetup::Process(void)
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
            throw(LogicFail("Bad value for m_gameState"));
    }
}

void
GameSetup::Display(void)
{
    GLUtils::DisplayPrologue();
    GLUtils::ClearScreen();
    GLUtils::OrthoPrologue();

    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());

    tVal msecNow=gameAppHandler.MillisecondsGet();
    
    GLState::ColourSet(1.0,1.0,1.0,1.0);
    GLUtils orthoGL;

    {
        orthoGL.MoveRelative(0, 0.2);
        GLString glStr(CoreInfo::ApplicationNameGet(), GLFontRef("font-system1", 0.04), 0);
        glStr.Render();
    }

    {
        GLState::ColourSet(0.8,0.8,1.0,1);
        orthoGL.MoveRelative(0, -0.03);
        GLString glStr("Version: "+CoreInfo::PackageVersionGet()+"  ID: "+CoreInfo::PackageIDGet(), GLFontRef("font-system1", 0.018), 0);
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
    U32 webPort=CoreData<GameConfigDef>::Instance().DataGet("configport")->ValueGet().U32Get();
    try
    {
        MediaNetWebServer::Instance().Connect(webPort);
    }
    catch (NetworkFail& e)
    {
        MediaNetLog::Instance().WebLog() << e.what() << endl;
    }
        
    ostringstream configURL;
    configURL << "http://127.0.0.1:" << webPort << "/";
    m_configURL=configURL.str();
    m_gameState=kGameStateConfig;
}    

void
GameSetup::Config(void)
{
    MediaNetWebServer::Instance().Accept();
    MediaNetWebRouter::Instance().ReceiveAll();

    try
    {
        MediaNetServer::Instance().Accept();
        MediaNetRouter::Instance().ReceiveAll(GameRouter::Instance());
    }
    catch (NetworkFail& e)
    {
        MediaNetLog::Instance().NetLog() << "Network exception: " << e.what() << endl;
    }
   
    bool netActive=false;
    GameDef *gameDef = NULL;
    if (CoreData<GameDef>::Instance().DataGetIfExists(gameDef, "client"))
    {
        netActive=true;
        COREASSERT(gameDef != NULL);
        gameDef->Ticker();
    }
    if (CoreData<GameDef>::Instance().DataGetIfExists(gameDef, "server"))
    {
        netActive=true;
        COREASSERT(gameDef != NULL);
        gameDef->Ticker();
    }

    if (netActive)
    {
        if (!MediaNetServer::Instance().IsServing())
        {
            U32 portNum=GameConfig::Instance().ParameterGet("multiport").U32Get();
            
            try
            {
                MediaNetServer::Instance().Connect(portNum);
            }
            catch (NetworkFail& e)
            {
                MediaNetLog::Instance().NetLog() << "Server creation exception: " << e.what();
                PlatformMiscUtils::MinorErrorBox(e.what());
            }
        }
    }

    
    KeyControl();
    GLUtils::PostRedisplay();
    MediaAudio::Instance().Ticker();
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
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());
    if (gameAppHandler.LatchedKeyStateTake(GLKeys::kKeyMouse1))
    {
        if (!MediaNetWebServer::Instance().IsConnected())
        {
            U32 webPort=CoreData<GameConfigDef>::Instance().DataGet("configport")->ValueGet().U32Get();
            try
            {
                MediaNetWebServer::Instance().Connect(webPort);
            }
            catch (NetworkFail& e)
            {
                MediaNetLog::Instance().WebLog() << e.what() << endl;
            }
        }
        PlatformMiscUtils::LaunchURL(m_configURL);
        m_windowClicked=true;
    }
}

void
GameSetup::ScriptFunction(const string& inName) const
{
}

void
GameSetup::SwapIn(void)
{
    GLAppHandler& glAppHandler=dynamic_cast<GLAppHandler &>(CoreAppHandler::Instance());
    glAppHandler.EnterScreen(PlatformVideoUtils::Instance().ModeDefGet(0));
}

void
GameSetup::SwapOut(void)
{
}
