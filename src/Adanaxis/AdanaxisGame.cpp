//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisGame.cpp
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.2, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 7d8XNXTzlBe/E65+Bc7mXg
/*
 * $Id: AdanaxisGame.cpp,v 1.64 2007/04/16 08:41:07 southa Exp $
 * $Log: AdanaxisGame.cpp,v $
 * Revision 1.64  2007/04/16 08:41:07  southa
 * Level and header mods
 *
 * Revision 1.63  2007/03/20 17:31:23  southa
 * Difficulty and GL options
 *
 * Revision 1.62  2007/03/09 19:50:11  southa
 * Resident textures
 *
 * Revision 1.61  2007/03/07 16:59:43  southa
 * Khazi spawning and level ends
 *
 * Revision 1.60  2007/02/08 17:55:14  southa
 * Common routines in space generation
 *
 * Revision 1.59  2006/12/18 15:39:35  southa
 * Palette changes
 *
 * Revision 1.58  2006/12/14 15:59:23  southa
 * Fire and cutscene fixes
 *
 * Revision 1.57  2006/12/14 00:33:44  southa
 * Control fix and audio pacing
 *
 * Revision 1.56  2006/11/25 21:26:31  southa
 * Display mode definitions
 *
 * Revision 1.55  2006/11/09 23:53:59  southa
 * Explosion and texture loading
 *
 * Revision 1.54  2006/11/03 18:46:33  southa
 * Damage effectors
 *
 * Revision 1.53  2006/10/17 15:28:01  southa
 * Player collisions
 *
 * Revision 1.52  2006/09/07 10:02:36  southa
 * Shader interface
 *
 * Revision 1.51  2006/08/01 23:21:52  southa
 * Rendering demo content
 *
 * Revision 1.50  2006/08/01 17:21:23  southa
 * River demo
 *
 * Revision 1.49  2006/07/31 11:01:36  southa
 * Music and dialogues
 *
 * Revision 1.48  2006/07/28 16:52:18  southa
 * Options work
 *
 * Revision 1.47  2006/07/28 11:14:27  southa
 * Records for multiple spaces
 *
 * Revision 1.46  2006/07/27 13:51:33  southa
 * Menu and control fixes
 *
 * Revision 1.45  2006/07/26 16:37:20  southa
 * Options menu
 *
 * Revision 1.44  2006/07/20 12:22:20  southa
 * Precache display
 *
 * Revision 1.43  2006/07/19 14:34:50  southa
 * Flare effects
 *
 * Revision 1.42  2006/07/18 16:58:36  southa
 * Texture fixes
 *
 * Revision 1.41  2006/07/12 11:22:40  southa
 * Advanced control menu
 *
 * Revision 1.40  2006/07/11 19:49:03  southa
 * Control menu
 *
 * Revision 1.39  2006/07/07 18:13:57  southa
 * Menu start and stop
 *
 * Revision 1.38  2006/07/04 16:55:26  southa
 * Ruby key handling
 *
 * Revision 1.37  2006/07/02 21:08:53  southa
 * Ruby menu work
 *
 * Revision 1.36  2006/06/30 17:26:09  southa
 * Render prelude
 *
 * Revision 1.35  2006/06/30 15:05:31  southa
 * Texture and buffer purge
 *
 * Revision 1.34  2006/06/21 16:52:28  southa
 * Deco objects
 *
 * Revision 1.33  2006/06/21 12:17:54  southa
 * Ruby object generation
 *
 * Revision 1.32  2006/06/20 19:06:51  southa
 * Object creation
 *
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
#include "AdanaxisRecords.h"
#include "AdanaxisRender.h"
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
    m_startDialogueShown(false)
{
}

AdanaxisGame::~AdanaxisGame()
{}

void
AdanaxisGame::Process(MushGameAppHandler& inAppHandler)
{
#ifdef MUSHCORE_DEBUG
    if (inAppHandler.LatchedKeyStateTake('.'))
    {
        MushGLUtil::BufferPurge();
    }
    if (inAppHandler.LatchedKeyStateTake('/'))
    {
        MushGLUtil::TexturePurge();
    }
    if (inAppHandler.LatchedKeyStateTake(','))
    {
        MushGLUtil::Purge();
        MushGLV::Sgl().Purge();
        MushGLV::Sgl().Acquaint();
    }
#endif
    
    Logic().PerFrameProcessing();
    Logic().MainSequence();
    
    // Start the clock once we're going
    if (!Logic().IsPrecacheMode() && !SaveData().ClockStarted())
    {
        if (Logic().IsGameMode())
        {
            // TimingSequence will have run at least once, so GameMsec is valid
            Logic().StartTimeSet(Logic().GameMsec());
            SaveData().ClockStartedSet(true);
        }
        else if (Logic().IsMenuMode() && !m_startDialogueShown)
        {
            m_startDialogueShown = true;
            MushGameDialogueUtils::NamedDialoguesAdd(SaveData().DialoguesWRef(), "^menuonce");
        }
    }
        
    GLUtils::PostRedisplay();
}

const GLModeDef&
AdanaxisGame::DisplayModeDef(void) const
{
    return m_config.ModeDef();
}

void
AdanaxisGame::PreviousModeDef(void)
{
    m_config.ModeDefSet(PlatformVideoUtils::Sgl().PreviousModeDef(m_config.ModeDef()));
}

void
AdanaxisGame::NextModeDef(void)
{
    m_config.ModeDefSet(PlatformVideoUtils::Sgl().NextModeDef(m_config.ModeDef()));
}

void
AdanaxisGame::BrightnessSet(Mushware::tVal inValue)
{
    VolatileData().BrightnessSet(inValue);
}

void
AdanaxisGame::Display(MushGameAppHandler& inAppHandler)
{    
}

void
AdanaxisGame::ScriptFunction(const std::string& inName, MushGameAppHandler& inAppHandler) const
{}

void 
AdanaxisGame::LocalGameCreate(MushGameAppHandler& inAppHandler)
{
    MushGameUtil::LocalGameCreate("adanaxis", "Adanaxis");
    ClientRefWRef().NameSet(m_name);
    ServerRefWRef().NameSet(m_name);
    SaveDataRefWRef().NameSet(m_name);
    VolatileDataRefWRef().NameSet(m_name);
    LogicRefWRef().NameSet(m_name);
	AdanaxisRuby::LogicNameSet(m_name);
    MushGameUtil::LocalGameJobsCreate(Logic());
}

void
AdanaxisGame::Init(MushGameAppHandler& inAppHandler)
{
    MushMeshLibraryBase::SingletonMutate(new AdanaxisMeshLibrary);
    MushMesh4Maker::SingletonMutate(new MushMeshLibraryMaker);

    std::srand(time(NULL));
    
    LocalGameCreate(inAppHandler);
    
    MushGameConfigUtils::ConfigAcquire(&m_config);
    AdanaxisRecords::Sgl().Load();
        
    if (AdanaxisUtil::AppHandler().FirstGame() && m_config.SafeMode())
    {
        m_config.ModeDefSet(GLModeDef(640, 480, false));
        m_config.TextureDetailSet(0);
        m_config.UseGLCompressionSet(0);
        m_config.UseGLShaderSet(0);
        MushGameDialogueUtils::NamedDialoguesAdd(SaveData().DialoguesWRef(), "^safemode");
    }
    
    Logic().InitialDataCreate();

    UpdateFromConfig();
    
    SaveData().GameDifficultySet(AdanaxisUtil::Config().ConfigDifficulty()); // 
	VolatileData().RubyGameSet(MushRubyExec::Sgl().Call("$currentGame.mLoad"));
	VolatileData().RubyLogicSet(MushRubyExec::Sgl().Eval("$currentLogic"));
	VolatileData().RubySpaceSet(MushRubyExec::Sgl().Call("$currentGame.mSpace"));
	MushRubyExec::Sgl().Call(VolatileData().RubySpace(), "mInitialPiecesCreate");
	VolatileData().IsMenuBackdropSet(MushRubyExec::Sgl().Call(VolatileData().RubySpace(), "mIsMenuBackdrop").Bool());
    SaveData().SpaceNameSet(MushRubyExec::Sgl().Call("$currentGame.mSpaceName").String());
    
	AdanaxisUtil::MissingSkinsCreate(Logic());
    //AdanaxisUtil::MeshPurge(Logic());

    MediaAudio::Sgl().AudioVolumeSet(m_config.AudioVolume() / 100.0);
    MediaAudio::Sgl().MusicVolumeSet(m_config.MusicVolume() / 100.0);
    MediaAudio::Sgl().VoiceVolumeSet(m_config.VoiceVolume() / 100.0);
    MediaAudio::Sgl().MusicFadeOut(1000); // Level starts music once it loads
    
    Logic().RecordTimeSet(AdanaxisRecords::Sgl().RecordTime(SaveData().SpaceName()));
    Logic().MenuModeEnter();
    Logic().StartTimeSet(0);
    Logic().EndTimeSet(0);
    inAppHandler.MouseSensitivitySet(m_config.MouseSensitivity());
    VolatileData().BrightnessSet(m_config.Brightness());
    VolatileData().ScannerOnSet(false);
    
    m_inited = true;
    SaveData().ClockStartedSet(false);
    AdanaxisUtil::AppHandler().FirstGameSet(false);
}

void
AdanaxisGame::ControlsToDefaultSet(MushGameAppHandler& inHandler)
{
    MushGameBase::ControlsToDefaultSet(inHandler);
    m_config.AxesToDefaultSet();
    m_config.KeysToDefaultSet();
    UpdateFromConfig();
}

void
AdanaxisGame::UpdateFromConfig(void)
{
    AdanaxisAppHandler& appHandler = AdanaxisUtil::AppHandler();
    for (U32 i=0; i < m_config.AxisDefs().size(); ++i)
    {
        appHandler.AxisDefSet(m_config.AxisDefs(i), i);
        appHandler.AxisDefWRef(i).Reset();
    }
    
    for (U32 i=0; i < m_config.KeyDefs().size(); ++i)
    {
        appHandler.KeyDefSet(m_config.KeyDefs(i), i);
        appHandler.KeyDefWRef(i).Reset();
    }
}

void
AdanaxisGame::UpdateToConfig(void)
{
    AdanaxisAppHandler& appHandler = AdanaxisUtil::AppHandler();
    for (U32 i=0; i < m_config.AxisDefs().size(); ++i)
    {
        m_config.AxisDefSet(appHandler.AxisDef(i), i);
        m_config.AxisDefWRef(i).Reset();
    }
    
    for (U32 i=0; i < m_config.KeyDefs().size(); ++i)
    {
        m_config.KeyDefSet(appHandler.KeyDef(i), i);
        m_config.KeyDefWRef(i).Reset();
    }
}

void
AdanaxisGame::ConfigSave(void)
{
    const MushcoreScalar *pScalar;    
    if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "CONFIG_FILENAME"))
    {
        UpdateToConfig();
        m_config.AutoFileSave(pScalar->StringGet());
    }
}    

void
AdanaxisGame::SwapIn(MushGameAppHandler& inAppHandler)
{
    MushGameBase::SwapIn(inAppHandler);
    
    AdanaxisAppHandler& appHandler = AdanaxisUtil::AppHandler();
    appHandler.LastAxesValidSet(false);

    if (!m_inited)
    {
        Init(inAppHandler);
    }
    
    try
    {
        const GLModeDef& modeDefRef = m_config.ModeDef();
        
        if (!inAppHandler.ScreenEntered() || modeDefRef != inAppHandler.CurrentModeDefGet())
        {
            if (MushGLV::Sgl().ContextValid())
            {
                // Purge all textures
                MushGLUtil::Purge();
                MushGLV::Sgl().Purge();
            } 
            inAppHandler.EnterScreen(modeDefRef);
            MushGLV::Sgl().Acquaint();
            if (MushcoreEnv::Sgl().VariableExists("MUSHGL_DUMP_MUSHGLV"))
            {
                MushcoreLog::Sgl().InfoLog() << MushGLV::Sgl() << endl;
            }
            
            if (MushGLV::Sgl().HasS3TC())
            {
                m_config.UseGLCompressionSet(m_config.UseGLCompression() % 2);        
            }
            else
            {
                m_config.UseGLCompressionSet(2);        
            }
            MushGLV::Sgl().UseS3TCSet(m_config.UseGLCompression() == 1);
            
            if (MushGLV::Sgl().HasShader())
            {
                m_config.UseGLShaderSet(m_config.UseGLShader() % 2);
                try
                {
                    MushGLUtil::ShaderTest();
                }
                catch (std::exception &e)
                {
                    MushcoreLog::Sgl().WarningLog() << "GL Shader test failed - disabling : " << e.what() << endl;
                    m_config.UseGLShaderSet(2);        
                }
            }
            else
            {
                m_config.UseGLShaderSet(2);        
            }
            MushGLV::Sgl().UseShaderSet(m_config.UseGLShader() == 1);
        }
        else
        {
            // Screen alread valid - just purge the level-specific textures
            MushGLV::Sgl().Acquaint();
            MushGLUtil::PurgeNonResident();
        }
    }
    catch (...)
    {
        m_config.ModeDefSet(GLModeDef(640, 480, false));
        ConfigSave();
        throw;
    }

    GLUtils::CheckGLError();
    
    Logic().PrecacheModeEnter();
    
    dynamic_cast<AdanaxisRender&>(SaveData().RenderRef().WRef()).RenderPreludeSet();
}  

void
AdanaxisGame::SwapOut(MushGameAppHandler& inAppHandler)
{
    MushGameBase::SwapOut(inAppHandler);
    ConfigSave();
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
    ioOut << "config=" << m_config << ", ";
    ioOut << "startDialogueShown=" << m_startDialogueShown;
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
    else if (inTagStr == "config")
    {
        ioIn >> m_config;
    }
    else if (inTagStr == "startDialogueShown")
    {
        ioIn >> m_startDialogueShown;
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
    ioOut.TagSet("config");
    ioOut << m_config;
    ioOut.TagSet("startDialogueShown");
    ioOut << m_startDialogueShown;
}
//%outOfLineFunctions } 7rvmWEETrQ1yRz+b8SzWWA
