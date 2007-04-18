//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLFont.cpp
 *
 * Author: Andy Southgate 2002-2007
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } LobDilyfMhzXguRim9ttTw
/*
 * $Id: GLFont.cpp,v 1.24 2006/06/01 15:38:50 southa Exp $
 * $Log: GLFont.cpp,v $
 * Revision 1.24  2006/06/01 15:38:50  southa
 * DrawArray verification and fixes
 *
 * Revision 1.23  2005/05/19 13:01:58  southa
 * Mac release work
 *
 * Revision 1.22  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.21  2003/10/04 15:32:08  southa
 * Module split
 *
 * Revision 1.20  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.19  2003/08/21 23:08:20  southa
 * Fixed file headers
 *
 * Revision 1.18  2003/01/20 12:23:20  southa
 * Code and interface tidying
 *
 * Revision 1.17  2003/01/20 10:45:23  southa
 * Singleton tidying
 *
 * Revision 1.16  2003/01/13 14:31:54  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.15  2003/01/12 17:32:50  southa
 * Mushcore work
 *
 * Revision 1.14  2003/01/11 17:07:50  southa
 * Mushcore library separation
 *
 * Revision 1.13  2003/01/09 14:56:58  southa
 * Created Mushcore
 *
 * Revision 1.12  2003/01/07 17:13:40  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.11  2002/12/29 20:59:52  southa
 * More build fixes
 *
 * Revision 1.10  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.9  2002/10/22 20:42:00  southa
 * Source conditioning
 *
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
 * InfernalDialogue added
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
#include "GLRectangle.h"
#include "GLState.h"
#include "GLTexture.h"
#include "GLUtils.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller GLFontInstaller(GLFont::Install);

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
GLFont::RenderString(const string& inStr, tVal inAlign) const
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

MushcoreScalar
GLFont::LoadFontMap(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    string name;
    string filename;
    if (ioCommand.NumParams() < 2 || ioCommand.NumParams() > 6)
    {
        throw(MushcoreCommandFail("Usage: loadfontmap <name> <filename>"));
    }
    ioCommand.PopParam(name);
    ioCommand.PopParam(filename);
    MushcoreInterpreter::Sgl().Execute("loadpixmap('"+name+"','"+filename+"')");
    GLFont *font(new GLFont(name));
    GLData::Sgl().FontGive(name, font);
    U32 xNum(10),yNum(10);
    tVal xSize(256),ySize(256);
    ioCommand.PopParam(xNum);
    ioCommand.PopParam(yNum);
    ioCommand.PopParam(xSize);
    ioCommand.PopParam(ySize);
    font->ShapeSet(xNum, yNum);
    font->SizeSet(xSize, ySize);
    return MushcoreScalar(0);
}

void
GLFont::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("loadfontmap", LoadFontMap);
}
