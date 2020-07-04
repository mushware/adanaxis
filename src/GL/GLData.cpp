//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLData.cpp
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
//%Header } of+28vd1qc+oXrHnkt62XQ
/*
 * $Id: GLData.cpp,v 1.30 2006/06/01 15:38:50 southa Exp $
 * $Log: GLData.cpp,v $
 * Revision 1.30  2006/06/01 15:38:50  southa
 * DrawArray verification and fixes
 *
 * Revision 1.29  2005/05/19 13:01:58  southa
 * Mac release work
 *
 * Revision 1.28  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.27  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.26  2003/08/21 23:08:20  southa
 * Fixed file headers
 *
 * Revision 1.25  2003/02/05 17:06:35  southa
 * Build fixes
 *
 * Revision 1.24  2003/01/13 14:31:54  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.23  2003/01/12 17:32:49  southa
 * Mushcore work
 *
 * Revision 1.22  2003/01/09 14:56:58  southa
 * Created Mushcore
 *
 * Revision 1.21  2002/12/29 20:59:52  southa
 * More build fixes
 *
 * Revision 1.20  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.19  2002/10/22 20:42:00  southa
 * Source conditioning
 *
 * Revision 1.18  2002/10/15 14:02:29  southa
 * Mode changes
 *
 * Revision 1.17  2002/10/08 22:47:07  southa
 * Fixed initialisation bug
 *
 * Revision 1.16  2002/10/08 17:13:16  southa
 * Tiered maps
 *
 * Revision 1.15  2002/08/27 08:56:19  southa
 * Source conditioning
 *
 * Revision 1.14  2002/08/08 13:39:09  southa
 * Text rendering
 *
 * Revision 1.13  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.12  2002/07/19 15:44:39  southa
 * Graphic optimisations
 *
 * Revision 1.11  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.10  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.9  2002/05/28 16:37:39  southa
 * Texture references and decomposer
 *
 * Revision 1.8  2002/05/24 18:10:43  southa
 * MushcoreXML and game map
 *
 * Revision 1.7  2002/05/10 16:41:42  southa
 * Changed .hp files to .h
 *
 * Revision 1.6  2002/03/21 22:07:54  southa
 * Initial wrangle application handler
 *
 * Revision 1.5  2002/02/25 23:05:14  southa
 * Subclassed GLTexture
 *
 * Revision 1.4  2002/02/23 23:58:45  southa
 * Made buildable for cygwin
 *
 * Revision 1.3  2002/02/23 17:54:45  southa
 * Added GIF loader and GL tests
 *
 * Revision 1.2  2002/02/18 22:43:53  southa
 * First stage GIF loader
 *
 * Revision 1.1  2002/02/18 22:04:37  southa
 * Initial texture loading
 *
 */
  
#include "GLData.h"
#include "GLFont.h"
#include "GLLights.h"
#include "GLTexture.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

GLData *GLData::m_instance=NULL;

GLData::GLData() :
    m_lights(NULL)
{
}

GLData::~GLData()
{
    for (map<std::string, GLTexture *>::iterator p = m_textures.begin();
        p != m_textures.end(); ++p)
    {
        delete p->second;
    }
    
    for (map<std::string, GLFont *>::iterator p = m_fonts.begin();
         p != m_fonts.end(); ++p)
    {
        delete p->second;
    }
    if (m_lights != NULL) delete m_lights;
}

void
GLData::TextureAdd(const string& inName, const GLTexture& inTexture)
{
    if (m_textures.find(inName) != m_textures.end())
    {
        delete m_textures[inName];
    }
    m_textures[inName]=inTexture.Clone();
}

GLTexture * 
GLData::TextureFind(const string& inName)
{
    map<std::string, GLTexture*>::iterator p = m_textures.find(inName);
    if (p != m_textures.end())
    {
        return p->second;
    }
    else
    {
        return NULL;
    }
}

GLFont *
GLData::FontGive(const string& inName, GLFont *inFont)
{
    map<std::string, GLFont *>::iterator p = m_fonts.find(inName);
    if (p != m_fonts.end())
    {
        delete p->second;
        p->second=inFont;
    }
    else
    {
        m_fonts[inName]=inFont;
    }
    return inFont;
}

GLFont *
GLData::FontGet(const string& inName) const
{
    map<std::string, GLFont *>::const_iterator p = m_fonts.find(inName);
    if (p == m_fonts.end())
    {
        throw(MushcoreReferenceFail("Access to non-existent font '"+inName+"'"));
    }
    return p->second;
}

GLLights *
GLData::LightsGet(void)
{
    if (m_lights == NULL)
    {
        m_lights = new GLLights;
    }
    return m_lights;
}

void
GLData::Decache(void)
{
    for (map<std::string, GLTexture *>::iterator p = m_textures.begin();
         p != m_textures.end(); ++p)
    {
        p->second->Decache();
    }
}

void
GLData::DumpTextures(ostream& inOut)
{
    for (map<std::string, GLTexture*>::iterator p = m_textures.begin();
         p != m_textures.end(); ++p)
    {
        inOut << p->first << ": " << *p->second << endl;
    }
}

    
