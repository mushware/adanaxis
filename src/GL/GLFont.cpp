/*
 * $Id$
 * $Log$
 */

#include "GLFont.h"

#include "GLData.h"
#include "GLTexture.h"
#include "GLRectangle.h"
#include "GLUtils.h"

CoreInstaller GLFontInstaller(GLFont::Install);

GLFont::GLFont(const string& inName):
    m_name(inName),
    m_texRef(inName)
{
    cerr << "Constructing font using " << inName << endl;
    // Monospaced only right now
    GLTexture *texMap(m_texRef.TextureGet());
    cerr << "Texture: " << *texMap << endl;
    m_xstep=texMap->Width()/8;
    m_ystep=texMap->Height()/12;
}

void
GLFont::RenderCharacter(U32 inChar) const
{
    if (inChar < 32 || inChar > 127)
    {
        static U32 warnings(0);
        if (++warnings < 5)
        {
            cerr << "Unrenderable character '" << static_cast<char>(inChar) << "'" <<endl;
        }
    }
    tVal xstep=(340.0/512.0)/8.0;
    tVal ystep=(768.0/1024.0)/12.0;
    tVal xPos=((inChar-32) % 8)*xstep;
    tVal yPos=1-((inChar-32) / 8)*ystep;
    GLRectangle rect=GLRectangle(xPos, yPos-ystep, xPos+xstep, yPos);
    GLUtils::BlendSet(GLUtils::kBlendTransparent);
    GLUtils::ModulateSet(true);
    GLUtils::DrawSprite(*m_texRef.TextureGet(), rect);
}

void
GLFont::RenderString(const string& inStr) const
{
    GLUtils gl;
    U32 size=inStr.size();
    for (U32 i=0; i<size; ++i)
    {
        gl.MoveTo(i*1.1, 0);
        RenderCharacter(inStr[i]);
    }
    gl.MoveTo(0,0);
}

CoreScalar
GLFont::LoadFontMap(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    string name;
    string filename;
    if (ioCommand.NumParams() != 2)
    {
        throw(CommandFail("Usage: loadfontmap <name> <filename>"));
    }
    ioCommand.PopParam(name);
    ioCommand.PopParam(filename);
    CoreApp::Instance().Process("loadpixmap('"+name+"','"+filename+"')");
    GLFont *font(new GLFont(name));
    GLData::Instance().FontGive(name, font);
    return CoreScalar(0);
}

void
GLFont::Install(void)
{
    CoreApp::Instance().AddHandler("loadfontmap", LoadFontMap);
}
