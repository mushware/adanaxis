/*
 * $Id$
 * $Log$
 */

#include "GLTexture.hp"

GLTexture::GLTexture(const string& inFilename)
{
    m_xSize=100;
    m_ySize=100;
    m_hBytes=m_xSize*4;
    m_data=new U8[m_ySize * m_hBytes];
    U8 col=0;
    for (Size i=0; i<sizeof(U32) * m_ySize * m_hBytes; i++)
    {
        m_data[i] = col++;
    }
}
