//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameQuit.cpp
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
//%Header } r79mqt+2RFNLrIfNJYqp7A
/*
 * $Id: GameQuit.cpp,v 1.26 2005/07/02 00:42:37 southa Exp $
 * $Log: GameQuit.cpp,v $
 * Revision 1.26  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.25  2005/06/20 14:30:34  southa
 * Adanaxis work
 *
 * Revision 1.24  2005/06/16 17:25:38  southa
 * Client/server work
 *
 * Revision 1.23  2005/05/19 13:02:02  southa
 * Mac release work
 *
 * Revision 1.22  2005/04/19 23:25:39  southa
 * Mode switching and recognition
 *
 * Revision 1.21  2005/03/13 00:34:46  southa
 * Build fixes, key support and stereo
 *
 * Revision 1.20  2005/02/10 12:33:58  southa
 * Template fixes
 *
 * Revision 1.19  2004/09/27 22:42:08  southa
 * MSVC compilation fixes
 *
 * Revision 1.18  2004/03/06 13:59:59  southa
 * Fixes
 *
 * Revision 1.17  2004/03/06 13:13:42  southa
 * Maurheen created
 *
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
#include "mushPlatform.h"

#ifdef MUSHWARE_USE_MUSTL
#include "mushMustlGame.h"
#endif

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
        GLState::ColourSet(1.0,1.0,1.0,0.75+0.25*sin(msecNow/100));
        orthoGL.MoveRelative(0, -0.12);
        GLString glStr("Quitting", GLFontRef("font-mono1", 0.03), 0);
        glStr.Render();
    }
    GLUtils::OrthoEpilogue();
    GLUtils::DisplayEpilogue();
}

void
GameQuit::Init(void)
{
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Sgl());
    m_startMsec=gameAppHandler.MillisecondsGet();

#ifdef MUSHWARE_USE_MUSTL
    MustlLog::Sgl().WebLog() << "Waiting to quit" << endl;
    MustlGameUtils::KillServers();
    MustlGameUtils::KillClients();
#endif
}    

void
GameQuit::Timing(void)
{
#ifdef MUSHWARE_USE_MUSTL
    MustlWebServer::Sgl().Accept();
    MustlWebRouter::Sgl().ReceiveAll();
#endif
    GLUtils::PostRedisplay();
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Sgl());

#ifdef MUSHWARE_USE_MUSTL
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
#else    
    gameAppHandler.AppQuit();
#endif
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
	inValue = static_cast<GameQuit::tGameState>(static_cast<Mushware::U32>(value));
}

//%outOfLineFunctions {

const char *GameQuit::AutoName(void) const
{
    return "GameQuit";
}

MushcoreVirtualObject *GameQuit::AutoClone(void) const
{
    return new GameQuit(*this);
}

MushcoreVirtualObject *GameQuit::AutoCreate(void) const
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
    ioOut << "gameState=" << m_gameState << ", ";
    ioOut << "startMsec=" << m_startMsec;
    ioOut << "]";
}
bool
GameQuit::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
    else if (inTagStr == "startMsec")
    {
        ioIn >> m_startMsec;
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
    ioOut.TagSet("gameState");
    ioOut << m_gameState;
    ioOut.TagSet("startMsec");
    ioOut << m_startMsec;
}
//%outOfLineFunctions } BG3ZdMAPQHDxHx1aMUelxA
