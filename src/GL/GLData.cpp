/*
 * $Id$
 * $Log$
 */

#include "GLData.hp"

GLData *GLData::m_instance=NULL;

TextureRef
GLData::AddTexture(GLTexture& inTexture)
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