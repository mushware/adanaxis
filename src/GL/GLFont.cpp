/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GLFont.cpp,v 1.8 2002/10/12 15:24:58 southa Exp $
 * $Log: GLFont.cpp,v $
 * Revision 1.8  2002/10/12 15:24:58  southa
 * Facet renderer
 *
 * Revision 1.7  2002/10/06 22:09:58  southa
 * Initial lighting test
 *
 * Revision 1.6  2002/08/27 08:56:19  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/21 10:12:21  southa
 * Time down counter
 *
 * Revision 1.4  2002/08/19 22:18:36  southa
 * Display of time differences
 *
 * Revision 1.3  2002/08/09 17:09:02  southa
 * GameDialogue added
 *
 * Revision 1.2  2002/08/08 18:20:29  southa
 * Plot on screen of dimension 1.0
 *
 * Revision 1.1  2002/08/08 13:39:09  southa
 * Text rendering
 *
 */

#include "GLFont.h"

#include "GLData.h"
#include "GLTexture.h"
#include "GLRectangle.h"
#include "GLUtils.h"
#include "GLState.h"

CoreInstaller GLFontInstaller(GLFont::Install);

GLFont::GLFont(const string& inName):
    m_name(inName),
    m_texRef(inName)
{
    // Monospaced only right now
    GLTexture *texMap(m_texRef.TextureGet());
    m_xMapSize=texMap->Width();
    m_yMapSize=texMap->Height();
}

void
GLFont::ShapeSet(U32 inXNum, U32 inYNum)
{
    m_xNum=inXNum;
    m_yNum=inYNum;
}

void
GLFont::SizeSet(tVal inXSize, tVal inYSize)
{
    m_xUsedSize=inXSize;
    m_yUsedSize=inYSize;
}

void
GLFont::RenderCharacter(U32 inChar) const
{
    if (inChar < 32 || inChar > 127)
    {
        static U32 warnings(0);
        if (++warnings < 5)
        {
            cerr << "Unrenderable character '" << static_cast<char>(inChar) << "' (" << inChar << ")" <<endl;
        }
    }
    tVal xstep=(m_xUsedSize/m_xMapSize)/m_xNum;
    tVal ystep=(m_yUsedSize/m_yMapSize)/m_yNum;
    tVal xPos=((inChar-32) % m_xNum)*xstep;
    tVal yPos=1-((inChar-32) / m_xNum)*ystep;
    GLRectangle rect=GLRectangle(xPos, yPos-ystep, xPos+xstep, yPos);
    GLState::BlendSet(GLState::kBlendTransparent);
    GLState::ModulationSet(GLState::kModulationColour);
    GLUtils::DrawSprite(*m_texRef.TextureGet(), rect);
}

void
GLFont::RenderString(const string& inStr, tVal inAlign=-1.0) const
{
    GLUtils gl;
    tVal length=StringLengthGet(inStr);
    tVal offset=(1+inAlign)*length/2;
    U32 size=inStr.size();
    for (U32 i=0; i<size; ++i)
    {
        // Characters are rendered with their centre at the position given
        gl.MoveTo(i+0.5-offset, 0);
        RenderCharacter(inStr[i]);
    }
    gl.MoveTo(0,0);
}

tVal
GLFont::StringLengthGet(const string& inStr) const
{
    return inStr.size();
}

CoreScalar
GLFont::LoadFontMap(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    string name;
    string filename;
    if (ioCommand.NumParams() < 2 || ioCommand.NumParams() > 6)
    {
        throw(CommandFail("Usage: loadfontmap <name> <filename>"));
    }
    ioCommand.PopParam(name);
    ioCommand.PopParam(filename);
    CoreApp::Instance().Process("loadpixmap('"+name+"','"+filename+"')");
    GLFont *font(new GLFont(name));
    GLData::Instance().FontGive(name, font);
    U32 xNum(10),yNum(10);
    tVal xSize(256),ySize(256);
    ioCommand.PopParam(xNum);
    ioCommand.PopParam(yNum);
    ioCommand.PopParam(xSize);
    ioCommand.PopParam(ySize);
    font->ShapeSet(xNum, yNum);
    font->SizeSet(xSize, ySize);
    return CoreScalar(0);
}

void
GLFont::Install(void)
{
    CoreApp::Instance().AddHandler("loadfontmap", LoadFontMap);
}
