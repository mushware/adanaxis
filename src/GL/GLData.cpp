/*
 * $Id: GLData.cpp,v 1.8 2002/05/24 18:10:43 southa Exp $
 * $Log: GLData.cpp,v $
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

GLData *GLData::m_instance=NULL;

GLData::~GLData()
{
    for (map<string, GLTexture *>::iterator p = m_textures.begin();
        p != m_textures.end(); ++p)
    {
        delete p->second;
    }
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

void
GLData::DumpTextures(ostream& inOut)
{
    for (map<string, GLTexture*>::iterator p = m_textures.begin();
         p != m_textures.end(); ++p)
    {
        inOut << p->first << ": " << *p->second << endl;
    }
}
    
    