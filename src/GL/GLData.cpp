/*
 * $Id: GLData.cpp,v 1.7 2002/05/10 16:41:42 southa Exp $
 * $Log: GLData.cpp,v $
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
    for (tSize i=0; i<m_textures.size(); ++i)
    {
        delete m_textures[i];
    }
}

TextureRef
GLData::AddTexture(const GLTexture& inTexture)
{
    TextureRef ref=m_textures.size();
    m_textures.push_back(inTexture.Clone());
    return ref;
}

GLTexture&
GLData::GetTexture(const TextureRef& inRef)
{
    return *m_textures[inRef];
}
