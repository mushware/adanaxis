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
 * $Id$
 * $Log$
 */

#include "MushGLStandard.h"

template <class T>
class MushGLBuffer
{
public:
    typedef T tVec;
    
    MushGLBuffer();
    explicit MushGLBuffer(const Mushware::tSize inSize);
    virtual ~MushGLBuffer();
    
    bool DataMap();
    tVec& Ref(const Mushware::tSize inIndex);
    void Set(const tVec& inValue, const Mushware::tSize inIndex);
    void *AddrForGLGet(const Mushware::tSize inIndex = 0);
    bool AttemptRelease();
    
    void ClearAndResize(const Mushware::tSize inSize);
    
    GLuint GLName() const { return m_handle; }
    
private:
    MushGLBuffer(const MushGLBuffer& inBuffer) { throw MushcoreLogicFail("Forbiddden copy contructor"); }
    const MushGLBuffer& operator=(const MushGLBuffer& inBuffer) { throw MushcoreLogicFail("Forbiddden assignment"); }    
        
    void Allocate(const Mushware::tSize inSize);
    
    GLuint m_handle;
    Mushware::tSize m_size;
    tVec *m_pData;
};

template <class T>
inline
MushGLBuffer<T>::MushGLBuffer() :
    m_size(0),
    m_pData(NULL)
{
}

template <class T>
inline
MushGLBuffer<T>::MushGLBuffer(const Mushware::tSize inSize)
{
    m_pData = new tVec[inSize];
    m_size = inSize;
}

template <class T>
inline
MushGLBuffer<T>::~MushGLBuffer()
{
    if (m_pData != NULL)
    {
        delete[] m_pData;
    }
}

template <class T>
inline void
MushGLBuffer<T>::Allocate(const Mushware::tSize inSize)
{
    glBindBuffer(1, &m_handle);
    if (m_pData != NULL)
    {
        delete[] m_pData;
    }
    m_pData = new tVec[inSize];
    m_size = inSize;
}


template <class T>
inline typename MushGLBuffer<T>::tVec&
MushGLBuffer<T>::Ref(const Mushware::tSize inIndex)
{
    MushMeshUtils::BoundsCheck(inIndex, m_size);
    return m_pData[inIndex];
}

template <class T>
inline void
MushGLBuffer<T>::Set(const tVec& inValue, const Mushware::tSize inIndex)
{
    MushMeshUtils::BoundsCheck(inIndex, m_size);
    m_pData[inIndex] = inValue;
}

template <class T>
inline void *
MushGLBuffer<T>::AddrForGLGet(const Mushware::tSize inIndex)
{
    MushMeshUtils::BoundsCheck(inIndex, m_size);
    return &m_pData[inIndex];    
}

template <class T>
inline void
MushGLBuffer<T>::ClearAndResize(const Mushware::tSize inSize)
{
    if (m_pData != NULL)
    {
        delete[] m_pData;
    }
    m_pData = new tVec[inSize];
    m_size = inSize;
}


//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
