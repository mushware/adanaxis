//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLState.cpp
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } tWGKT6xf6h2OQMzlKKglYA
/*
 * $Id: MushGLState.cpp,v 1.2 2005/08/31 23:57:27 southa Exp $
 * $Log: MushGLState.cpp,v $
 * Revision 1.2  2005/08/31 23:57:27  southa
 * Texture coordinate work
 *
 * Revision 1.1  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 */

#include "MushGLState.h"

MUSHCORE_SINGLETON_INSTANCE(MushGLState);


MushGLState::MushGLState()
{
    InvalidateAll();
}

void
MushGLState::InvalidateAll(void)
{
    m_colourArray = kStateNone;
    m_edgeFlagArray = kStateNone;
    m_indexArray = kStateNone;
    m_normalArray = kStateNone;
    for (Mushware::U32 i=0; i<m_texCoordArrays.size(); ++i)
    {
        m_texCoordArrays[i] = kStateNone;
    }
    m_vertexArray = kStateNone;
    m_activeTexNum = ~0;
    m_clientActiveTexNum = ~0;
}

void
MushGLState::Reset(void)
{
    ArraysDisable();
    for (Mushware::U32 i=0; i<m_textureStates.size(); ++i)
    {
        TextureDisable2D(i);
    }
    ActiveTextureZeroBased(0);
    ClientActiveTextureZeroBased(0);
}

void
MushGLState::ActiveTextureZeroBased(Mushware::U32 inTexNum)
{
    if (m_activeTexNum != inTexNum)
    {
        MushGLV::Sgl().ActiveTextureZeroBased(inTexNum);
    }
    m_activeTexNum = inTexNum;
}

void
MushGLState::ClientActiveTextureZeroBased(Mushware::U32 inTexNum)
{
    if (m_clientActiveTexNum != inTexNum)
    {
        MushGLV::Sgl().ClientActiveTextureZeroBased(inTexNum);
    }
    m_clientActiveTexNum = inTexNum;
}

void
MushGLState::TextureStateGrow(Mushware::U32 inTexNum)
{
    if (inTexNum <= m_textureStates.size())
    {
        if (inTexNum >= MushGLV::Sgl().NumTextureUnits())
        {
            std::ostringstream message;
            message << "Texture number too high (" << inTexNum << " >= " << MushGLV::Sgl().NumTextureUnits() << ")";
            throw MushcoreRequestFail(message.str());
        }
        m_textureStates.resize(inTexNum+1, kStateNone);
    }
}

void
MushGLState::TextureEnable2D(Mushware::U32 inTexNum)
{
    TextureStateGrow(inTexNum);
    if (m_textureStates[inTexNum] != kStateTrue)
    {
        ActiveTextureZeroBased(inTexNum);
        glEnable(GL_TEXTURE_2D);
        m_textureStates[inTexNum] = kStateTrue;
    }
}    

void
MushGLState::TextureDisable2D(Mushware::U32 inTexNum)
{
    TextureStateGrow(inTexNum);
    if (m_textureStates[inTexNum] != kStateFalse)
    {
        ActiveTextureZeroBased(inTexNum);
        glDisable(GL_TEXTURE_2D);
        m_textureStates[inTexNum] = kStateFalse;
    }
}    

void
MushGLState::DisableClientState(Mushware::U8& ioStateVar, Mushware::U32 inGLState)
{
    if (ioStateVar != kStateFalse)
    {
        glDisableClientState(inGLState);
        ioStateVar = kStateFalse;
    }
}

void
MushGLState::TextureArrayGrow(Mushware::U32 inTexNum)
{
    if (inTexNum <= m_texCoordArrays.size())
    {
        if (inTexNum >= MushGLV::Sgl().NumTextureUnits())
        {
            std::ostringstream message;
            message << "Texture number too high (" << inTexNum << " >= " << MushGLV::Sgl().NumTextureUnits() << ")";
            throw MushcoreRequestFail(message.str());
        }
        m_texCoordArrays.resize(inTexNum+1, kStateNone);
    }
}

void
MushGLState::DisableClientTextureState(Mushware::U32 inTexNum)
{
    TextureArrayGrow(inTexNum);
    if (m_texCoordArrays[inTexNum] != kStateFalse)
    {
        ClientActiveTextureZeroBased(inTexNum);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
    m_texCoordArrays[inTexNum] = kStateFalse;
}

void
MushGLState::ColourArraySetTrue(MushGLVertexBuffer<Mushware::t4GLVal>& ioBuffer)
{
    ioBuffer.Bind();
    
    glColorPointer(4, MUSHGL_VALTYPE, 0, ioBuffer.AddrForGLGet());
    
    if (m_colourArray != kStateTrue)
    {
        glEnableClientState(GL_COLOR_ARRAY);
        m_colourArray = kStateTrue;
    }
}

void
MushGLState::TexCoordArraySetTrue(MushGLVertexBuffer<Mushware::t4GLVal>& ioBuffer, Mushware::U32 inTexNum)
{
    TextureArrayGrow(inTexNum);
    
    ActiveTextureZeroBased(inTexNum);
    ClientActiveTextureZeroBased(inTexNum);
    
    ioBuffer.Bind();
    
    glTexCoordPointer(2, MUSHGL_VALTYPE, 2, ioBuffer.AddrForGLGet());
    
    MUSHCOREASSERT(inTexNum < m_texCoordArrays.size());
    
    if (m_texCoordArrays[inTexNum] != kStateTrue)
    {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        m_texCoordArrays[inTexNum] = kStateTrue;
    }
}

void
MushGLState::VertexArraySetTrue(MushGLVertexBuffer<Mushware::t4GLVal>& ioBuffer)
{
    ioBuffer.Bind();
    
    glVertexPointer(4, MUSHGL_VALTYPE, 0, ioBuffer.AddrForGLGet());
    
    if (m_vertexArray != kStateTrue)
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        m_vertexArray = kStateTrue;
    }
}

void
MushGLState::ArraysDisable(void)
{
    ColourArrayDisable();
    EdgeFlagArrayDisable();
    IndexArrayDisable();
    NormalArrayDisable();
    for (Mushware::U32 i=0; i<m_texCoordArrays.size(); ++i)
    {
        TexCoordArrayDisable(i);
    }
    VertexArrayDisable();
}

void
MushGLState::TexturesDisable(void)
{
    for (Mushware::U32 i=0; i<m_textureStates.size(); ++i)
    {
        TextureDisable2D(i);
    }
}

//%outOfLineFunctions {

const char *MushGLState::AutoName(void) const
{
    return "MushGLState";
}

MushcoreVirtualObject *MushGLState::AutoClone(void) const
{
    return new MushGLState(*this);
}

MushcoreVirtualObject *MushGLState::AutoCreate(void) const
{
    return new MushGLState;
}

MushcoreVirtualObject *MushGLState::AutoVirtualFactory(void)
{
    return new MushGLState;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLState", MushGLState::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLState::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "colourArray=" << m_colourArray << ", ";
    ioOut << "edgeFlagArray=" << m_edgeFlagArray << ", ";
    ioOut << "indexArray=" << m_indexArray << ", ";
    ioOut << "normalArray=" << m_normalArray << ", ";
    ioOut << "vertexArray=" << m_vertexArray << ", ";
    ioOut << "texCoordArrays=" << m_texCoordArrays << ", ";
    ioOut << "textureStates=" << m_textureStates << ", ";
    ioOut << "activeTexNum=" << m_activeTexNum << ", ";
    ioOut << "clientActiveTexNum=" << m_clientActiveTexNum;
    ioOut << "]";
}
bool
MushGLState::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "colourArray")
    {
        ioIn >> m_colourArray;
    }
    else if (inTagStr == "edgeFlagArray")
    {
        ioIn >> m_edgeFlagArray;
    }
    else if (inTagStr == "indexArray")
    {
        ioIn >> m_indexArray;
    }
    else if (inTagStr == "normalArray")
    {
        ioIn >> m_normalArray;
    }
    else if (inTagStr == "vertexArray")
    {
        ioIn >> m_vertexArray;
    }
    else if (inTagStr == "texCoordArrays")
    {
        ioIn >> m_texCoordArrays;
    }
    else if (inTagStr == "textureStates")
    {
        ioIn >> m_textureStates;
    }
    else if (inTagStr == "activeTexNum")
    {
        ioIn >> m_activeTexNum;
    }
    else if (inTagStr == "clientActiveTexNum")
    {
        ioIn >> m_clientActiveTexNum;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGLState::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("colourArray");
    ioOut << m_colourArray;
    ioOut.TagSet("edgeFlagArray");
    ioOut << m_edgeFlagArray;
    ioOut.TagSet("indexArray");
    ioOut << m_indexArray;
    ioOut.TagSet("normalArray");
    ioOut << m_normalArray;
    ioOut.TagSet("vertexArray");
    ioOut << m_vertexArray;
    ioOut.TagSet("texCoordArrays");
    ioOut << m_texCoordArrays;
    ioOut.TagSet("textureStates");
    ioOut << m_textureStates;
    ioOut.TagSet("activeTexNum");
    ioOut << m_activeTexNum;
    ioOut.TagSet("clientActiveTexNum");
    ioOut << m_clientActiveTexNum;
}
//%outOfLineFunctions } 2GhLUqy6+S5xHfcvSi3sMA
