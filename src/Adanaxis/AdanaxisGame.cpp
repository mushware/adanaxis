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
 * $Id: AdanaxisGame.cpp,v 1.1 2005/06/13 17:34:54 southa Exp $
 * $Log: AdanaxisGame.cpp,v $
 * Revision 1.1  2005/06/13 17:34:54  southa
 * Adanaxis creation
 *
 */

#include "AdanaxisGame.h"

#include "mushPlatform.h"
#include "mushMedia.h"
#include "mushMushGL.h"

using namespace Mushware;
using namespace std;

AdanaxisGame::AdanaxisGame() :
    m_inited(false)
{
}

AdanaxisGame::~AdanaxisGame()
{}

void
AdanaxisGame::Process(GameAppHandler& inAppHandler)
{
    GameAppHandler& gameAppHandler = inAppHandler;
    tVal msecNow = gameAppHandler.MillisecondsGet();
    
    GLUtils::PostRedisplay();
}

void
AdanaxisGame::Display(GameAppHandler& inAppHandler)
{    
    //GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Sgl());
    //tVal msecNow = gameAppHandler.MillisecondsGet();
    
    GLUtils::DisplayPrologue();
    GLUtils::ClearScreen();
    
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
AdanaxisGame::Init(GameAppHandler& inAppHandler)
{
    const MushcoreScalar *pScalar; 
    m_config.DisplayModeSet(MushcoreEnv::Sgl().VariableGet("MUSHGL_DISPLAY_MODE").U32Get());
    
    try
    {
        if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "CONFIG_FILENAME"))
        {
            if (!m_config.AutoFileIfExistsLoad(pScalar->StringGet()))
            {
                MushcoreLog::Sgl().InfoLog() << "Creating new configuration file '" << pScalar->StringGet() << "'" << endl;
                m_config.ToDefaultSet();
            }
            if (m_config.Version() != AdanaxisConfig().Version())
            {
                throw MushcoreDataFail("Incompatible configuration file version - discarding");
            }
        }
    }
    catch (MushcoreNonFatalFail& e)
    {
        MushcoreLog::Sgl().ErrorLog() << e.what() << endl;
        m_config.ToDefaultSet();
    }
    
    if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "SAFE_MODE"))
    {
        if (pScalar->U32Get())
        {
            m_config.DisplayModeSet(0);
            //NamedDialoguesAdd("^safemode");
        }
    }

    //NamedDialoguesAdd("^start");

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

const char *AdanaxisGame::AutoNameGet(void) const
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
    ioOut << "modeKeypressMsec=" << m_modeKeypressMsec << ", ";
    ioOut << "newMode=" << m_newMode << ", ";
    ioOut << "dialogues=" << m_dialogues << ", ";
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
    else if (inTagStr == "modeKeypressMsec")
    {
        ioIn >> m_modeKeypressMsec;
    }
    else if (inTagStr == "newMode")
    {
        ioIn >> m_newMode;
    }
    else if (inTagStr == "dialogues")
    {
        ioIn >> m_dialogues;
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
    ioOut.TagSet("modeKeypressMsec");
    ioOut << m_modeKeypressMsec;
    ioOut.TagSet("newMode");
    ioOut << m_newMode;
    ioOut.TagSet("dialogues");
    ioOut << m_dialogues;
    ioOut.TagSet("config");
    ioOut << m_config;
}
//%outOfLineFunctions } zwexsupJy5H07WzL0MH39w
