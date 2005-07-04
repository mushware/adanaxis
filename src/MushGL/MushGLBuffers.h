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
 * $Id$
 * $Log$
 */

#include "MushGLStandard.h"

#include "MushGLVertexBuffer.h"

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
    
    typedef MushGLVertexBuffer<Mushware::t4GLVal> tVertexBuffer;
    typedef MushGLVertexBuffer<Mushware::t4GLVal> tColourBuffer;
    typedef MushGLVertexBuffer<Mushware::t4GLVal> tTexCoordBuffer;
    typedef MushcoreData<MushGLBuffers, Mushware::U32> tData;
    typedef MushcoreDataRef<MushGLBuffers, Mushware::U32> tDataRef;
    
    MushGLBuffers() : m_owner(kOwnerNone) {}
    virtual ~MushGLBuffers() {}

    void Claim(Mushware::U8 inOwner = kOwnerOther);
    void Release(Mushware::U8 inOwner = kOwnerOther);
    void Decache(void) {}
    
    static Mushware::U32 NextBufferNumAdvance(void) { return ++m_nextBufferNum; }
    
private:
    Mushware::U8 m_owner;
    tVertexBuffer m_vertexBuffer; //:read :wref
    tColourBuffer m_colourBuffer; //:read :wref
    std::vector<tTexCoordBuffer> m_texCoordBuffers; //:wref

    static Mushware::U32 m_nextBufferNum;
    
//%classPrototypes {
public:
    const tVertexBuffer& VertexBuffer(void) const { return m_vertexBuffer; }
    // Writable reference for m_vertexBuffer
    tVertexBuffer& VertexBufferWRef(void) { return m_vertexBuffer; }
    const tColourBuffer& ColourBuffer(void) const { return m_colourBuffer; }
    // Writable reference for m_colourBuffer
    tColourBuffer& ColourBufferWRef(void) { return m_colourBuffer; }
    // Writable reference for m_texCoordBuffers
    std::vector<tTexCoordBuffer>& TexCoordBuffersWRef(void) { return m_texCoordBuffers; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } Q1Md88FkC9CMnNLJdBTbGA
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
