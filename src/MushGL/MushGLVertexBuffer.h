//%includeGuardStart {
#ifndef MUSHGLVERTEXBUFFER_H
#define MUSHGLVERTEXBUFFER_H
//%includeGuardStart } PX4eb7EQhquluaJJ52g+cA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLVertexBuffer.h
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
//%Header } IqSxvqRd3OSDd+9vhv6sYw
/*
 * $Id: MushGLVertexBuffer.h,v 1.13 2006/07/28 19:24:34 southa Exp $
 * $Log: MushGLVertexBuffer.h,v $
 * Revision 1.13  2006/07/28 19:24:34  southa
 * Pre-release work
 *
 * Revision 1.12  2006/06/30 15:05:34  southa
 * Texture and buffer purge
 *
 * Revision 1.11  2006/06/01 15:39:19  southa
 * DrawArray verification and fixes
 *
 * Revision 1.10  2006/05/11 10:43:16  southa
 * Project updates
 *
 * Revision 1.9  2005/09/03 17:05:36  southa
 * Material work
 *
 * Revision 1.8  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.7  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 * Revision 1.6  2005/05/19 13:02:09  southa
 * Mac release work
 *
 * Revision 1.5  2005/04/19 23:25:42  southa
 * Mode switching and recognition
 *
 * Revision 1.4  2005/04/10 00:09:23  southa
 * Registration
 *
 * Revision 1.3  2005/02/26 17:53:38  southa
 * Plane sets and pairs
 *
 * Revision 1.2  2005/02/10 12:34:04  southa
 * Template fixes
 *
 * Revision 1.1  2005/02/01 13:40:37  southa
 * Rotating spheres and hypercube
 *
 */

#include "MushGLStandard.h"

#include "MushGLV.h"

//:generate inline nonvirtual ostream xml1
template <class T>
class MushGLVertexBuffer
{
public:
    typedef T tVec;
    
    MushGLVertexBuffer();
    explicit MushGLVertexBuffer(const Mushware::tSize inSize);

public:
    
    virtual ~MushGLVertexBuffer();
    
    void Bind(void);
    void MapReadWrite();
    bool AttemptUnmap();
    
    tVec& Ref(const Mushware::tSize inIndex);
    void Set(const tVec& inValue, const Mushware::tSize inIndex);
    void *AddrForGLGet(const Mushware::tSize inIndex = 0);
    
    void ClearAndResize(const Mushware::tSize inSize);
    void Purge(void);

    GLuint GLName() const { return m_handle; }
    
private:  
    MushGLVertexBuffer(const MushGLVertexBuffer& inBuffer); // Prohibit copying
    MushGLVertexBuffer& operator=(const MushGLVertexBuffer& inBuffer); // Prohibit assignement
    void Validate(void);
    void Allocate(const Mushware::tSize inSize);
    void Deallocate();
    
    GLuint m_handle;
    bool m_isVertexBuffer; //:read
    bool m_mapped;
    bool m_allocated;
    Mushware::tSize m_size; //:read
    tVec *m_pData;
    Mushware::U32 m_contextNum;
    
public:
//%classPrototypes {
public:
    const bool& IsVertexBuffer(void) const { return m_isVertexBuffer; }
    const Mushware::tSize& Size(void) const { return m_size; }
    void AutoPrint(std::ostream& ioOut) const;
    bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } iPdNbJXyU5lCpczH82lmtw
};

template <class T>
inline
MushGLVertexBuffer<T>::MushGLVertexBuffer() :
    m_isVertexBuffer(false),
    m_mapped(false),
    m_allocated(false),
    m_size(0),
    m_pData(NULL),
    m_contextNum(0)
{
}

template <class T>
inline
MushGLVertexBuffer<T>::MushGLVertexBuffer(const Mushware::tSize inSize) :
    m_isVertexBuffer(false),
    m_mapped(false),
    m_allocated(false),
    m_size(0),
    m_pData(NULL),
    m_contextNum(0)
{
    Allocate(inSize);
}

template <class T>
inline
MushGLVertexBuffer<T>::~MushGLVertexBuffer()
{
    if (m_allocated)
    {
        Deallocate();
    }
}

template <class T>
inline void
MushGLVertexBuffer<T>::Allocate(const Mushware::tSize inSize)
{
    if (MushGLV::Sgl().UseVertexBuffer())
    {
        MushGLV::Sgl().GenBuffers(1, &m_handle);
        MushGLV::Sgl().BindBuffer(GL_ARRAY_BUFFER, m_handle);
        MushGLV::Sgl().BufferData(GL_ARRAY_BUFFER, inSize*sizeof(T), NULL, GL_DYNAMIC_DRAW);
        
        m_isVertexBuffer = true;
    }
    else
    {
        if (m_pData != NULL)
        {
            throw MushcoreLogicFail("MushGLVertexBuffer: Double allocation");
        }
        m_pData = new tVec[inSize];
    }
    m_size = inSize;
    m_allocated = true;
    m_contextNum = MushGLV::Sgl().ContextNum();
}

template <class T>
inline void
MushGLVertexBuffer<T>::Deallocate()
{
    if (m_isVertexBuffer)
    {
        if (m_contextNum == MushGLV::Sgl().ContextNum())
        {
            MushGLV::Sgl().DeleteBuffers(1, &m_handle);
        }
        else
        {
            // Mustn't delete if the context has changed, as the old buffers are already gone
            // and we might delete a new one
            MushcoreLog::Sgl().WarningLog() << "Couldn't delete buffer - context mismatch" << std::endl;
        }
    }
    else
    {
        if (m_pData == NULL)
        {
            throw MushcoreLogicFail("MushGLVertexBuffer: NULL deallocation");
        }
        delete[] m_pData;
    }
    
    m_pData = NULL;
    m_allocated = false;
    m_mapped = false;
    
}    

template <class T>
inline void
MushGLVertexBuffer<T>::Purge(void)
{
    if (m_allocated)
    {
        Deallocate();
    }
}

template <class T>
inline void
MushGLVertexBuffer<T>::Validate(void)
{
    if (!m_allocated)
    {
        Allocate(m_size);   
    }
    if (m_contextNum != MushGLV::Sgl().ContextNum())
    {
        MushcoreLog::Sgl().WarningLog() << "Reallocating vertex buffer - context mismatch" << std::endl;

        Deallocate();
        Allocate(m_size);
    }
}

template <class T>
inline void
MushGLVertexBuffer<T>::Bind(void)
{
    if (m_isVertexBuffer)
    {
        Validate();
        MushGLV::Sgl().BindBuffer(GL_ARRAY_BUFFER, m_handle);
    }
}

template <class T>
inline void
MushGLVertexBuffer<T>::MapReadWrite(void)
{
    if (m_mapped)
    {
        throw MushcoreLogicFail("MushGLVertexBuffer attempt to map buffer twice");
    }
    
    if (m_size == 0)
    {
        throw MushcoreLogicFail("MushGLVertexBuffer cannot map buffer of zero size");
    }
    
    if (m_isVertexBuffer)
    {
        Bind();
        T *pData;
        pData = reinterpret_cast<T *>(MushGLV::Sgl().MapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
        if (pData == NULL)
        {
            GLenum glErr = glGetError();
            
            // As we're indicating failure, don't leave the buffer mapped
            m_mapped = false;
            MushGLV::Sgl().UnmapBuffer(GL_ARRAY_BUFFER);
            
            if (glErr == GL_INVALID_OPERATION)
            {
                throw MushcoreRequestFail("MushGLVertexBuffer buffer already mapped");
            }
            else if (glErr == GL_OUT_OF_MEMORY)
            {
                m_pData = NULL;
                throw MushcoreDeviceFail("MushGLVertexBuffer cannot map buffer");
            }                
            else
            {
                m_pData = NULL;
                std::ostringstream message;
                message << "Bad result from glMapBuffer (" << std::hex << glErr << ")";
                throw MushcoreLogicFail(message.str());
            }                
        }
        m_pData = pData;
    }
    else
    {
        Validate();
    }
    m_mapped = true;
}

template <class T>
inline bool
MushGLVertexBuffer<T>::AttemptUnmap(void)
{
    bool success = true;
    
    if (!m_mapped)
    {
        throw MushcoreLogicFail("MushGLVertexBuffer buffer not mapped");
    }
    
    m_mapped = false;
    
    if (m_isVertexBuffer)
    {
        Bind();
        if (MushGLV::Sgl().UnmapBuffer(GL_ARRAY_BUFFER) != GL_TRUE)
        {
            success = false;
        }
    }
    return success;
}

template <class T>
inline typename MushGLVertexBuffer<T>::tVec&
MushGLVertexBuffer<T>::Ref(const Mushware::tSize inIndex)
{
    if (!m_mapped)
    {
        throw MushcoreLogicFail("MushGLVertexBuffer: Ref to unmapped buffer");
    }
    
    MushcoreUtil::BoundsCheck(inIndex, m_size);
    MUSHCOREASSERT(m_pData != NULL);
    return m_pData[inIndex];
}

template <class T>
inline void
MushGLVertexBuffer<T>::Set(const tVec& inValue, const Mushware::tSize inIndex)
{
    if (!m_mapped)
    {
        throw MushcoreLogicFail("MushGLVertexBuffer: Set on unmapped buffer");
    }
    MushcoreUtil::BoundsCheck(inIndex, m_size);
    MUSHCOREASSERT(m_pData != NULL);
    m_pData[inIndex] = inValue;
}

template <class T>
inline void *
MushGLVertexBuffer<T>::AddrForGLGet(const Mushware::tSize inIndex)
{
    if (m_mapped)
    {
        throw MushcoreLogicFail("MushGLVertexBuffer: AddrForGLGet on mapped buffer");
    }
    MUSHCOREASSERT(m_allocated);
    MushcoreUtil::BoundsCheck(inIndex, m_size);
    if (m_isVertexBuffer)
    {
        if (m_contextNum != MushGLV::Sgl().ContextNum())
        {
            throw MushcoreLogicFail("MushGLVertexBuffer: Buffer no longer valid in AddrForGLGet");
        }
        return reinterpret_cast<void *>(inIndex*sizeof(T));
    }
    else
    {
        MUSHCOREASSERT(m_pData != NULL);
        return &m_pData[inIndex];
    }
}

template <class T>
inline void
MushGLVertexBuffer<T>::ClearAndResize(const Mushware::tSize inSize)
{
    if (m_allocated)
    {
        Deallocate();
    }
    Allocate(inSize);
}

//%inlineHeader {
template <class T>
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGLVertexBuffer<T>& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
template <class T>
inline MushcoreXMLIStream&
operator>>(MushcoreXMLIStream& ioIn, MushGLVertexBuffer<T>& outObj)
{
    throw MushcoreDataFail("Cannot read XML object type 'MushGLVertexBuffer'");
    return ioIn;
}
template <class T>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const MushGLVertexBuffer<T>& inObj)
{
    inObj.AutoXMLPrint(ioOut);
    return ioOut;
}
template <class T>
inline void
MushGLVertexBuffer<T>::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "handle=" << m_handle << ", ";
    ioOut << "isVertexBuffer=" << m_isVertexBuffer << ", ";
    ioOut << "mapped=" << m_mapped << ", ";
    ioOut << "allocated=" << m_allocated << ", ";
    ioOut << "size=" << m_size << ", ";
    if (m_pData == NULL)
    {
        ioOut << "pData=NULL"  << ", ";
    }
    else
    {
        ioOut << "pData=" << *m_pData << ", ";
    }
    ioOut << "contextNum=" << m_contextNum;
    ioOut << "]";
}
template <class T>
inline bool
MushGLVertexBuffer<T>::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "handle")
    {
        ioIn >> m_handle;
    }
    else if (inTagStr == "isVertexBuffer")
    {
        ioIn >> m_isVertexBuffer;
    }
    else if (inTagStr == "mapped")
    {
        ioIn >> m_mapped;
    }
    else if (inTagStr == "allocated")
    {
        ioIn >> m_allocated;
    }
    else if (inTagStr == "size")
    {
        ioIn >> m_size;
    }
    else if (inTagStr == "pData")
    {
        ioIn >> m_pData;
    }
    else if (inTagStr == "contextNum")
    {
        ioIn >> m_contextNum;
    }
    else 
    {
        return false;
    }
    return true;
}
template <class T>
inline void
MushGLVertexBuffer<T>::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("handle");
    ioOut << m_handle;
    ioOut.TagSet("isVertexBuffer");
    ioOut << m_isVertexBuffer;
    ioOut.TagSet("mapped");
    ioOut << m_mapped;
    ioOut.TagSet("allocated");
    ioOut << m_allocated;
    ioOut.TagSet("size");
    ioOut << m_size;
    ioOut.TagSet("pData");
    ioOut << m_pData;
    ioOut.TagSet("contextNum");
    ioOut << m_contextNum;
}
//%inlineHeader } cUhwAoJ1+vgk3brL5mUrag

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
