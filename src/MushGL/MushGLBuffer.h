//%includeGuardStart {
#ifndef MUSHGLBUFFER_H
#define MUSHGLBUFFER_H
//%includeGuardStart } 14ndRogKV1m4L55fic/KUw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLBuffer.h
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
//%Header } 7OpR3zTj9YNW6vQRFe5IfA
/*
 * $Id: MushGLBuffer.h,v 1.3 2005/02/01 13:40:37 southa Exp $
 * $Log: MushGLBuffer.h,v $
 * Revision 1.3  2005/02/01 13:40:37  southa
 * Rotating spheres and hypercube
 *
 * Revision 1.2  2005/01/29 18:27:31  southa
 * Vertex buffer stuff
 *
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
    if (m_mapped)
    {
        throw MushcoreLogicFail("MushGLBuffer attempt to map buffer twice");
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
                throw MushcoreRequestFail("MushGLBuffer buffer already mapped");
            }
            else if (glErr == GL_OUT_OF_MEMORY)
            {
                m_pData = NULL;
                throw MushcoreDeviceFail("MushGLBuffer cannot map buffer");
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
MushGLBuffer<T>::AttemptUnmap(void)
{
    bool success = true;
    
    if (!m_mapped)
    {
        throw MushcoreLogicFail("MushGLBuffer buffer not mapped");
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
