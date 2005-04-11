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
 * $Id: TesseractTrainerGame.cpp,v 1.11 2005/04/10 00:09:23 southa Exp $
 * $Log: TesseractTrainerGame.cpp,v $
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
#include "mushMushGL.h"

using namespace Mushware;
using namespace std;

TesseractTrainerGame::TesseractTrainerGame() :
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
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Sgl());
    tVal msecNow = gameAppHandler.MillisecondsGet();
    
    if (gameAppHandler.LatchedKeyStateTake('1'))
    {
        ++m_ttRenderFaces;
        if (m_ttRenderFaces == 9) m_ttRenderFaces = 1;
    }
    
    if (gameAppHandler.LatchedKeyStateTake('2'))
    {
        m_ttRenderFaceOutlines = !m_ttRenderFaceOutlines;
    }
    
    if (gameAppHandler.LatchedKeyStateTake('3'))
    {
        m_ttRenderFaceTextures = !m_ttRenderFaceTextures;
    }
    
    if (gameAppHandler.LatchedKeyStateTake('4'))
    {
        m_ttRenderFacePoints = !m_ttRenderFacePoints;
    }
    
    if (gameAppHandler.LatchedKeyStateTake('5'))
    {
        m_ttRenderRotationPlanes = !m_ttRenderRotationPlanes;
    }
    
    if (gameAppHandler.LatchedKeyStateTake('6'))
    {
        m_ttRenderBasicPlanes = !m_ttRenderBasicPlanes;
    }
    
    if (gameAppHandler.LatchedKeyStateTake('s'))
    {
        m_ttRenderStereo = !m_ttRenderStereo;
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
    
    
    GLUtils::PostRedisplay();
}

void
TesseractTrainerGame::Display(GameAppHandler& inAppHandler)
{    
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Sgl());
    tVal msecNow = gameAppHandler.MillisecondsGet();
    
    if (msecNow > m_lastChangeMsec + m_ttRotationChangeMsec ||
        m_lastChangeMsec == 0 ||
        gameAppHandler.LatchedKeyStateTake('\013'))
    {
        Reorientate();
        m_lastChangeMsec = msecNow;
    }
    
    tVal proportion = (msecNow - m_lastChangeMsec) / m_ttRealignMsec;
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
    
    if (m_ttRenderStereo)
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

    GLUtils::OrthoEpilogue();
    
    GLUtils::DisplayEpilogue();
}

void
TesseractTrainerGame::RenderView(GameAppHandler& inAppHandler, tVal inStereo)
{
    
    GLUtils::IdentityPrologue();
    
    GLUtils::PerspectiveLookAt(GLVector(m_ttStereoImageSeparation*inStereo, 0, -m_ttObjectDistance), GLVector(m_ttStereoImageSeparation*inStereo, 0, 0), 0);
    
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
    glLineWidth(m_ttLineWidth);
    glPointSize(m_ttPointSize);
    
    GLState::TextureDisable();
    
    m_hypercube.RenderFacesSet(m_ttRenderFaces);
    m_hypercube.RenderFaceOutlinesSet(m_ttRenderFaceOutlines);
    m_hypercube.RenderFaceTexturesSet(m_ttRenderFaceTextures);

    m_hypersphere.RenderFacesSet(m_ttRenderFaces);
    
    if (m_ttRenderFacePoints) m_hypersphere.Render(0);
    m_hypercube.Render(0);
    if (m_ttRenderRotationPlanes) m_planepair.Render(0);
    if (m_ttRenderBasicPlanes) m_planeset.Render(0);
    
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
TesseractTrainerGame::SwapIn(GameAppHandler& inAppHandler)
{
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Sgl());
    gameAppHandler.EnterScreen(PlatformVideoUtils::Sgl().ModeDefGet(14)); // 14
    MushGLV::Sgl().Acquaint();

    tVal msecNow = gameAppHandler.MillisecondsGet();
    
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
    
    m_hypercube.Create(0, m_colours);
    m_hypersphere.Create(0, m_colours);
    m_planepair.Create(0, m_colours);
    m_planeset.Create(0, m_colours);

    for (U32 i=0; i<2; ++i)
    {
        m_orientations[i] = tQValPair::RotationIdentityGet();
        m_angVels[i] = tQValPair::RotationIdentityGet();
    }
    
    m_lastChangeMsec = 0;
    
    m_ttRotationChangeMsec = MushcoreEnv::Sgl().VariableGet("TT_ROTATION_CHANGE_MSEC").ValGet();
    m_ttRealignMsec = MushcoreEnv::Sgl().VariableGet("TT_REALIGN_MSEC").ValGet();
    m_ttLineWidth = MushcoreEnv::Sgl().VariableGet("TT_LINE_WIDTH").ValGet();
    m_ttPointSize = MushcoreEnv::Sgl().VariableGet("TT_POINT_SIZE").ValGet();
    
    m_ttObjectDistance = MushcoreEnv::Sgl().VariableGet("TT_OBJECT_DISTANCE").ValGet();

    tVal ttFogStart = MushcoreEnv::Sgl().VariableGet("TT_FOG_START").ValGet();
    tVal ttFogEnd = MushcoreEnv::Sgl().VariableGet("TT_FOG_END").ValGet();
    
    float black[4] = {0,0,0,0};
    glFogfv(GL_FOG_COLOR, black);
    glFogf(GL_FOG_START, m_ttObjectDistance + ttFogStart);
    glFogf(GL_FOG_END, m_ttObjectDistance + ttFogEnd);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    
    
    m_ttRenderFaces = MushcoreEnv::Sgl().VariableGet("TT_RENDER_FACES").U32Get();
    m_ttRenderFaceOutlines = MushcoreEnv::Sgl().VariableGet("TT_RENDER_FACE_OUTLINES").U32Get();
    m_ttRenderFaceTextures = MushcoreEnv::Sgl().VariableGet("TT_RENDER_FACE_TEXTURES").U32Get();
    m_ttRenderFacePoints = MushcoreEnv::Sgl().VariableGet("TT_RENDER_FACE_POINTS").U32Get();
    m_ttRenderRotationPlanes = MushcoreEnv::Sgl().VariableGet("TT_RENDER_ROTATION_PLANES").U32Get();
    m_ttRenderBasicPlanes  = MushcoreEnv::Sgl().VariableGet("TT_RENDER_BASIC_PLANES").U32Get();
    
    m_ttRenderStereo  = MushcoreEnv::Sgl().VariableGet("TT_RENDER_STEREO").U32Get();
    m_ttStereoEyeSeparation  = MushcoreEnv::Sgl().VariableGet("TT_STEREO_EYE_SEPARATION").ValGet();
    m_ttStereoImageSeparation  = MushcoreEnv::Sgl().VariableGet("TT_STEREO_IMAGE_SEPARATION").ValGet();
    
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
    
    m_lastRegCheckMsec = msecNow;
}

void
TesseractTrainerGame::SwapOut(GameAppHandler& inAppHandler)
{}

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

                std::ifstream codeFileStrm(filenameStr.c_str());
                if (codeFileStrm)
                {
                    MushcoreXMLIStream xmlIn(codeFileStrm);
                    
                    xmlIn >> *pGameCode;
                }
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
    ioOut << "dialogues=" << m_dialogues << ", ";
    ioOut << "ttRotationChangeMsec=" << m_ttRotationChangeMsec << ", ";
    ioOut << "ttRealignMsec=" << m_ttRealignMsec << ", ";
    ioOut << "ttLineWidth=" << m_ttLineWidth << ", ";
    ioOut << "ttPointSize=" << m_ttPointSize << ", ";
    ioOut << "ttObjectDistance=" << m_ttObjectDistance << ", ";
    ioOut << "ttRenderFaces=" << m_ttRenderFaces << ", ";
    ioOut << "ttRenderFaceOutlines=" << m_ttRenderFaceOutlines << ", ";
    ioOut << "ttRenderFaceTextures=" << m_ttRenderFaceTextures << ", ";
    ioOut << "ttRenderFacePoints=" << m_ttRenderFacePoints << ", ";
    ioOut << "ttRenderRotationPlanes=" << m_ttRenderRotationPlanes << ", ";
    ioOut << "ttRenderBasicPlanes=" << m_ttRenderBasicPlanes << ", ";
    ioOut << "ttRenderStereo=" << m_ttRenderStereo << ", ";
    ioOut << "ttStereoEyeSeparation=" << m_ttStereoEyeSeparation << ", ";
    ioOut << "ttStereoImageSeparation=" << m_ttStereoImageSeparation;
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
    else if (inTagStr == "dialogues")
    {
        ioIn >> m_dialogues;
    }
    else if (inTagStr == "ttRotationChangeMsec")
    {
        ioIn >> m_ttRotationChangeMsec;
    }
    else if (inTagStr == "ttRealignMsec")
    {
        ioIn >> m_ttRealignMsec;
    }
    else if (inTagStr == "ttLineWidth")
    {
        ioIn >> m_ttLineWidth;
    }
    else if (inTagStr == "ttPointSize")
    {
        ioIn >> m_ttPointSize;
    }
    else if (inTagStr == "ttObjectDistance")
    {
        ioIn >> m_ttObjectDistance;
    }
    else if (inTagStr == "ttRenderFaces")
    {
        ioIn >> m_ttRenderFaces;
    }
    else if (inTagStr == "ttRenderFaceOutlines")
    {
        ioIn >> m_ttRenderFaceOutlines;
    }
    else if (inTagStr == "ttRenderFaceTextures")
    {
        ioIn >> m_ttRenderFaceTextures;
    }
    else if (inTagStr == "ttRenderFacePoints")
    {
        ioIn >> m_ttRenderFacePoints;
    }
    else if (inTagStr == "ttRenderRotationPlanes")
    {
        ioIn >> m_ttRenderRotationPlanes;
    }
    else if (inTagStr == "ttRenderBasicPlanes")
    {
        ioIn >> m_ttRenderBasicPlanes;
    }
    else if (inTagStr == "ttRenderStereo")
    {
        ioIn >> m_ttRenderStereo;
    }
    else if (inTagStr == "ttStereoEyeSeparation")
    {
        ioIn >> m_ttStereoEyeSeparation;
    }
    else if (inTagStr == "ttStereoImageSeparation")
    {
        ioIn >> m_ttStereoImageSeparation;
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
    ioOut.TagSet("dialogues");
    ioOut << m_dialogues;
    ioOut.TagSet("ttRotationChangeMsec");
    ioOut << m_ttRotationChangeMsec;
    ioOut.TagSet("ttRealignMsec");
    ioOut << m_ttRealignMsec;
    ioOut.TagSet("ttLineWidth");
    ioOut << m_ttLineWidth;
    ioOut.TagSet("ttPointSize");
    ioOut << m_ttPointSize;
    ioOut.TagSet("ttObjectDistance");
    ioOut << m_ttObjectDistance;
    ioOut.TagSet("ttRenderFaces");
    ioOut << m_ttRenderFaces;
    ioOut.TagSet("ttRenderFaceOutlines");
    ioOut << m_ttRenderFaceOutlines;
    ioOut.TagSet("ttRenderFaceTextures");
    ioOut << m_ttRenderFaceTextures;
    ioOut.TagSet("ttRenderFacePoints");
    ioOut << m_ttRenderFacePoints;
    ioOut.TagSet("ttRenderRotationPlanes");
    ioOut << m_ttRenderRotationPlanes;
    ioOut.TagSet("ttRenderBasicPlanes");
    ioOut << m_ttRenderBasicPlanes;
    ioOut.TagSet("ttRenderStereo");
    ioOut << m_ttRenderStereo;
    ioOut.TagSet("ttStereoEyeSeparation");
    ioOut << m_ttStereoEyeSeparation;
    ioOut.TagSet("ttStereoImageSeparation");
    ioOut << m_ttStereoImageSeparation;
}
//%outOfLineFunctions } 6kErLUg8IcLC6qXNs4N7zA
