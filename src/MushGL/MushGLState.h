//%includeGuardStart {
#ifndef MUSHGLSTATE_H
#define MUSHGLSTATE_H
//%includeGuardStart } qL9wXSwitdUiB2AgBoaA8A
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLState.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } VgqnFfbosKoUu8n17D9mSg
/*
 * $Id: MushGLState.h,v 1.9 2006/09/07 16:38:51 southa Exp $
 * $Log: MushGLState.h,v $
 * Revision 1.9  2006/09/07 16:38:51  southa
 * Vertex shader
 *
 * Revision 1.8  2006/06/30 17:26:10  southa
 * Render prelude
 *
 * Revision 1.7  2006/06/26 17:03:13  southa
 * win32 installer tweaks
 *
 * Revision 1.6  2006/06/01 15:39:18  southa
 * DrawArray verification and fixes
 *
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

#include "MushGLShader.h"
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
        kRenderState2D,
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
    void ShaderDisable(void);
    
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
    MushGLShader::tDataRef m_standardShader;
    
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
