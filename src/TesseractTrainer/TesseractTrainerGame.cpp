//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerGame.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } DGznA4s7M/09HsWaOc7wZA
/*
 * $Id: TesseractTrainerGame.cpp,v 1.13 2005/04/19 19:23:14 southa Exp $
 * $Log: TesseractTrainerGame.cpp,v $
 * Revision 1.13  2005/04/19 19:23:14  southa
 * Save and load config
 *
 * Revision 1.12  2005/04/11 23:31:41  southa
 * Startup and registration screen
 *
 * Revision 1.11  2005/04/10 00:09:23  southa
 * Registration
 *
 * Revision 1.10  2005/03/28 18:59:33  southa
 * Dialogues for Tesseract Trainer
 *
 * Revision 1.9  2005/03/25 22:04:50  southa
 * Dialogue and MushcoreIO fixes
 *
 * Revision 1.8  2005/03/25 19:13:51  southa
 * GameDialogue work
 *
 * Revision 1.7  2005/03/13 00:34:48  southa
 * Build fixes, key support and stereo
 *
 * Revision 1.6  2005/03/08 01:24:10  southa
 * Quaternion slerp between orientations
 *
 * Revision 1.5  2005/02/27 01:01:32  southa
 * Eigenplane markers
 *
 * Revision 1.4  2005/02/26 17:53:44  southa
 * Plane sets and pairs
 *
 * Revision 1.3  2005/02/13 22:44:08  southa
 * Tesseract stuff
 *
 * Revision 1.2  2005/02/10 12:34:20  southa
 * Template fixes
 *
 * Revision 1.1  2005/02/03 15:46:57  southa
 * Quaternion work
 *
 */

#include "TesseractTrainerGame.h"

#include "TesseractTrainerHypercube.h"

#include "mushPlatform.h"
#include "mushMedia.h"
#include "mushMushGL.h"

using namespace Mushware;
using namespace std;

TesseractTrainerGame::TesseractTrainerGame() :
    m_inited(false),
    m_orientations(2),
    m_angVels(2),
    m_current(0),
    m_previous(1)
{
}

TesseractTrainerGame::~TesseractTrainerGame()
{}

void
TesseractTrainerGame::Process(GameAppHandler& inAppHandler)
{
    GameAppHandler& gameAppHandler = inAppHandler;
    tVal msecNow = gameAppHandler.MillisecondsGet();
    
    if (gameAppHandler.LatchedKeyStateTake('1'))
    {
        ++m_config.RenderFacesWRef();
        if (m_config.RenderFaces() == 9) m_config.RenderFacesSet(1);
    }
    
    if (gameAppHandler.LatchedKeyStateTake('2'))
    {
        m_config.RenderFaceOutlinesToggle();
    }
    
    if (gameAppHandler.LatchedKeyStateTake('3'))
    {
        m_config.RenderFaceTexturesToggle();
    }
    
    if (gameAppHandler.LatchedKeyStateTake('4'))
    {
        m_config.RenderFacePointsToggle();
    }
    
    if (gameAppHandler.LatchedKeyStateTake('5'))
    {
        m_config.RenderRotationPlanesToggle();
    }
    
    if (gameAppHandler.LatchedKeyStateTake('6'))
    {
        m_config.RenderBasicPlanesToggle();
    }
    
    if (gameAppHandler.LatchedKeyStateTake('s'))
    {
        m_config.RenderStereoToggle();
    }
    
    if (gameAppHandler.LatchedKeyStateTake('m'))
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
    
    if (gameAppHandler.LatchedKeyStateTake(' '))
    {
        for (MushcoreData<GameDialogue>::tIterator p =
             m_dialogues.Begin();
             p != m_dialogues.End(); ++p)
        {
            p->second->ExpireNow();
        }
    }
    
    if (gameAppHandler.LatchedKeyStateTake('k'))
    {
        NamedDialoguesAdd("^keyhelp");
    }    
    
    if (m_lastRegCheckMsec + kRegTimeMsec < msecNow)
    {
        if (!RegCheck())
        {
            gameAppHandler.RegModeEnter();
        }
        m_lastRegCheckMsec = msecNow;
    }    

    if (gameAppHandler.LatchedKeyStateTake('r'))
    {
        if (RegCheck())
        {
            NamedDialoguesAdd("^registered");
        }
        else
        {
            gameAppHandler.RegModeEnter();
        }
        m_lastRegCheckMsec = msecNow;
    }    
    
    if (gameAppHandler.LatchedKeyStateTake('-'))
    {
        if (m_modeKeypressMsec != 0)
        {
            m_newMode = PlatformVideoUtils::Sgl().PreviousModeDef(m_newMode);
        }
        m_modeKeypressMsec = msecNow;
    }
    if (gameAppHandler.LatchedKeyStateTake('='))
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
    
    GLUtils::PostRedisplay();
}

void
TesseractTrainerGame::Display(GameAppHandler& inAppHandler)
{    
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Sgl());
    tVal msecNow = gameAppHandler.MillisecondsGet();
    
    if (msecNow > m_lastChangeMsec + m_config.RotationChangeMsec() ||
        m_lastChangeMsec == 0 ||
        gameAppHandler.LatchedKeyStateTake('\013'))
    {
        Reorientate();
        m_lastChangeMsec = msecNow;
    }
    
    tVal proportion = (msecNow - m_lastChangeMsec) / m_config.RealignMsec();
    if (proportion > 1) proportion = 1;
    
    proportion = pow(sin(proportion * M_PI/2), 4);
    
    tQValPair orientation =
        MushMeshOps::SlerpNormalised(m_orientations[m_previous],
                                     m_orientations[m_current],
                                     proportion);
    tQValPair angVel =
        MushMeshOps::SlerpNormalised(m_angVels[m_previous],
                                     m_angVels[m_current],
                                     proportion);
    
    m_orientations[m_previous] = orientation;
    m_angVels[m_previous] = angVel;
    
    m_orientations[m_previous].OuterMultiplyBy(m_angVels[m_previous]);
    m_orientations[m_current].OuterMultiplyBy(m_angVels[m_current]);
    
    m_hypercube.OrientationSet(orientation);
    m_hypersphere.OrientationSet(orientation);
    m_planepair.OrientationSet(orientation);
    m_planeset.OrientationSet(orientation);
    
    GLUtils::DisplayPrologue();
    GLUtils::ClearScreen();
    
    if (m_config.RenderStereo())
    {
        RenderView(inAppHandler, -1.0);
        RenderView(inAppHandler, 1.0);
    }
    else
    {
        RenderView(inAppHandler, 0.0);
    }
    
    GLUtils::OrthoPrologue();
    
    std::vector<MushcoreData<GameDialogue>::tIterator> expiredDialogues;
    
    for (MushcoreData<GameDialogue>::tIterator p = m_dialogues.Begin();
            p != m_dialogues.End(); ++p)
    {
        p->second->Move();
        GLUtils::PushMatrix();
        p->second->Render();
        GLUtils::PopMatrix();
        if (p->second->ExpiredGet())
        {
            expiredDialogues.push_back(p);
        }
    }
    
    for (U32 i=0; i<expiredDialogues.size(); ++i)
    {
        m_dialogues.Delete(expiredDialogues[i]);
    }

    if (m_modeKeypressMsec != 0)
    {
        PlatformVideoUtils::Sgl().RenderModeInfo(m_newMode);
    }
    
    GLUtils::OrthoEpilogue();
    
    GLUtils::DisplayEpilogue();
}

void
TesseractTrainerGame::RenderView(GameAppHandler& inAppHandler, tVal inStereo)
{
    GLUtils::IdentityPrologue();
    
    GLUtils::PerspectiveLookAt(GLVector(m_config.StereoImageSeparation()*inStereo, 0, -m_config.ObjectDistance()), GLVector(m_config.StereoImageSeparation()*inStereo, 0, 0), 0);
    
    GLState::ColourSet(1.0,1.0,1.0,1.0);
    GLColour white(1,1,1,1);
    GLColour black(0,0,0,1);
    
    GLState::AmbientLightSet(0.1);
    GLState::LightingAlphaSet(1.0);
    
    U32 lightEnum = GL_LIGHT0;
    glLightfv(lightEnum, GL_AMBIENT, black.ArrayGet());
    glLightfv(lightEnum, GL_DIFFUSE, white.ArrayGet());
    glLightfv(lightEnum, GL_SPECULAR, white.ArrayGet());
    
    glLightf(lightEnum, GL_SPOT_CUTOFF, 180);
    
    GLfloat direction[3]={0,0,-1};
    glLightfv(lightEnum, GL_SPOT_DIRECTION, direction);
    glLightf(lightEnum, GL_SPOT_EXPONENT, 127);
    glLightf(lightEnum, GL_CONSTANT_ATTENUATION, 0.0001);
    glLightf(lightEnum, GL_LINEAR_ATTENUATION, 0);
    glLightf(lightEnum, GL_QUADRATIC_ATTENUATION, 0.08);
    
    GLfloat position[4]={0, 0, 2, 1};
    glLightfv(lightEnum, GL_POSITION, position);
    
    glEnable(lightEnum);
    
    GLUtils::CheckGLError();

    GLState::UseLightingSet(false);
    GLState::BlendSet(GLState::kBlendLine);
    GLState::ModulationSet(GLState::kModulationNone);

    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    
    glDisable(GL_MULTISAMPLE);
    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
    
    glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    glLineWidth(m_config.LineWidth());
    glPointSize(m_config.PointSize());
    
    GLState::TextureDisable();
    
    m_hypercube.RenderFacesSet(m_config.RenderFaces());
    m_hypercube.RenderFaceOutlinesSet(m_config.RenderFaceOutlines());
    m_hypercube.RenderFaceTexturesSet(m_config.RenderFaceTextures());

    m_hypersphere.RenderFacesSet(m_config.RenderFaces());
    
    if (m_config.RenderFacePoints()) m_hypersphere.Render(0);
    m_hypercube.Render(0);
    if (m_config.RenderRotationPlanes()) m_planepair.Render(0);
    if (m_config.RenderBasicPlanes()) m_planeset.Render(0);
    
    GLUtils::IdentityEpilogue();
}

void
TesseractTrainerGame::Reorientate(void)
{
    tVal ttRotationAMin = MushcoreEnv::Sgl().VariableGet("TT_ROTATION_A_MIN").ValGet();
    tVal ttRotationAMax = MushcoreEnv::Sgl().VariableGet("TT_ROTATION_A_MAX").ValGet();
    tVal ttRotationBMin = MushcoreEnv::Sgl().VariableGet("TT_ROTATION_B_MIN").ValGet();
    tVal ttRotationBMax = MushcoreEnv::Sgl().VariableGet("TT_ROTATION_B_MAX").ValGet();
    
    tQValPair orientation = MushMeshTools::RandomOrientation();
    
    std::swap(m_current, m_previous);
    
    m_orientations[m_current] = tQValPair::RotationIdentityGet();
    m_angVels[m_current] = tQValPair::RotationIdentityGet();
    
    m_angVels[m_current].OuterMultiplyBy(orientation);
    
    m_angVels[m_current].OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis
                             (0, MushMeshTools::Random(ttRotationAMin, ttRotationAMax)));
    m_angVels[m_current].OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis
                             (1, MushMeshTools::Random(ttRotationBMin, ttRotationBMax)));
    
    m_angVels[m_current].OuterMultiplyBy(orientation.ConjugateGet());
    
    m_planepair.Create(0, m_colours);
    m_planepair.Rotate(orientation.ConjugateGet());
}

void
TesseractTrainerGame::ScriptFunction(const std::string& inName, GameAppHandler& inAppHandler) const
{}

void
TesseractTrainerGame::Init(GameAppHandler& inAppHandler)
{
    m_config.DisplayModeSet(MushcoreEnv::Sgl().VariableGet("TT_DISPLAY_MODE").U32Get());
    
    m_colours.resize(8);

    for (U32 i=0; i<m_colours.size(); ++i)
    {
        std::ostringstream varName;
        varName << "TT_COLOUR_" << i;
        MushcoreScalar textValue = MushcoreEnv::Sgl().VariableGet(varName.str());
        std::istringstream strIStrm(textValue.StringGet());
        MushcoreXMLIStream xmlIStrm(strIStrm);
        
        xmlIStrm >> m_colours[i];
    }

    m_config.RotationChangeMsecSet(MushcoreEnv::Sgl().VariableGet("TT_ROTATION_CHANGE_MSEC").ValGet());
    m_config.RealignMsecSet(MushcoreEnv::Sgl().VariableGet("TT_REALIGN_MSEC").ValGet());
    m_config.LineWidthSet(MushcoreEnv::Sgl().VariableGet("TT_LINE_WIDTH").ValGet());
    m_config.PointSizeSet(MushcoreEnv::Sgl().VariableGet("TT_POINT_SIZE").ValGet());

    m_config.ObjectDistanceSet(MushcoreEnv::Sgl().VariableGet("TT_OBJECT_DISTANCE").ValGet());

    m_config.RenderFacesSet(MushcoreEnv::Sgl().VariableGet("TT_RENDER_FACES").U32Get());
    m_config.RenderFaceOutlinesSet(MushcoreEnv::Sgl().VariableGet("TT_RENDER_FACE_OUTLINES").U32Get());
    m_config.RenderFaceTexturesSet(MushcoreEnv::Sgl().VariableGet("TT_RENDER_FACE_TEXTURES").U32Get());
    m_config.RenderFacePointsSet(MushcoreEnv::Sgl().VariableGet("TT_RENDER_FACE_POINTS").U32Get());
    m_config.RenderRotationPlanesSet(MushcoreEnv::Sgl().VariableGet("TT_RENDER_ROTATION_PLANES").U32Get());
    m_config.RenderBasicPlanesSet(MushcoreEnv::Sgl().VariableGet("TT_RENDER_BASIC_PLANES").U32Get());

    m_config.RenderStereoSet(MushcoreEnv::Sgl().VariableGet("TT_RENDER_STEREO").U32Get());
    m_config.StereoEyeSeparationSet(MushcoreEnv::Sgl().VariableGet("TT_STEREO_EYE_SEPARATION").ValGet());
    m_config.StereoImageSeparationSet(MushcoreEnv::Sgl().VariableGet("TT_STEREO_IMAGE_SEPARATION").ValGet());
    m_config.PlayMusicSet(MushcoreEnv::Sgl().VariableGet("TT_PLAY_MUSIC").U32Get());
    
    
    const MushcoreScalar *pScalar;    
    if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "CONFIG_FILENAME"))
    {
        m_config.AutoFileIfExistsLoad(pScalar->StringGet());
    }

    if (MushcoreEnv::Sgl().VariableExists("TT_DUMP_MUSHGLV"))
    {
        std::cout << MushGLV::Sgl() << endl;
    }

    NamedDialoguesAdd("^start");
    if (RegCheck())
    {
        NamedDialoguesAdd("^registered");        
    }
    else
    {
        NamedDialoguesAdd("^unregistered");
    }
    
    MushcoreInterpreter::Sgl().Execute("loadsoundstream('tt-music1')");
    if (m_config.PlayMusic())
    {
        MediaAudio::Sgl().MusicFadeIn(300);                    
    }
    
    m_inited = true;
}

void
TesseractTrainerGame::SwapIn(GameAppHandler& inAppHandler)
{
    tVal msecNow = inAppHandler.MillisecondsGet();

    if (!m_inited)
    {
        Init(inAppHandler);
    }
    
    try
    {
        inAppHandler.EnterScreen(PlatformVideoUtils::Sgl().ModeDefGet(m_config.DisplayMode()));
        MushGLV::Sgl().Acquaint();
    }
    catch (...)
    {
        m_config.DisplayModeSet(0);
        throw;
    }
    
    GLUtils::CheckGLError();
    
    tVal ttFogStart = MushcoreEnv::Sgl().VariableGet("TT_FOG_START").ValGet();
    tVal ttFogEnd = MushcoreEnv::Sgl().VariableGet("TT_FOG_END").ValGet();
    
    float black[4] = {0,0,0,0};
    glFogfv(GL_FOG_COLOR, black);
    glFogf(GL_FOG_START, m_config.ObjectDistance() + ttFogStart);
    glFogf(GL_FOG_END, m_config.ObjectDistance() + ttFogEnd);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    
    m_lastChangeMsec = 0;
    m_lastRegCheckMsec = msecNow;
    m_modeKeypressMsec = 0;
    m_newMode = m_config.DisplayMode();

    m_hypercube.Create(0, m_colours);
    m_hypersphere.Create(0, m_colours);
    m_planepair.Create(0, m_colours);
    m_planeset.Create(0, m_colours);
    
    for (U32 i=0; i<2; ++i)
    {
        m_orientations[i] = tQValPair::RotationIdentityGet();
        m_angVels[i] = tQValPair::RotationIdentityGet();
    }
}

void
TesseractTrainerGame::SwapOut(GameAppHandler& inAppHandler)
{
    const MushcoreScalar *pScalar;    
    if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "CONFIG_FILENAME"))
    {
        m_config.AutoFileSave(pScalar->StringGet());
    }
}

bool
TesseractTrainerGame::RegCheck(void)
{
    bool success = false;
    
    std::string packageName = MushcoreInfo::Sgl().PackageNameGet();
    GameCode *pGameCode = MushcoreData<GameCode>::Sgl().GetOrCreate(packageName);
    
    if (GameUtils::CodeVerify(pGameCode->Code()))
    {
        success = true;
    }
    else
    {
        try
        {
            std::string filenameStr;
            const MushcoreScalar *pScalar;

            if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "REG_FILENAME"))
            {
                filenameStr = pScalar->StringGet();
                pGameCode->AutoFileIfExistsLoad(filenameStr);
            }
            if (GameUtils::CodeVerify(pGameCode->Code()))
            {
                success = true;
            }
        }
        catch (MushcoreNonFatalFail& e)
        {
            std::cerr << "Registration check failed: " << e.what() << std::endl;
        }
    }
    
    return success;
}

void
TesseractTrainerGame::NamedDialoguesAdd(const std::string& inRegExp)
{
    MushcoreRegExp regExp(inRegExp);
    for (MushcoreData<GameDialogue>::tIterator p = MushcoreData<GameDialogue>::Sgl().Begin();
         p != MushcoreData<GameDialogue>::Sgl().End(); ++p)
    {
        if (regExp.Search(p->first))
        {
            m_dialogues.Give(p->first, new GameDialogue(*p->second));
        }
    }   
}

//%outOfLineFunctions {

const char *TesseractTrainerGame::AutoNameGet(void) const
{
    return "TesseractTrainerGame";
}

MushcoreVirtualObject *TesseractTrainerGame::AutoClone(void) const
{
    return new TesseractTrainerGame(*this);
}

MushcoreVirtualObject *TesseractTrainerGame::AutoCreate(void) const
{
    return new TesseractTrainerGame;
}

MushcoreVirtualObject *TesseractTrainerGame::AutoVirtualFactory(void)
{
    return new TesseractTrainerGame;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("TesseractTrainerGame", TesseractTrainerGame::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
TesseractTrainerGame::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "orientations=" << m_orientations << ", ";
    ioOut << "angVels=" << m_angVels << ", ";
    ioOut << "current=" << m_current << ", ";
    ioOut << "previous=" << m_previous << ", ";
    ioOut << "colours=" << m_colours << ", ";
    ioOut << "lastChangeMsec=" << m_lastChangeMsec << ", ";
    ioOut << "lastRegCheckMsec=" << m_lastRegCheckMsec << ", ";
    ioOut << "modeKeypressMsec=" << m_modeKeypressMsec << ", ";
    ioOut << "newMode=" << m_newMode << ", ";
    ioOut << "dialogues=" << m_dialogues << ", ";
    ioOut << "config=" << m_config;
    ioOut << "]";
}
bool
TesseractTrainerGame::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "orientations")
    {
        ioIn >> m_orientations;
    }
    else if (inTagStr == "angVels")
    {
        ioIn >> m_angVels;
    }
    else if (inTagStr == "current")
    {
        ioIn >> m_current;
    }
    else if (inTagStr == "previous")
    {
        ioIn >> m_previous;
    }
    else if (inTagStr == "colours")
    {
        ioIn >> m_colours;
    }
    else if (inTagStr == "lastChangeMsec")
    {
        ioIn >> m_lastChangeMsec;
    }
    else if (inTagStr == "lastRegCheckMsec")
    {
        ioIn >> m_lastRegCheckMsec;
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
TesseractTrainerGame::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("orientations");
    ioOut << m_orientations;
    ioOut.TagSet("angVels");
    ioOut << m_angVels;
    ioOut.TagSet("current");
    ioOut << m_current;
    ioOut.TagSet("previous");
    ioOut << m_previous;
    ioOut.TagSet("colours");
    ioOut << m_colours;
    ioOut.TagSet("lastChangeMsec");
    ioOut << m_lastChangeMsec;
    ioOut.TagSet("lastRegCheckMsec");
    ioOut << m_lastRegCheckMsec;
    ioOut.TagSet("modeKeypressMsec");
    ioOut << m_modeKeypressMsec;
    ioOut.TagSet("newMode");
    ioOut << m_newMode;
    ioOut.TagSet("dialogues");
    ioOut << m_dialogues;
    ioOut.TagSet("config");
    ioOut << m_config;
}
//%outOfLineFunctions } vBC3u4fBe/aE1X55Ir2FUw
