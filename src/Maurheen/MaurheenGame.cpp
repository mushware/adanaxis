//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenGame.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 1UTcekI/TccaPfXbPReOYw
/*
 * $Id: MaurheenGame.cpp,v 1.5 2004/10/31 23:34:06 southa Exp $
 * $Log: MaurheenGame.cpp,v $
 * Revision 1.5  2004/10/31 23:34:06  southa
 * Hypercube rendering test
 *
 * Revision 1.4  2004/09/20 21:50:47  southa
 * Added GLV
 *
 * Revision 1.3  2004/03/07 20:33:54  southa
 * Graphics tuning
 *
 * Revision 1.2  2004/03/07 12:05:56  southa
 * Rendering work
 *
 * Revision 1.1  2004/03/06 14:01:42  southa
 * Maurheen created
 *
 */

#include "MaurheenGame.h"

#include "MaurheenHypercube.h"
#include "MaurheenWorm.h"

#include "mushPlatform.h"
#include "mushMushGL.h"

using namespace Mushware;
using namespace std;

MaurheenGame::MaurheenGame()
{

}

MaurheenGame::~MaurheenGame()
{}

void
MaurheenGame::Process(GameAppHandler& inAppHandler)
{
    GLUtils::PostRedisplay();
}

void
MaurheenGame::Display(GameAppHandler& inAppHandler)
{
    
    GLUtils::DisplayPrologue();
    GLUtils::ClearScreen();
    GLUtils::IdentityPrologue();
    
    GLUtils::PerspectiveLookAt(GLVector(0,0,-4), GLVector(0,0,0), 0);
    
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Sgl());
    
    tVal msecNow = gameAppHandler.MillisecondsGet();
    
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
    
    //glRotated(msecNow/50, 0, 0, 1);
    //glRotated(msecNow/45, 0, 1, 0);
    //glRotated(msecNow/40, 1, 0, 0);

    GLState::UseLightingSet(false);
    GLState::BlendSet(GLState::kBlendLine);
    GLState::ModulationSet(GLState::kModulationNone);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    
    glDisable(GL_MULTISAMPLE);
    glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    glLineWidth(1.0);
    
    GLState::TextureDisable();
    //GLTextureRef texRef("font-system1");
    
    //GLState::BindTexture(texRef.TextureGet()->BindingNameGet());
    
    MaurheenHypercube hypercube;
    hypercube.Create(msecNow / 1000);
    hypercube.Render(msecNow / 1000);
    
    GLUtils::IdentityEpilogue();
    GLUtils::DisplayEpilogue();
}

void
MaurheenGame::ScriptFunction(const std::string& inName, GameAppHandler& inAppHandler) const
{}

void
MaurheenGame::SwapIn(GameAppHandler& inAppHandler)
{
    GLAppHandler& glAppHandler=dynamic_cast<GLAppHandler &>(MushcoreAppHandler::Sgl());
    glAppHandler.EnterScreen(PlatformVideoUtils::Sgl().ModeDefGet(13)); // 13
    MushGLV glv;
    glv.Acquaint();
}

void
MaurheenGame::SwapOut(GameAppHandler& inAppHandler)
{}


//%outOfLineFunctions {
const char *MaurheenGame::AutoNameGet(void) const
{
    return "MaurheenGame";
}
MaurheenGame *MaurheenGame::AutoClone(void) const
{
    return new MaurheenGame(*this);
}
MaurheenGame *MaurheenGame::AutoCreate(void) const
{
    return new MaurheenGame;
}
MushcoreVirtualObject *MaurheenGame::AutoVirtualFactory(void)
{
    return new MaurheenGame;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MaurheenGame", MaurheenGame::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MaurheenGame::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MaurheenGame::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else
    {
        return false;
    }
    return true;
}
void
MaurheenGame::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } SfHuX8OxfbXq+qZe7FVjog
