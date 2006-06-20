//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisGame.cpp
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } DEX6Sh9oUk/bih2GXm2coA
/*
 * $Id: AdanaxisGame.cpp,v 1.31 2006/06/14 18:45:45 southa Exp $
 * $Log: AdanaxisGame.cpp,v $
 * Revision 1.31  2006/06/14 18:45:45  southa
 * Ruby mesh generation
 *
 * Revision 1.30  2006/06/12 16:01:21  southa
 * Ruby mesh generation
 *
 * Revision 1.29  2006/06/07 12:15:18  southa
 * Grid and test textures
 *
 * Revision 1.28  2006/06/06 17:58:31  southa
 * Ruby texture definition
 *
 * Revision 1.27  2006/06/05 16:54:43  southa
 * Ruby textures
 *
 * Revision 1.26  2006/05/01 17:39:00  southa
 * Texture generation
 *
 * Revision 1.25  2006/04/20 00:22:45  southa
 * Added ruby executive
 *
 * Revision 1.24  2006/04/19 20:14:10  southa
 * Added Ruby framework
 *
 * Revision 1.23  2005/09/05 12:54:29  southa
 * Solid rendering work
 *
 * Revision 1.22  2005/08/05 10:33:33  southa
 * win32 build fixes
 *
 * Revision 1.21  2005/08/02 14:37:44  southa
 * Adanaxis control demo work
 *
 * Revision 1.20  2005/08/02 11:11:47  southa
 * Adanaxis control demo work
 *
 * Revision 1.19  2005/08/01 20:24:15  southa
 * Backdrop and build fixes
 *
 * Revision 1.18  2005/07/18 13:13:35  southa
 * Extrude to point and projectile mesh
 *
 * Revision 1.17  2005/07/11 16:37:46  southa
 * Uplink control work
 *
 * Revision 1.16  2005/07/07 16:54:17  southa
 * Control tweaks
 *
 * Revision 1.15  2005/07/06 19:08:26  southa
 * Adanaxis control work
 *
 * Revision 1.14  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.13  2005/07/02 00:42:36  southa
 * Conditioning tweaks
 *
 * Revision 1.12  2005/07/01 16:42:54  southa
 * Render work
 *
 * Revision 1.11  2005/06/30 16:29:24  southa
 * Adanaxis work
 *
 * Revision 1.10  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 * Revision 1.9  2005/06/23 13:56:56  southa
 * MushGame link work
 *
 * Revision 1.8  2005/06/23 11:58:27  southa
 * MushGame link work
 *
 * Revision 1.7  2005/06/21 15:57:46  southa
 * MushGame work
 *
 * Revision 1.6  2005/06/21 13:10:50  southa
 * MushGame work
 *
 * Revision 1.5  2005/06/20 14:30:33  southa
 * Adanaxis work
 *
 * Revision 1.4  2005/06/16 17:25:37  southa
 * Client/server work
 *
 * Revision 1.3  2005/06/14 20:39:40  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/06/14 13:25:33  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/13 17:34:54  southa
 * Adanaxis creation
 *
 */

#include "AdanaxisGame.h"

#include "AdanaxisAppHandler.h"
#include "AdanaxisClient.h"
#include "AdanaxisMeshLibrary.h"
#include "AdanaxisRuby.h"
#include "AdanaxisSaveData.h"
#include "AdanaxisServer.h"
#include "AdanaxisUtil.h"

#include "API/mushPlatform.h"
#include "API/mushMedia.h"
#include "API/mushMushGL.h"
#include "API/mushMushGame.h"
#include "API/mushMushMesh.h"
#include "API/mushMushMeshLibrary.h"
#include "API/mushMushRuby.h"

using namespace Mushware;
using namespace std;

AdanaxisGame::AdanaxisGame(const std::string& inName) :
    m_inited(false),
    m_name(inName),
	m_rubyGame(Mushware::kRubyQnil),
	m_rubySpace(Mushware::kRubyQnil)
{
}

AdanaxisGame::~AdanaxisGame()
{}

void
AdanaxisGame::Process(GameAppHandler& inAppHandler)
{    
    U32 msecNow = inAppHandler.MillisecondsGet();

    VolatileData().ModeKeypressMsecSet(m_modeKeypressMsec);
    VolatileData().NewModeSet(m_newMode);
    
    
    if (inAppHandler.LatchedKeyStateTake('m'))
    {
        m_config.PlayMusicToggle();
        if (m_config.PlayMusic())
        {
            MediaAudio::Sgl().MusicFadeIn(300);            
        }
        else
        {
            MediaAudio::Sgl().MusicFadeOut(300);            
        }
    }
    if (inAppHandler.LatchedKeyStateTake('-'))
    {
        if (m_modeKeypressMsec != 0)
        {
            m_newMode = PlatformVideoUtils::Sgl().PreviousModeDef(m_newMode);
        }
        m_modeKeypressMsec = msecNow;
    }
    if (inAppHandler.LatchedKeyStateTake('='))
    {
        if (m_modeKeypressMsec != 0)
        {
            m_newMode = PlatformVideoUtils::Sgl().NextModeDef(m_newMode);
        }
        m_modeKeypressMsec = msecNow;
    }
    if (m_modeKeypressMsec != 0 && m_modeKeypressMsec + 3000 < msecNow)
    {
        if (m_newMode != m_config.DisplayMode())
        {
            m_config.DisplayModeSet(m_newMode);
            SwapOut(inAppHandler);
            SwapIn(inAppHandler);
        }
        
        m_modeKeypressMsec=0;
    }
    
    m_logicRef.WRef().PerFrameProcessing();
    Logic().MainSequence();
        
    GLUtils::PostRedisplay();
}

void
AdanaxisGame::Display(GameAppHandler& inAppHandler)
{    
    //tVal msecNow = inAppHandler.MillisecondsGet();
    

}

void
AdanaxisGame::ScriptFunction(const std::string& inName, GameAppHandler& inAppHandler) const
{}

void 
AdanaxisGame::LocalGameCreate(GameAppHandler& inAppHandler)
{
    MushGameUtil::LocalGameCreate("adanaxis", "Adanaxis");
    m_clientRef.NameSet(m_name);
    m_serverRef.NameSet(m_name);
    m_saveDataRef.NameSet(m_name);
    m_volatileDataRef.NameSet(m_name);
    m_logicRef.NameSet(m_name);
	AdanaxisRuby::LogicNameSet(m_name);
    MushGameUtil::LocalGameJobsCreate(m_logicRef.WRef());
}

void
AdanaxisGame::Init(GameAppHandler& inAppHandler)
{    
    MushMeshLibraryBase::SingletonMutate(new AdanaxisMeshLibrary);
    MushMesh4Maker::SingletonMutate(new MushMeshLibraryMaker);

    std::srand(time(NULL));
    
    LocalGameCreate(inAppHandler);
    
    MushGameConfigUtils::ConfigAcquire(&m_config);
    
    if (m_config.SafeMode())
    {
        m_config.DisplayModeSet(0);
        MushGameDialogueUtils::NamedDialoguesAdd(SaveData().DialoguesWRef(), "^safemode");
    }
    
    MushGameDialogueUtils::NamedDialoguesAdd(SaveData().DialoguesWRef(), "^start");

    Logic().InitialDataCreate();

    UpdateFromConfig();
    
	m_rubyGame = MushRubyExec::Sgl().Call("$currentGame.mLoad");
	m_rubySpace = MushRubyExec::Sgl().Call("$currentGame.space");
	MushRubyExec::Sgl().Call(m_rubySpace, "mInitialPiecesCreate");
	
    AdanaxisUtil::TestSkinsCreate(Logic());
    AdanaxisUtil::TestDecoCreate(Logic());
    AdanaxisUtil::TestPiecesCreate(Logic());
    
    MushcoreInterpreter::Sgl().Execute("loadsoundstream('adanaxis-music1')");
    if (m_config.PlayMusic())
    {
        MediaAudio::Sgl().MusicFadeIn(300);                    
    }
    
    Logic().StartTimeSet(inAppHandler.MillisecondsGet());
    m_inited = true;
}

void
AdanaxisGame::UpdateFromConfig(void)
{
    AdanaxisAppHandler& appHandler = AdanaxisUtil::AppHandler();
    for (U32 i=0; i < m_config.AxisDefs().size(); ++i)
    {
        appHandler.AxisDefSet(m_config.AxisDefs(i), i);
    }
    
    for (U32 i=0; i < m_config.KeyDefs().size(); ++i)
    {
        appHandler.KeyDefSet(m_config.KeyDefs(i), i);
    }
}

void
AdanaxisGame::SwapIn(GameAppHandler& inAppHandler)
{
    AdanaxisAppHandler& appHandler = AdanaxisUtil::AppHandler();
    appHandler.LastAxesValidSet(false);

    if (!m_inited)
    {
        Init(inAppHandler);
    }
    
    try
    {
        inAppHandler.EnterScreen(PlatformVideoUtils::Sgl().ModeDefGet(m_config.DisplayMode()));
        MushGLV::Sgl().Acquaint();
        if (MushcoreEnv::Sgl().VariableExists("MUSHGL_DUMP_MUSHGLV"))
        {
            std::cout << MushGLV::Sgl() << endl;
        }
    }
    catch (...)
    {
        m_config.DisplayModeSet(0);
        throw;
    }
    
    GLUtils::CheckGLError();
    //tVal msecNow = inAppHandler.MillisecondsGet();
   
    m_modeKeypressMsec = 0;
    m_newMode = m_config.DisplayMode();
    Logic().RecordTimeSet(m_config.RecordTime());
}

void
AdanaxisGame::SwapOut(GameAppHandler& inAppHandler)
{
    
    tMsec gameTime = Logic().EndTime() - Logic().StartTime();
    
    if (m_config.RecordTime() == 0 || gameTime < m_config.RecordTime())
    {
        if (Logic().KhaziCount() == 0)
        {
            m_config.RecordTimeSet(gameTime);
        }
    }

    const MushcoreScalar *pScalar;    
    if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "CONFIG_FILENAME"))
    {
        m_config.AutoFileSave(pScalar->StringGet());
    }
}

//%outOfLineFunctions {

const char *AdanaxisGame::AutoName(void) const
{
    return "AdanaxisGame";
}

MushcoreVirtualObject *AdanaxisGame::AutoClone(void) const
{
    return new AdanaxisGame(*this);
}

MushcoreVirtualObject *AdanaxisGame::AutoCreate(void) const
{
    return new AdanaxisGame;
}

MushcoreVirtualObject *AdanaxisGame::AutoVirtualFactory(void)
{
    return new AdanaxisGame;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisGame", AdanaxisGame::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisGame::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "name=" << m_name << ", ";
    ioOut << "modeKeypressMsec=" << m_modeKeypressMsec << ", ";
    ioOut << "newMode=" << m_newMode << ", ";
    ioOut << "saveDataRef=" << m_saveDataRef << ", ";
    ioOut << "volatileDataRef=" << m_volatileDataRef << ", ";
    ioOut << "clientRef=" << m_clientRef << ", ";
    ioOut << "serverRef=" << m_serverRef << ", ";
    ioOut << "logicRef=" << m_logicRef << ", ";
    ioOut << "config=" << m_config << ", ";
    ioOut << "rubyGame=" << m_rubyGame << ", ";
    ioOut << "rubySpace=" << m_rubySpace;
    ioOut << "]";
}
bool
AdanaxisGame::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "name")
    {
        ioIn >> m_name;
    }
    else if (inTagStr == "modeKeypressMsec")
    {
        ioIn >> m_modeKeypressMsec;
    }
    else if (inTagStr == "newMode")
    {
        ioIn >> m_newMode;
    }
    else if (inTagStr == "saveDataRef")
    {
        ioIn >> m_saveDataRef;
    }
    else if (inTagStr == "volatileDataRef")
    {
        ioIn >> m_volatileDataRef;
    }
    else if (inTagStr == "clientRef")
    {
        ioIn >> m_clientRef;
    }
    else if (inTagStr == "serverRef")
    {
        ioIn >> m_serverRef;
    }
    else if (inTagStr == "logicRef")
    {
        ioIn >> m_logicRef;
    }
    else if (inTagStr == "config")
    {
        ioIn >> m_config;
    }
    else if (inTagStr == "rubyGame")
    {
        ioIn >> m_rubyGame;
    }
    else if (inTagStr == "rubySpace")
    {
        ioIn >> m_rubySpace;
    }
    else 
    {
        return false;
    }
    return true;
}
void
AdanaxisGame::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("name");
    ioOut << m_name;
    ioOut.TagSet("modeKeypressMsec");
    ioOut << m_modeKeypressMsec;
    ioOut.TagSet("newMode");
    ioOut << m_newMode;
    ioOut.TagSet("saveDataRef");
    ioOut << m_saveDataRef;
    ioOut.TagSet("volatileDataRef");
    ioOut << m_volatileDataRef;
    ioOut.TagSet("clientRef");
    ioOut << m_clientRef;
    ioOut.TagSet("serverRef");
    ioOut << m_serverRef;
    ioOut.TagSet("logicRef");
    ioOut << m_logicRef;
    ioOut.TagSet("config");
    ioOut << m_config;
    ioOut.TagSet("rubyGame");
    ioOut << m_rubyGame;
    ioOut.TagSet("rubySpace");
    ioOut << m_rubySpace;
}
//%outOfLineFunctions } y3R7S3Xddx3Lcnej/pDAMA
