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
 * $Id: TesseractTrainerGame.cpp,v 1.4 2005/02/26 17:53:44 southa Exp $
 * $Log: TesseractTrainerGame.cpp,v $
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

TesseractTrainerGame::TesseractTrainerGame()
{
}

TesseractTrainerGame::~TesseractTrainerGame()
{}

void
TesseractTrainerGame::Process(GameAppHandler& inAppHandler)
{
    GLUtils::PostRedisplay();
}

void
TesseractTrainerGame::Display(GameAppHandler& inAppHandler)
{
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Sgl());
    tVal msecNow = gameAppHandler.MillisecondsGet();
    
    GLUtils::DisplayPrologue();
    GLUtils::ClearScreen();
    GLUtils::IdentityPrologue();
    
    GLUtils::PerspectiveLookAt(GLVector(0,0,-4), GLVector(0,0,0), 0);
    
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
    glLineWidth(1.0);
    glPointSize(2.0);
    
    GLState::TextureDisable();
    //GLTextureRef texRef("font-system1");
    
    //GLState::BindTexture(texRef.TextureGet()->BindingNameGet());


    if (msecNow > m_lastChangeMsec + 30000 || m_lastChangeMsec == 0)
    {
        Reorientate();
        m_lastChangeMsec = msecNow;
    }
    
    m_orientation.OuterMultiplyBy(m_angVel);
    
    m_hypercube.OrientationSet(m_orientation);
    m_hypersphere.OrientationSet(m_orientation);
    m_planepair.OrientationSet(m_orientation);
    
    m_hypersphere.Render(0);
    m_hypercube.Render(0);
    m_planepair.Render(0);
    
    GLUtils::IdentityEpilogue();
    GLUtils::DisplayEpilogue();
}

void
TesseractTrainerGame::Reorientate(void)
{
    tQValPair orientation = MushMeshTools::RandomOrientation();
    
    m_orientation = tQValPair::RotationIdentityGet();
    m_angVel = tQValPair::RotationIdentityGet();
    
    m_angVel.OuterMultiplyBy(orientation);
    
    m_angVel.OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis
                             (0, MushMeshTools::Random(-0.03, 0.03)));
    m_angVel.OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis
                             (1, MushMeshTools::Random(-0.03, 0.03)));
    
    m_angVel.OuterMultiplyBy(orientation.ConjugateGet());
    
    m_planepair.Create(0, m_colours);
    m_planepair.Rotate(orientation.ConjugateGet());
}

void
TesseractTrainerGame::ScriptFunction(const std::string& inName, GameAppHandler& inAppHandler) const
{}

void
TesseractTrainerGame::SwapIn(GameAppHandler& inAppHandler)
{
    GLAppHandler& glAppHandler=dynamic_cast<GLAppHandler &>(MushcoreAppHandler::Sgl());
    glAppHandler.EnterScreen(PlatformVideoUtils::Sgl().ModeDefGet(13)); // 13
    MushGLV::Sgl().Acquaint();
    
    m_colours.resize(8);
    tVal alpha=0.2;
    m_colours[0] = t4GLVal(1.0,0.5,0.5,alpha);
    m_colours[1] = t4GLVal(0.5,0.5,0.5,alpha);
    m_colours[2] = t4GLVal(0.5,1.0,0.5,alpha);
    m_colours[3] = t4GLVal(0.5,0.5,0.5,alpha);
    m_colours[4] = t4GLVal(0.5,0.5,1.0,alpha);
    m_colours[5] = t4GLVal(0.5,0.5,0.5,alpha);
    m_colours[6] = t4GLVal(0.8,0.8,0.5,alpha);
    m_colours[7] = t4GLVal(0.5,0.5,0.5,alpha);
    
    m_hypercube.Create(0, m_colours);
    m_hypersphere.Create(0, m_colours);
    m_planepair.Create(0, m_colours);

    m_orientation = tQValPair::RotationIdentityGet();
    m_angVel = tQValPair::RotationIdentityGet();
    m_lastChangeMsec = 0;
    
    cout << MushGLV::Sgl() << endl;
}

void
TesseractTrainerGame::SwapOut(GameAppHandler& inAppHandler)
{}

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
    ioOut << "orientation=" << m_orientation << ", ";
    ioOut << "angVel=" << m_angVel << ", ";
    ioOut << "colours=" << m_colours << ", ";
    ioOut << "lastChangeMsec=" << m_lastChangeMsec;
    ioOut << "]";
}
bool
TesseractTrainerGame::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "orientation")
    {
        ioIn >> m_orientation;
    }
    else if (inTagStr == "angVel")
    {
        ioIn >> m_angVel;
    }
    else if (inTagStr == "colours")
    {
        ioIn >> m_colours;
    }
    else if (inTagStr == "lastChangeMsec")
    {
        ioIn >> m_lastChangeMsec;
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
    ioOut.TagSet("orientation");
    ioOut << m_orientation;
    ioOut.TagSet("angVel");
    ioOut << m_angVel;
    ioOut.TagSet("colours");
    ioOut << m_colours;
    ioOut.TagSet("lastChangeMsec");
    ioOut << m_lastChangeMsec;
}
//%outOfLineFunctions } flMJJ+2BTjbhl1h6X9U9lw
