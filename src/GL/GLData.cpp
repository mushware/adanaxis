/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GLData.cpp,v 1.19 2002/10/22 20:42:00 southa Exp $
 * $Log: GLData.cpp,v $
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
 * CoreXML and game map
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

using namespace Mushware;

GLData *GLData::m_instance=NULL;

GLData::GLData() :
    m_lights(NULL)
{
}

GLData::~GLData()
{
    for (map<string, GLTexture *>::iterator p = m_textures.begin();
        p != m_textures.end(); ++p)
    {
        delete p->second;
    }
    
    for (map<string, GLFont *>::iterator p = m_fonts.begin();
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
    map<string, GLTexture*>::iterator p = m_textures.find(inName);
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
    map<string, GLFont *>::iterator p = m_fonts.find(inName);
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
    map<string, GLFont *>::const_iterator p = m_fonts.find(inName);
    if (p == m_fonts.end())
    {
        throw(ReferenceFail("Access to non-existent font '"+inName+"'"));
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
    for (map<string, GLTexture *>::iterator p = m_textures.begin();
         p != m_textures.end(); ++p)
    {
        p->second->Decache();
    }
}

void
GLData::DumpTextures(ostream& inOut)
{
    for (map<string, GLTexture*>::iterator p = m_textures.begin();
         p != m_textures.end(); ++p)
    {
        inOut << p->first << ": " << *p->second << endl;
    }
}

    
