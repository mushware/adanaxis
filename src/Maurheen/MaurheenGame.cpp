//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenGame.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } vigIDiudPK6DSPFpEVPovQ
/*
 * $Id: MaurheenGame.cpp,v 1.17 2006/06/01 15:39:11 southa Exp $
 * $Log: MaurheenGame.cpp,v $
 * Revision 1.17  2006/06/01 15:39:11  southa
 * DrawArray verification and fixes
 *
 * Revision 1.16  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.15  2005/06/20 14:30:35  southa
 * Adanaxis work
 *
 * Revision 1.14  2005/06/16 17:25:38  southa
 * Client/server work
 *
 * Revision 1.13  2005/05/19 13:02:07  southa
 * Mac release work
 *
 * Revision 1.12  2005/04/19 23:25:40  southa
 * Mode switching and recognition
 *
 * Revision 1.11  2005/02/10 12:34:02  southa
 * Template fixes
 *
 * Revision 1.10  2005/02/01 13:40:36  southa
 * Rotating spheres and hypercube
 *
 * Revision 1.9  2005/01/29 18:27:30  southa
 * Vertex buffer stuff
 *
 * Revision 1.8  2005/01/29 14:06:12  southa
 * OpenGL buffers and extensions
 *
 * Revision 1.7  2005/01/27 21:00:39  southa
 * Division and rendering
 *
 * Revision 1.6  2005/01/26 00:48:46  southa
 * MushMeshGroup and rendering
 *
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
    
    //glRotated(msecNow/50, 0, 0, 1);
    //glRotated(msecNow/45, 0, 1, 0);
    //glRotated(msecNow/40, 1, 0, 0);

    GLState::UseLightingSet(false);
    GLState::BlendSet(GLState::kBlendLine);
    GLState::ModulationSet(GLState::kModulationNone);

    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    
    glDisable(GL_MULTISAMPLE);
    glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    glLineWidth(1.0);
    glPointSize(2.0);
    
    GLState::TextureDisable();
    //GLTextureRef texRef("font-mono1");
    
    //GLState::BindTexture(texRef.TextureGet()->BindingNameGet());
    
    m_hypersphere.Render(msecNow / 2000);
    m_hypercube.Render(msecNow / 2000);
    
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
    MushGLV::Sgl().Acquaint();
    m_hypercube.Create(0);
    m_hypersphere.Create(0);

    cout << MushGLV::Sgl() << endl;
}

void
MaurheenGame::SwapOut(GameAppHandler& inAppHandler)
{}

//%outOfLineFunctions {

const char *MaurheenGame::AutoName(void) const
{
    return "MaurheenGame";
}

MushcoreVirtualObject *MaurheenGame::AutoClone(void) const
{
    return new MaurheenGame(*this);
}

MushcoreVirtualObject *MaurheenGame::AutoCreate(void) const
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
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
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
//%outOfLineFunctions } VD1k+zuJlUyUMXOXGGuiHw
