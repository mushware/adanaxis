//%includeGuardStart {
#ifndef MUSHGLVERTEXBUFFER_H
#define MUSHGLVERTEXBUFFER_H
//%includeGuardStart } PX4eb7EQhquluaJJ52g+cA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLVertexBuffer.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 8xLMG4RN55BtVXvugHCuFA
/*
 * $Id: MushGLVertexBuffer.h,v 1.2 2005/02/10 12:34:04 southa Exp $
 * $Log: MushGLVertexBuffer.h,v $
 * Revision 1.2  2005/02/10 12:34:04  southa
 * Template fixes
 *
 * Revision 1.1  2005/02/01 13:40:37  southa
 * Rotating spheres and hypercube
 *
 */

#include "MushGLStandard.h"

#include "MushGLV.h"

template <class T>
class MushGLVertexBuffer
{
public:
    typedef T tVec;
    
    MushGLVertexBuffer();
    explicit MushGLVertexBuffer(const Mushware::tSize inSize);
    MushGLVertexBuffer(const MushGLVertexBuffer& inBuffer) { throw MushcoreLogicFail("Forbiddden copy contructor"); }
    const MushGLVertexBuffer& operator=(const MushGLVertexBuffer& inBuffer) { throw MushcoreLogicFail("Forbiddden assignment"); }
    
    virtual ~MushGLVertexBuffer();
    
    void Bind(void);
    void MapReadWrite();
    bool AttemptUnmap();
    
    tVec& Ref(const Mushware::tSize inIndex);
    void Set(const tVec& inValue, const Mushware::tSize inIndex);
    void *AddrForGLGet(const Mushware::tSize inIndex = 0);
    
    void ClearAndResize(const Mushware::tSize inSize);
    
    GLuint GLName() const { return m_handle; }
    
private:  
    
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
MushGLVertexBuffer<T>::MushGLVertexBuffer() :
    m_isVertexBuffer(false),
    m_mapped(false),
    m_allocated(false),
    m_size(0),
    m_pData(NULL)
{
}

template <class T>
inline
MushGLVertexBuffer<T>::MushGLVertexBuffer(const Mushware::tSize inSize) :
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
}

template <class T>
inline void
MushGLVertexBuffer<T>::Deallocate()
{
    if (m_isVertexBuffer)
    {
        MushGLV::Sgl().DeleteBuffers(1, &m_handle);
    }
    else
    {
        if (m_pData == NULL)
        {
            throw MushcoreLogicFail("MushGLVertexBuffer: NULL deallocation");
        }
        delete[] m_pData;
    }
    m_allocated = false;
}    

template <class T>
inline void
MushGLVertexBuffer<T>::Bind(void)
{
    if (m_isVertexBuffer)
    {
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
    
    if (m_isVertexBuffer)
    {
        Bind();
        T *pData;
        pData = reinterpret_cast<T *>(MushGLV::Sgl().MapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
        if (pData == NULL)
        {
            GLenum glErr = glGetError();
            
            if (glErr == GL_INVALID_OPERATION)
            {
                // m_pData still valid
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
                throw MushcoreLogicFail("Bad result from glMapBuffer");
            }                
        }
        m_pData = pData;
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
        if (!MushGLV::Sgl().UnmapBuffer(GL_ARRAY_BUFFER))
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
    
    MushMeshUtils::BoundsCheck(inIndex, m_size);
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
    MushMeshUtils::BoundsCheck(inIndex, m_size);
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
    MushMeshUtils::BoundsCheck(inIndex, m_size);
    if (m_isVertexBuffer)
    {
        return reinterpret_cast<void *>(inIndex*sizeof(T));
    }
    else
    {
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

template <class T>
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGLVertexBuffer<T>& inObj)
{
    inObj.AutoPrint(ioOut);
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
