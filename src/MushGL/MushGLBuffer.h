//%includeGuardStart {
#ifndef MUSHGLBUFFER_H
#define MUSHGLBUFFER_H
//%includeGuardStart } 14ndRogKV1m4L55fic/KUw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLBuffer.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } waDPLDx1sNWC9Sjn6VGwXw
/*
 * $Id: MushGLBuffer.h,v 1.1 2005/01/29 14:06:12 southa Exp $
 * $Log: MushGLBuffer.h,v $
 * Revision 1.1  2005/01/29 14:06:12  southa
 * OpenGL buffers and extensions
 *
 */

#include "MushGLStandard.h"

#include "MushGLV.h"

template <class T>
class MushGLBuffer
{
public:
    typedef T tVec;
    
    MushGLBuffer();
    explicit MushGLBuffer(const Mushware::tSize inSize);
    virtual ~MushGLBuffer();
    
    void Bind(void);
    void MapReadWrite();
    bool AttemptUnmap();
    
    tVec& Ref(const Mushware::tSize inIndex);
    void Set(const tVec& inValue, const Mushware::tSize inIndex);
    void *AddrForGLGet(const Mushware::tSize inIndex = 0);
    
    void ClearAndResize(const Mushware::tSize inSize);
    
    GLuint GLName() const { return m_handle; }
    
private:
    MushGLBuffer(const MushGLBuffer& inBuffer) { throw MushcoreLogicFail("Forbiddden copy contructor"); }
    const MushGLBuffer& operator=(const MushGLBuffer& inBuffer) { throw MushcoreLogicFail("Forbiddden assignment"); }    
        
    void Allocate(const Mushware::tSize inSize);
    void Deallocate();
    
    GLuint m_handle;
    bool m_isVertexBuffer;
    bool m_mapped;
    bool m_allocated;
    Mushware::tSize m_size;
    tVec *m_pData;

public:
    virtual void AutoPrint(std::ostream& ioOut) const;
};

template <class T>
inline
MushGLBuffer<T>::MushGLBuffer() :
    m_isVertexBuffer(false),
    m_mapped(false),
    m_allocated(false),
    m_size(0),
    m_pData(NULL)
{
}

template <class T>
inline
MushGLBuffer<T>::MushGLBuffer(const Mushware::tSize inSize) :
    m_isVertexBuffer(false),
    m_mapped(false),
    m_allocated(false),
    m_size(0),
    m_pData(NULL)
{
    Allocate(inSize);
}

template <class T>
inline
MushGLBuffer<T>::~MushGLBuffer()
{
    if (m_allocated)
    {
        Deallocate();
    }
}

template <class T>
inline void
MushGLBuffer<T>::Allocate(const Mushware::tSize inSize)
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
            throw MushcoreLogicFail("MushGLBuffer: Double allocation");
        }
        m_pData = new tVec[inSize];
    }
    m_size = inSize;
    m_allocated = true;
}

template <class T>
inline void
MushGLBuffer<T>::Deallocate()
{
    if (m_isVertexBuffer)
    {
        MushGLV::Sgl().DeleteBuffers(1, &m_handle);
    }
    else
    {
        if (m_pData == NULL)
        {
            throw MushcoreLogicFail("MushGLBuffer: NULL deallocation");
        }
        delete[] m_pData;
    }
    m_allocated = false;
}    

template <class T>
inline void
MushGLBuffer<T>::Bind(void)
{
    if (m_isVertexBuffer)
    {
        MushGLV::Sgl().BindBuffer(GL_ARRAY_BUFFER, m_handle);
    }
}

template <class T>
inline void
MushGLBuffer<T>::MapReadWrite(void)
{
    if (m_isVertexBuffer)
    {
        Bind();
        m_pData = MushGLV::Sgl().MapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
    }
    m_mapped = true;
}

template <class T>
inline bool
MushGLBuffer<T>::AttemptUnmap(void)
{
    if (m_isVertexBuffer)
    {
        Bind();
        if (MushGLV::Sgl().UnmapBuffer(GL_ARRAY_BUFFER))
        {
            m_mapped = false;
            return true;
        }
        else
        {
            return false;
        }
    }
    m_mapped = false;
    return true;
}

template <class T>
inline typename MushGLBuffer<T>::tVec&
MushGLBuffer<T>::Ref(const Mushware::tSize inIndex)
{
    if (!m_mapped)
    {
        throw MushcoreLogicFail("MushGLBuffer: Ref to unmapped buffer");
    }
    
    MushMeshUtils::BoundsCheck(inIndex, m_size);
    return m_pData[inIndex];
}

template <class T>
inline void
MushGLBuffer<T>::Set(const tVec& inValue, const Mushware::tSize inIndex)
{
    if (!m_mapped)
    {
        throw MushcoreLogicFail("MushGLBuffer: Set on unmapped buffer");
    }
    MushMeshUtils::BoundsCheck(inIndex, m_size);
    m_pData[inIndex] = inValue;
}

template <class T>
inline void *
MushGLBuffer<T>::AddrForGLGet(const Mushware::tSize inIndex)
{
    if (m_mapped)
    {
        throw MushcoreLogicFail("MushGLBuffer: AddrForGLGet on mapped buffer");
    }
    MushMeshUtils::BoundsCheck(inIndex, m_size);
    return &m_pData[inIndex];    
}

template <class T>
inline void
MushGLBuffer<T>::ClearAndResize(const Mushware::tSize inSize)
{
    if (m_allocated)
    {
        Deallocate();
    }
    Allocate(inSize);
}

template <class T>
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGLBuffer<T>& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}

template <class T>
inline void
MushGLBuffer<T>::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "handle=" << m_handle << ", ";
    ioOut << "isVertexBuffer=" << m_isVertexBuffer << ", ";
    ioOut << "mapped=" << m_mapped << ", ";
    ioOut << "allocated=" << m_allocated << ", ";
    ioOut << "size=" << m_size << ", ";
    if (m_pData == NULL)
    {
        ioOut << "pData=NULL" ;
    }
    else
    {
        ioOut << "pData=" << *m_pData;
    }
    ioOut << "]";
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
