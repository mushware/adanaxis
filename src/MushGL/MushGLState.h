//%includeGuardStart {
#ifndef MUSHGLSTATE_H
#define MUSHGLSTATE_H
//%includeGuardStart } qL9wXSwitdUiB2AgBoaA8A
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLState.h
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
//%Header } d/h1MgTijF1xZZlnCvknWQ
/*
 * $Id: MushGLState.h,v 1.3 2005/08/31 23:57:27 southa Exp $
 * $Log: MushGLState.h,v $
 * Revision 1.3  2005/08/31 23:57:27  southa
 * Texture coordinate work
 *
 * Revision 1.2  2005/07/06 19:08:26  southa
 * Adanaxis control work
 *
 * Revision 1.1  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 */

#include "MushGLStandard.h"

#include "MushGLVertexBuffer.h"

//:generate standard ostream xml1
class MushGLState : public MushcoreVirtualObject, public MushcoreSingleton<MushGLState>
{
public:
    typedef Mushware::U8 tState;
    enum
    {
        kStateFalse,
        kStateTrue,
        kStateDontCare,
        kStateNone
    };
    
    MushGLState();
    
    void ActiveTextureZeroBased(Mushware::U32 inTexNum);
    void ClientActiveTextureZeroBased(Mushware::U32 inTexNum);
    void TextureEnable2D(Mushware::U32 inTexNum);
    void TextureDisable2D(Mushware::U32 inTexNum);
    
    void ColourArrayDisable(void) { DisableClientState(m_colourArray, GL_COLOR_ARRAY); }
    void EdgeFlagArrayDisable(void) { DisableClientState(m_edgeFlagArray, GL_EDGE_FLAG_ARRAY); }
    void IndexArrayDisable(void) { DisableClientState(m_indexArray, GL_INDEX_ARRAY); }
    void NormalArrayDisable(void) { DisableClientState(m_normalArray, GL_NORMAL_ARRAY); }
    void TexCoordArrayDisable(Mushware::U32 inIndex) { DisableClientTextureState(inIndex); }
    void VertexArrayDisable(void) { DisableClientState(m_vertexArray, GL_VERTEX_ARRAY); }
        
    void ColourArraySetTrue(MushGLVertexBuffer<Mushware::t4GLVal>& ioBuffer);
    void TexCoordArraySetTrue(MushGLVertexBuffer<Mushware::t4GLVal>& ioBuffer, Mushware::U32 inIndex);
    void VertexArraySetTrue(MushGLVertexBuffer<Mushware::t4GLVal>& ioBuffer);
    
    void ArraysDisable(void);
    void TexturesDisable(void);
    
    void ResetWriteAll(void) { InvalidateAll(); Reset(); }
    void Reset(void);
    
protected:
    void DisableClientState(tState& ioStateVar, Mushware::U32 inGLState);
    void DisableClientTextureState(Mushware::U32 inIndex);
    void InvalidateAll();
    
private:
    void TextureStateGrow(Mushware::U32 inTexNum);
    void TextureArrayGrow(Mushware::U32 inTexNum);
    
    tState m_colourArray;
    tState m_edgeFlagArray;
    tState m_indexArray;
    tState m_normalArray;
    tState m_vertexArray;
    std::vector<tState> m_texCoordArrays;
    std::vector<tState> m_textureStates;
    Mushware::U32 m_activeTexNum;
    Mushware::U32 m_clientActiveTexNum;
    
//%classPrototypes {
public:
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 1oBgFruy5qHAaudtV+Hcmg
};

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGLState& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } fDBPEHo0FNe/dqIH6odASw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
