/*
 * $Id: GameSetup.cpp,v 1.16 2002/11/28 16:19:25 southa Exp $
 * $Log: GameSetup.cpp,v $
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
#include "GameRouter.h"

#include "mushGL.h"
#include "mushMedia.h"
#include "mushPlatform.h"

GameSetup::GameSetup() :
    m_gameState(kGameStateConfigInit),
    m_lastTickerMsec(0),
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

    m_currentMsec=gameAppHandler.MillisecondsGet();

    tVal msecNow=m_currentMsec;
    
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
    m_currentMsec=dynamic_cast<GLAppHandler &>(CoreAppHandler::Instance()).MillisecondsGet();
    
    try
    {
        MediaNetWebServer::Instance().Accept();
        MediaNetWebRouter::Instance().ReceiveAll();

        MediaNetServer::Instance().Accept();
        MediaNetRouter::Instance().ReceiveAll(GameRouter::Instance());
    }
    catch (NetworkFail& e)
    {
        MediaNetLog::Instance().NetLog() << "Network exception: " << e.what() << endl;
    }

    if (m_currentMsec > m_lastTickerMsec + kTickerMsec)
    {
        m_lastTickerMsec = m_currentMsec;
        Ticker();
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
GameSetup::Ticker(void)
{
    {
        CoreData<GameDefClient>::tMapIterator endValue = CoreData<GameDefClient>::Instance().End();
        CoreData<GameDefClient>::tMapIterator killValue = CoreData<GameDefClient>::Instance().End();
    
        for (CoreData<GameDefClient>::tMapIterator p=CoreData<GameDefClient>::Instance().Begin(); p != endValue; ++p)
        {
            if (p->second->IsImage())
            {
                // Expire images after a time limit
                if (m_currentMsec > p->second->CreationMsecGet() + kImageLifetimeMsec)
                {
                    p->second->Kill();
                }
            }
            else
            {
                p->second->Ticker();
            }
            if (p->second->IsDead())
            {
                killValue = p;
            }
        }
        if (killValue != CoreData<GameDefClient>::Instance().End())
        {
            CoreData<GameDefClient>::Instance().DataDelete(killValue);
        }
    }


    bool serverNeeded=false;
    {
        CoreData<GameDefServer>::tMapIterator endValue = CoreData<GameDefServer>::Instance().End();
        CoreData<GameDefServer>::tMapIterator killValue = CoreData<GameDefServer>::Instance().End();

        for (CoreData<GameDefServer>::tMapIterator p = CoreData<GameDefServer>::Instance().Begin(); p != endValue; ++p)
        {
            if (p->second->IsImage())
            {
                // Expire images after a time limit
                if (m_currentMsec > p->second->CreationMsecGet() + kImageLifetimeMsec)
                {
                    p->second->Kill();
                }
            }
            else
            {
                p->second->Ticker();
                serverNeeded=true;
            }
            if (p->second->IsDead())
            {
                killValue = p;
            }
        }
        if (killValue != CoreData<GameDefServer>::Instance().End())
        {
            CoreData<GameDefServer>::Instance().DataDelete(killValue);
        }
    }
    
    if (serverNeeded)
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
                static U32 failedPortNum=65536;
                if (portNum != failedPortNum)
                {
                    MediaNetLog::Instance().NetLog() << "Server creation exception: " << e.what() << endl;
                    PlatformMiscUtils::MinorErrorBox(e.what());
                    failedPortNum=portNum;
                }
            }
        }
    }
    else
    {
        if (MediaNetServer::Instance().IsServing())
        {
            MediaNetServer::Instance().Disconnect();
        }
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
