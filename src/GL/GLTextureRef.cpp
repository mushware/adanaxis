/*
 * $Id$
 * $Log$
 */

#include "GLTextureRef.h"
#include "GLData.h"

GLTexture *
GLTextureRef::TextureGet(void)
{
    if (m_texPtr == NULL)
    {
        GetReference();
    }
    return m_texPtr;
}

void
GLTextureRef::GetReference(void)
{

    m_texPtr=GLData::Instance().TextureFind(m_name);
    if (m_texPtr == NULL)
    {
        throw(LogicFail("Attempt to access non-existent texture '"+m_name+"'"));
    }
}

bool
GLTextureRef::Exists(void)
{
    return (m_texPtr != NULL || GLData::Instance().TextureFind(m_name) != NULL);
}
