/*
 * $Id: GLData.cpp,v 1.1 2002/02/18 22:04:37 southa Exp $
 * $Log: GLData.cpp,v $
 * Revision 1.1  2002/02/18 22:04:37  southa
 * Initial texture loading
 *
 */

#include "GLData.hp"

GLData *GLData::m_instance=NULL;

TextureRef
GLData::AddTexture(const GLTexture& inTexture)
{
    TextureRef ref=m_textures.size();
    m_textures.push_back(inTexture);
    return ref;
}

const GLTexture&
GLData::GetTexture(TextureRef& inRef)
{
    return m_textures.at(inRef);
}