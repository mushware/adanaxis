//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisGame.cpp
 *
 * Copyright: Andy Southgate 2005
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
//%Header } 1+Fcp5/pJdalVjA2hnviXw
/*
 * $Id: AdanaxisGame.cpp,v 1.8 2005/06/23 11:58:27 southa Exp $
 * $Log: AdanaxisGame.cpp,v $
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

#include "AdanaxisClient.h"
#include "AdanaxisSaveData.h"
#include "AdanaxisServer.h"

#include "API/mushPlatform.h"
#include "API/mushMedia.h"
#include "API/mushMushGL.h"
#include "API/mushMushGame.h"

using namespace Mushware;
using namespace std;

AdanaxisGame::AdanaxisGame(const std::string& inName) :
    m_inited(false),
    m_name(inName)
{
}

AdanaxisGame::~AdanaxisGame()
{}

void
AdanaxisGame::Process(GameAppHandler& inAppHandler)
{    
    m_logicRef.WRef().PerFrameProcessing();
    Logic().MainSequence();
    GLUtils::PostRedisplay();
}

void
AdanaxisGame::Display(GameAppHandler& inAppHandler)
{    
    //tVal msecNow = inAppHandler.MillisecondsGet();
    
    GLUtils::DisplayPrologue();
    GLUtils::ClearScreen();
    
    MushGameDialogueUtils::MoveAndRender(SaveData().DialoguesWRef(), inAppHandler);
    
    GLUtils::OrthoPrologue();
    
    if (m_modeKeypressMsec != 0)
    {
        PlatformVideoUtils::Sgl().RenderModeInfo(m_newMode);
    }
    
    GLUtils::OrthoEpilogue();
    
    GLUtils::DisplayEpilogue();
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
    m_logicRef.NameSet(m_name);
    MushGameUtil::LocalGameJobsCreate(m_logicRef.WRef());
}

void
AdanaxisGame::Init(GameAppHandler& inAppHandler)
{
    LocalGameCreate(inAppHandler);
    
    MushGameConfigUtils::ConfigAcquire(&m_config);
    
    if (m_config.SafeMode())
    {
        m_config.DisplayModeSet(0);
        MushGameDialogueUtils::NamedDialoguesAdd(SaveData().DialoguesWRef(), "^safemode");
    }
    
    MushGameDialogueUtils::NamedDialoguesAdd(SaveData().DialoguesWRef(), "^start");

    m_inited = true;
}

void
AdanaxisGame::SwapIn(GameAppHandler& inAppHandler)
{
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

}

void
AdanaxisGame::SwapOut(GameAppHandler& inAppHandler)
{
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
    ioOut << "clientRef=" << m_clientRef << ", ";
    ioOut << "serverRef=" << m_serverRef << ", ";
    ioOut << "logicRef=" << m_logicRef << ", ";
    ioOut << "config=" << m_config;
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
    ioOut.TagSet("clientRef");
    ioOut << m_clientRef;
    ioOut.TagSet("serverRef");
    ioOut << m_serverRef;
    ioOut.TagSet("logicRef");
    ioOut << m_logicRef;
    ioOut.TagSet("config");
    ioOut << m_config;
}
//%outOfLineFunctions } EbWvTrB6V4QdgXdU4KFoLA
