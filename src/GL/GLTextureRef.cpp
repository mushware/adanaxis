/*
 * $Id: GLTextureRef.cpp,v 1.2 2002/06/04 17:02:24 southa Exp $
 * $Log: GLTextureRef.cpp,v $
 * Revision 1.2  2002/06/04 17:02:24  southa
 * More work
 *
 * Revision 1.1  2002/05/28 16:37:39  southa
 * Texture references and decomposer
 *
 */

#include "GLTextureRef.h"
#include "GLData.h"

GLTexture *
GLTextureRef::TextureGet(void) const
{
    if (m_texPtr == NULL)
    {
        GetReference();
    }
    return m_texPtr;
}

void
GLTextureRef::GetReference(void) const
{
    m_texPtr=GLData::Instance().TextureFind(m_name);
    if (m_texPtr == NULL)
    {
        throw(LogicFail("Attempt to access non-existent texture '"+m_name+"'"));
    }
}

bool
GLTextureRef::Exists(void) const
{
    return (m_texPtr != NULL || GLData::Instance().TextureFind(m_name) != NULL);
}
