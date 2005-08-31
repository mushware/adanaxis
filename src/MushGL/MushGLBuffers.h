//%includeGuardStart {
#ifndef MUSHGLBUFFERS_H
#define MUSHGLBUFFERS_H
//%includeGuardStart } p34af5R27BoG6LKqDWQeKQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLBuffers.h
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
//%Header } DbBqjjQLEDRD5N83MupJQQ
/*
 * $Id: MushGLBuffers.h,v 1.3 2005/07/05 13:52:22 southa Exp $
 * $Log: MushGLBuffers.h,v $
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

//:generate standard ostream xml1
class MushGLBuffers : public MushcoreVirtualObject
{
public:
    enum
    {
        kOwnerInvalid,
        kOwnerNone,
        kOwnerMushGL,
        kOwnerOther
    };
    
    typedef Mushware::t4GLVal tVertex;
    typedef Mushware::t4GLVal tColour;
    typedef Mushware::t4GLVal tTexCoord;
    typedef MushGLVertexBuffer<tVertex> tVertexBuffer;
    typedef MushGLVertexBuffer<tColour> tColourBuffer;
    typedef MushGLVertexBuffer<tTexCoord> tTexCoordBuffer;
    typedef MushcoreData<MushGLBuffers, Mushware::U32> tData;
    typedef MushcoreDataRef<MushGLBuffers, Mushware::U32> tDataRef;
    
    MushGLBuffers() : m_owner(kOwnerNone) {}
    virtual ~MushGLBuffers() {}

    void Claim(Mushware::U8 inOwner = kOwnerOther);
    void Release(Mushware::U8 inOwner = kOwnerOther);
    void Decache(void) {}
    
    static Mushware::U32 NextBufferNumAdvance(void) { return ++m_nextBufferNum; }
    
    const tTexCoordBuffer& TexCoordBuffer(Mushware::U32 inIndex) const
        { MushcoreUtil::BoundsCheck(inIndex, m_texCoordBuffers.size()); return m_texCoordBuffers[inIndex]; }
    tTexCoordBuffer& TexCoordBufferWRef(Mushware::U32 inIndex)
        { MushcoreUtil::BoundsCheck(inIndex, m_texCoordBuffers.size()); return m_texCoordBuffers[inIndex]; }
    
private:
    Mushware::U8 m_owner;
    tVertexBuffer m_vertexBuffer; //:read :wref
    tColourBuffer m_colourBuffer; //:read :wref
    std::vector<tTexCoordBuffer> m_texCoordBuffers; //:read :wref

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
    const std::vector<tTexCoordBuffer>& TexCoordBuffers(void) const { return m_texCoordBuffers; }
    // Writable reference for m_texCoordBuffers
    std::vector<tTexCoordBuffer>& TexCoordBuffersWRef(void) { return m_texCoordBuffers; }
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
//%classPrototypes } /pPtQszfWVPWhV388tE0rw
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
