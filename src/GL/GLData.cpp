/*
 * $Id: GLData.cpp,v 1.4 2002/02/23 23:58:45 southa Exp $
 * $Log: GLData.cpp,v $
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

#include "GLData.hp"

GLData *GLData::m_instance=NULL;

GLData::~GLData()
{
    for (Size i=0; i<m_textures.size(); ++i)
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

const GLTexture&
GLData::GetTexture(const TextureRef& inRef)
{
    return *m_textures[inRef];
}
