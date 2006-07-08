//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameSetup.cpp
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } jvWsLpd9yiZoqGOz/5hv2w
/*
 * $Id: GameSetup.cpp,v 1.49 2006/06/01 15:38:59 southa Exp $
 * $Log: GameSetup.cpp,v $
 * Revision 1.49  2006/06/01 15:38:59  southa
 * DrawArray verification and fixes
 *
 * Revision 1.48  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.47  2005/06/20 14:30:34  southa
 * Adanaxis work
 *
 * Revision 1.46  2005/06/16 17:25:38  southa
 * Client/server work
 *
 * Revision 1.45  2005/05/19 13:02:03  southa
 * Mac release work
 *
 * Revision 1.44  2005/04/19 23:25:39  southa
 * Mode switching and recognition
 *
 * Revision 1.43  2005/03/13 00:34:46  southa
 * Build fixes, key support and stereo
 *
 * Revision 1.42  2005/02/10 12:33:59  southa
 * Template fixes
 *
 * Revision 1.41  2004/09/27 22:42:08  southa
 * MSVC compilation fixes
 *
 * Revision 1.40  2004/03/06 13:59:59  southa
 * Fixes
 *
 * Revision 1.39  2004/03/06 13:13:42  southa
 * Maurheen created
 *
 * Revision 1.38  2004/01/02 21:13:07  southa
 * Source conditioning
 *
 * Revision 1.37  2003/10/06 23:06:31  southa
 * Include fixes
 *
 * Revision 1.36  2003/10/06 22:23:45  southa
 * Game to GameMustl move
 *
 * Revision 1.35  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.34  2003/08/21 23:08:54  southa
 * Fixed file headers
 *
 * Revision 1.33  2003/03/10 21:57:11  southa
 * ic2 revisions
 *
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
#include "GameRouter.h"
#include "GameSTL.h"

#include "mushGL.h"
#include "mushMedia.h"
#include "mushPlatform.h"

#ifdef MUSHWARE_USE_MUSTL
#include "mushMustlGame.h"
#endif

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
        GLString glStr(MushcoreInfo::Sgl().ApplicationNameGet(), GLFontRef("font-mono1", 0.04), 0);
        glStr.Render();
    }

    {
        GLState::ColourSet(0.8,0.8,1.0,1);
        orthoGL.MoveRelative(0, -0.03);
        GLString glStr("Version: "+MushcoreInfo::Sgl().PackageVersionGet()+"  ID: "+MushcoreInfo::Sgl().PackageIDGet(), GLFontRef("font-mono1", 0.018), 0);
        glStr.Render();
    }
    
    
    {
        GLState::ColourSet(1.0,1.0,1.0,1.0);
        orthoGL.MoveRelative(0, -0.12);
        GLString glStr("Configuration mode", GLFontRef("font-mono1", 0.03), 0);
        glStr.Render();
    }

    {
        GLState::ColourSet(0.8,0.8,1.0,1.0);
        GLString glStr("Please click this window or view", GLFontRef("font-mono1", 0.02), 0);
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
        GLString glStr("Click this window to begin", GLFontRef("font-mono1", 0.03), 0);
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
#ifdef MUSHWARE_USE_MUSTL
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
#else
    U32 webPort = 0;
#endif
    
    ostringstream configURL;
    configURL << "http://127.0.0.1:" << webPort << "/";
    m_configURL=configURL.str();
    m_gameState=kGameStateConfig;
}    

void
GameSetup::Config(void)
{
    m_currentMsec=dynamic_cast<GLAppHandler &>(MushcoreAppHandler::Sgl()).MillisecondsGet();
    
#ifdef MUSHWARE_USE_MUSTL
    MustlGameUtils::WebReceive();
    MustlGameUtils::NetReceive();

    if (m_currentMsec > m_lastTickerMsec + kTickerMsec)
    {
        m_lastTickerMsec = m_currentMsec;
        MustlGameUtils::NetTicker();
    }
#endif
    
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
    if (gameAppHandler.LatchedKeyStateTake(MediaKeyboard::kKeyMouse0))
    {
#ifdef MUSHWARE_USE_MUSTL
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
#endif
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


void
operator>>(MushcoreXMLIStream& ioIn, GameSetup::tGameState& inValue)
{
    Mushware::tXMLVal value;
    ioIn >> value;
	inValue = static_cast<GameSetup::tGameState>(static_cast<Mushware::U32>(value));
}

//%outOfLineFunctions {

const char *GameSetup::AutoName(void) const
{
    return "GameSetup";
}

MushcoreVirtualObject *GameSetup::AutoClone(void) const
{
    return new GameSetup(*this);
}

MushcoreVirtualObject *GameSetup::AutoCreate(void) const
{
    return new GameSetup;
}

MushcoreVirtualObject *GameSetup::AutoVirtualFactory(void)
{
    return new GameSetup;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("GameSetup", GameSetup::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
GameSetup::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "gameState=" << m_gameState << ", ";
    ioOut << "configURL=" << m_configURL << ", ";
    ioOut << "currentMsec=" << m_currentMsec << ", ";
    ioOut << "lastTickerMsec=" << m_lastTickerMsec << ", ";
    ioOut << "windowClicked=" << m_windowClicked;
    ioOut << "]";
}
bool
GameSetup::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "gameState")
    {
        ioIn >> m_gameState;
    }
    else if (inTagStr == "configURL")
    {
        ioIn >> m_configURL;
    }
    else if (inTagStr == "currentMsec")
    {
        ioIn >> m_currentMsec;
    }
    else if (inTagStr == "lastTickerMsec")
    {
        ioIn >> m_lastTickerMsec;
    }
    else if (inTagStr == "windowClicked")
    {
        ioIn >> m_windowClicked;
    }
    else 
    {
        return false;
    }
    return true;
}
void
GameSetup::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("gameState");
    ioOut << m_gameState;
    ioOut.TagSet("configURL");
    ioOut << m_configURL;
    ioOut.TagSet("currentMsec");
    ioOut << m_currentMsec;
    ioOut.TagSet("lastTickerMsec");
    ioOut << m_lastTickerMsec;
    ioOut.TagSet("windowClicked");
    ioOut << m_windowClicked;
}
//%outOfLineFunctions } I4pbLqHwrNu5+sK7z8chOw
