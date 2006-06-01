//%includeGuardStart {
#ifndef MUSHGLSTATE_H
#define MUSHGLSTATE_H
//%includeGuardStart } qL9wXSwitdUiB2AgBoaA8A
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLState.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } vFMISa2849VX/N6vU3bn2g
/*
 * $Id: MushGLState.h,v 1.5 2005/09/06 12:15:35 southa Exp $
 * $Log: MushGLState.h,v $
 * Revision 1.5  2005/09/06 12:15:35  southa
 * Texture and rendering work
 *
 * Revision 1.4  2005/09/05 17:14:23  southa
 * Solid rendering
 *
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
	typedef MushGLVertexBuffer<Mushware::t4GLVal> tColourArrayBuffer;
	typedef MushGLVertexBuffer<Mushware::tGLTexCoord> tTexCoordArrayBuffer;
	typedef MushGLVertexBuffer<Mushware::t4GLVal> tVertexArrayBuffer;
	
    enum
    {
        kStateFalse,
        kStateTrue,
        kStateDontCare,
        kStateNone
    };
    
    enum
    {
        kRenderState4D
    };
    
    MushGLState();
    
	bool ColourArray(void) const { return m_colourArray == kStateTrue; }
    bool EdgeFlagArray(void) const { return m_edgeFlagArray == kStateTrue; }
    bool IndexArray(void) const { return m_indexArray == kStateTrue; }
    bool NormalArray(void) const { return m_normalArray == kStateTrue; }
    bool VertexArray(void) const { return m_vertexArray == kStateTrue; }
    bool TexCoordArray(Mushware::U32 inIndex) const { MushcoreUtil::DebugBoundsCheck(inIndex, m_texCoordArrays.size()); return m_texCoordArrays[inIndex] == kStateTrue; }
    bool TextureState(Mushware::U32 inIndex) const { MushcoreUtil::DebugBoundsCheck(inIndex, m_textureStates.size()); return m_textureStates[inIndex] == kStateTrue; }
	
	Mushware::U32 NumTexCoordArrays(void) const { return m_texCoordArrays.size(); }
	Mushware::U32 NumTextureStates(void) const { return m_textureStates.size(); }
	
    void RenderStateSet(Mushware::U32 inRenderState);
    
    void ActiveTextureZeroBased(Mushware::U32 inTexNum);
    void ClientActiveTextureZeroBased(Mushware::U32 inTexNum);
    void TextureEnable2D(Mushware::U32 inTexNum);
    void TextureDisable2D(Mushware::U32 inTexNum);
    
    void ColourArrayDisable(void) { m_pCurrentColourBuffer = NULL; DisableClientState(m_colourArray, GL_COLOR_ARRAY); }
    void EdgeFlagArrayDisable(void) { DisableClientState(m_edgeFlagArray, GL_EDGE_FLAG_ARRAY); }
    void IndexArrayDisable(void) { DisableClientState(m_indexArray, GL_INDEX_ARRAY); }
    void NormalArrayDisable(void) { DisableClientState(m_normalArray, GL_NORMAL_ARRAY); }
    void TexCoordArrayDisable(Mushware::U32 inIndex) { m_pCurrentTexCoordBuffer = NULL; DisableClientTextureState(inIndex); }
    void VertexArrayDisable(void) { m_pCurrentVertexBuffer = NULL; DisableClientState(m_vertexArray, GL_VERTEX_ARRAY); }

    void ColourArraySetTrue(tColourArrayBuffer& ioBuffer);
    void TexCoordArraySetTrue(tTexCoordArrayBuffer& ioBuffer, Mushware::U32 inIndex);
    void VertexArraySetTrue(tVertexArrayBuffer& ioBuffer);
    
    void ArraysDisable(void);
    void TexturesDisable(void);
    
    void ResetWriteAll(void);
    void Reset(void);
    
	// Debug access
	tColourArrayBuffer *DebugColourBuffer(void) { return m_pCurrentColourBuffer; }
	tTexCoordArrayBuffer *DebugTexCoordBuffer(void) { return m_pCurrentTexCoordBuffer; }
	tVertexArrayBuffer *DebugVertexBuffer(void) { return m_pCurrentVertexBuffer; }
	
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
    
	// Debug variables
	tColourArrayBuffer *m_pCurrentColourBuffer;
	tTexCoordArrayBuffer *m_pCurrentTexCoordBuffer;
	tVertexArrayBuffer *m_pCurrentVertexBuffer;
	
//%classPrototypes {
public:
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } tO7bdQQzNBsFVPCMwFt0ng
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
