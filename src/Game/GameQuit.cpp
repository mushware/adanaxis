//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameQuit.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 8z6frlELi6JgItG1tdJiyw
/*
 * $Id: GameQuit.cpp,v 1.16 2004/01/02 21:13:07 southa Exp $
 * $Log: GameQuit.cpp,v $
 * Revision 1.16  2004/01/02 21:13:07  southa
 * Source conditioning
 *
 * Revision 1.15  2003/10/06 23:06:31  southa
 * Include fixes
 *
 * Revision 1.14  2003/10/06 22:23:44  southa
 * Game to GameMustl move
 *
 * Revision 1.13  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.12  2003/08/21 23:08:52  southa
 * Fixed file headers
 *
 * Revision 1.11  2003/01/20 10:45:27  southa
 * Singleton tidying
 *
 * Revision 1.10  2003/01/13 14:32:00  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.9  2003/01/12 17:32:56  southa
 * Mushcore work
 *
 * Revision 1.8  2003/01/11 17:44:26  southa
 * Mushcore fixes
 *
 * Revision 1.7  2003/01/09 14:57:03  southa
 * Created Mushcore
 *
 * Revision 1.6  2002/12/29 20:59:57  southa
 * More build fixes
 *
 * Revision 1.5  2002/12/20 13:17:42  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.4  2002/12/12 14:00:40  southa
 * Created Mustl
 *
 * Revision 1.3  2002/12/03 20:28:17  southa
 * Network, player and control work
 *
 * Revision 1.2  2002/11/22 11:42:06  southa
 * Added developer controls
 *
 * Revision 1.1  2002/11/18 18:55:58  southa
 * Game resume and quit
 *
 */

#include "GameQuit.h"

#include "GameAppHandler.h"
#include "GameConfigDef.h"
#include "GameSTL.h"

#include "mushGL.h"
#include "mushMedia.h"
#include "mushMustlGame.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

GameQuit::GameQuit() :
    m_gameState(kGameStateInit)
{
}

void
GameQuit::Process(GameAppHandler& inAppHandler)
{
    switch (m_gameState)
    {
        case kGameStateInit:
            Init();
            m_gameState=kGameStateTiming;
            break;

        case kGameStateTiming:
            Timing();
            break;

        default:
            throw(MushcoreLogicFail("Bad value for m_gameState"));
    }
}

void
GameQuit::Display(GameAppHandler& inAppHandler)
{
    GLUtils::DisplayPrologue();
    GLUtils::ClearScreen();
    GLUtils::OrthoPrologue();

    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Sgl());

    tVal msecNow=gameAppHandler.MillisecondsGet() - m_startMsec;
    
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
        GLState::ColourSet(1.0,1.0,1.0,0.75+0.25*sin(msecNow/100));
        orthoGL.MoveRelative(0, -0.12);
        GLString glStr("Quitting", GLFontRef("font-system1", 0.03), 0);
        glStr.Render();
    }
    GLUtils::OrthoEpilogue();
    GLUtils::DisplayEpilogue();
}

void
GameQuit::Init(void)
{
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Sgl());

    MustlLog::Sgl().WebLog() << "Waiting to quit" << endl;
    m_startMsec=gameAppHandler.MillisecondsGet();
    MustlGameUtils::KillServers();
    MustlGameUtils::KillClients();
}    

void
GameQuit::Timing(void)
{
    MustlWebServer::Sgl().Accept();
    MustlWebRouter::Sgl().ReceiveAll();
    GLUtils::PostRedisplay();
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Sgl());
    U32 currentMsec=gameAppHandler.MillisecondsGet();

    if (m_startMsec + kQuitHangTime < currentMsec)
    {
        // Quit after quit hang time if all web links are closed
        if (MushcoreData<MustlWebLink>::Sgl().Size() == 0)
        {
            MustlLog::Sgl().WebLog() << "Quitting" << endl;
            gameAppHandler.AppQuit();
        }
    }
    
    if (m_startMsec + kQuitTimeout < currentMsec)
    {
        MustlLog::Sgl().WebLog() << "Quitting on timeout" << endl;
        gameAppHandler.AppQuit();
    }
}

void
GameQuit::ScriptFunction(const string& inName, GameAppHandler& inAppHandler) const
{
}

void
GameQuit::SwapIn(GameAppHandler& inAppHandler)
{
}

void
GameQuit::SwapOut(GameAppHandler& inAppHandler)
{
}

void
operator>>(MushcoreXMLIStream& ioIn, GameQuit::tGameState& inValue)
{
    Mushware::tXMLVal value;
    ioIn >> value;
    inValue = static_cast<GameQuit::tGameState>(value);
}

//%outOfLineFunctions {
const char *GameQuit::AutoNameGet(void) const
{
    return "GameQuit";
}
GameQuit *GameQuit::AutoClone(void) const
{
    return new GameQuit(*this);
}
GameQuit *GameQuit::AutoCreate(void) const
{
    return new GameQuit;
}
MushcoreVirtualObject *GameQuit::AutoVirtualFactory(void)
{
    return new GameQuit;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("GameQuit", GameQuit::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
GameQuit::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    GameBase::AutoPrint(ioOut);
    ioOut << "gameState=" << m_gameState << ", ";
    ioOut << "startMsec=" << m_startMsec;
    ioOut << "]";
}
bool
GameQuit::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "gameState")
    {
        ioIn >> m_gameState;
    }
    else if (inTagStr == "startMsec")
    {
        ioIn >> m_startMsec;
    }
    else if (GameBase::AutoXMLDataProcess(ioIn, inTagStr))
    {
        // Tag consumed by base class
    }
    else
    {
        return false;
    }
    return true;
}
void
GameQuit::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    GameBase::AutoXMLPrint(ioOut);
    ioOut.TagSet("gameState");
    ioOut << m_gameState;
    ioOut.TagSet("startMsec");
    ioOut << m_startMsec;
}
//%outOfLineFunctions } OA02MJyGgAQQJM7kZqgQTQ
