//%includeGuardStart {
#ifndef MUSHGLBUFFERS_H
#define MUSHGLBUFFERS_H
//%includeGuardStart } p34af5R27BoG6LKqDWQeKQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLBuffers.h
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
//%Header } vIsa5TJY+2Ht+MrhZsy5rg
/*
 * $Id: MushGLBuffers.h,v 1.9 2006/06/30 15:05:33 southa Exp $
 * $Log: MushGLBuffers.h,v $
 * Revision 1.9  2006/06/30 15:05:33  southa
 * Texture and buffer purge
 *
 * Revision 1.8  2006/06/01 15:39:17  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/09/06 12:15:35  southa
 * Texture and rendering work
 *
 * Revision 1.6  2005/09/05 12:54:30  southa
 * Solid rendering work
 *
 * Revision 1.5  2005/09/03 17:05:36  southa
 * Material work
 *
 * Revision 1.4  2005/08/31 23:57:27  southa
 * Texture coordinate work
 *
 * Revision 1.3  2005/07/05 13:52:22  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 */

#include "MushGLStandard.h"

#include "MushGLVertexBuffer.h"
#include "MushGLWorkspace.h"

//:generate standard ostream xml1 nocopy
class MushGLBuffers : public MushcoreVirtualObject
{
public:
    enum
    {
        kOwnerInvalid,
        kOwnerNone,
        kOwnerMushGL,
        kOwnerOther,
        kNumTexCoordBuffers = 8
    };
    
    typedef Mushware::t4GLVal tVertex;
    typedef Mushware::t4GLVal tColour;
    typedef Mushware::tGLTexCoord tTexCoord;
    typedef MushGLVertexBuffer<tVertex> tVertexBuffer;
    typedef MushGLVertexBuffer<tColour> tColourBuffer;
    typedef MushGLVertexBuffer<tTexCoord> tTexCoordBuffer;
    typedef tTexCoordBuffer tTexCoordBuffers[kNumTexCoordBuffers];
    typedef std::vector<Mushware::U32> tTriangleList;
    
    typedef MushcoreData<MushGLBuffers, Mushware::U32> tData;
    typedef MushcoreDataRef<MushGLBuffers, Mushware::U32> tDataRef;
    typedef MushcoreData<MushGLBuffers> tSharedData;
    typedef MushcoreDataRef<MushGLBuffers> tSharedDataRef;
    
    MushGLBuffers() :
        m_owner(kOwnerNone),
        m_numTexCoordBuffers(0),
        m_vertexContextNum(0),
        m_colourContextNum(0),
        m_texCoordContextNum(0),
        m_triangleListContextNum(0)
    {}
    virtual ~MushGLBuffers() {}
    
    void NumTexCoordBuffersSet(const Mushware::U32& inValue)
    {
        if (inValue >= kNumTexCoordBuffers)
        {
            throw MushcoreLogicFail("Request for too many texture coordinates");
        }
        m_numTexCoordBuffers=inValue;
    }
    
    void Claim(Mushware::U8 inOwner = kOwnerOther);
    void Release(Mushware::U8 inOwner = kOwnerOther);
    void Decache(void) {}
    
    void Purge(void);
    
    static Mushware::U32 NextBufferNumAdvance(void) { return ++m_nextBufferNum; }
    
    const tTexCoordBuffer& TexCoordBuffer(Mushware::U32 inIndex) const
        { MushcoreUtil::BoundsCheck(inIndex, m_numTexCoordBuffers); return m_texCoordBuffers[inIndex]; }
    tTexCoordBuffer& TexCoordBufferWRef(Mushware::U32 inIndex)
        { MushcoreUtil::BoundsCheck(inIndex, m_numTexCoordBuffers); return m_texCoordBuffers[inIndex]; }
    
private:
    Mushware::U8 m_owner;
    tVertexBuffer m_vertexBuffer; //:read :wref
    tColourBuffer m_colourBuffer; //:read :wref
    tTexCoordBuffers m_texCoordBuffers; //:read :wref :xmlignore
    Mushware::U32 m_numTexCoordBuffers; //:read
    tTriangleList m_vertexTriangleList; //:read :wref
    tTriangleList m_texCoordTriangleList; //:read :wref
    
    Mushware::U32 m_vertexContextNum; //:readwrite
    Mushware::U32 m_colourContextNum; //:readwrite
    Mushware::U32 m_texCoordContextNum; //:readwrite
    Mushware::U32 m_triangleListContextNum; //:readwrite
    
    MushGLWorkspace<tVertex> m_worldVertices; //:read :wref
    MushGLWorkspace<tVertex> m_eyeVertices; //:read :wref
    MushGLWorkspace<tVertex> m_projectedVertices; //:read :wref
    
    static Mushware::U32 m_nextBufferNum;
    
//%classPrototypes {
public:
    const tVertexBuffer& VertexBuffer(void) const { return m_vertexBuffer; }
    // Writable reference for m_vertexBuffer
    tVertexBuffer& VertexBufferWRef(void) { return m_vertexBuffer; }
    const tColourBuffer& ColourBuffer(void) const { return m_colourBuffer; }
    // Writable reference for m_colourBuffer
    tColourBuffer& ColourBufferWRef(void) { return m_colourBuffer; }
    const tTexCoordBuffers& TexCoordBuffers(void) const { return m_texCoordBuffers; }
    // Writable reference for m_texCoordBuffers
    tTexCoordBuffers& TexCoordBuffersWRef(void) { return m_texCoordBuffers; }
    const Mushware::U32& NumTexCoordBuffers(void) const { return m_numTexCoordBuffers; }
    const tTriangleList& VertexTriangleList(void) const { return m_vertexTriangleList; }
    // Writable reference for m_vertexTriangleList
    tTriangleList& VertexTriangleListWRef(void) { return m_vertexTriangleList; }
    const tTriangleList& TexCoordTriangleList(void) const { return m_texCoordTriangleList; }
    // Writable reference for m_texCoordTriangleList
    tTriangleList& TexCoordTriangleListWRef(void) { return m_texCoordTriangleList; }
    const Mushware::U32& VertexContextNum(void) const { return m_vertexContextNum; }
    void VertexContextNumSet(const Mushware::U32& inValue) { m_vertexContextNum=inValue; }
    const Mushware::U32& ColourContextNum(void) const { return m_colourContextNum; }
    void ColourContextNumSet(const Mushware::U32& inValue) { m_colourContextNum=inValue; }
    const Mushware::U32& TexCoordContextNum(void) const { return m_texCoordContextNum; }
    void TexCoordContextNumSet(const Mushware::U32& inValue) { m_texCoordContextNum=inValue; }
    const Mushware::U32& TriangleListContextNum(void) const { return m_triangleListContextNum; }
    void TriangleListContextNumSet(const Mushware::U32& inValue) { m_triangleListContextNum=inValue; }
    const MushGLWorkspace<tVertex>& WorldVertices(void) const { return m_worldVertices; }
    // Writable reference for m_worldVertices
    MushGLWorkspace<tVertex>& WorldVerticesWRef(void) { return m_worldVertices; }
    const MushGLWorkspace<tVertex>& EyeVertices(void) const { return m_eyeVertices; }
    // Writable reference for m_eyeVertices
    MushGLWorkspace<tVertex>& EyeVerticesWRef(void) { return m_eyeVertices; }
    const MushGLWorkspace<tVertex>& ProjectedVertices(void) const { return m_projectedVertices; }
    // Writable reference for m_projectedVertices
    MushGLWorkspace<tVertex>& ProjectedVerticesWRef(void) { return m_projectedVertices; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 6JhyED29uNQef7FgFLuVIQ
};

inline void
MushGLBuffers::Claim(Mushware::U8 inOwner)
{
    if (m_owner != kOwnerNone)
    {
        std::ostringstream message;
        message << inOwner;
        throw MushcoreRequestFail(std::string("Cannot claim ownership of '")+AutoName()+"' (owner is "+message.str()+")");
    }
    m_owner = inOwner;
}

inline void
MushGLBuffers::Release(Mushware::U8 inOwner)
{
    if (m_owner != inOwner)
    {
        throw MushcoreRequestFail(std::string("Cannot release ownership of '")+AutoName()+"' - not owner");
    }
    m_owner = kOwnerNone;
}

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGLBuffers& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } hApmqKc8J0tzYpk+qEeDlA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
