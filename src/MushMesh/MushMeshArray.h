//%includeGuardStart {
#ifndef MUSHMESHARRAY_H
#define MUSHMESHARRAY_H
//%includeGuardStart } CYljICa3h+r4WSdWcHsDTw
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshArray.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } EEaZ1vjndQRXjGZYADcVMQ
/*
 * $Id: MushMeshArray.h,v 1.8 2003/10/19 12:41:42 southa Exp $
 * $Log: MushMeshArray.h,v $
 * Revision 1.8  2003/10/19 12:41:42  southa
 * Connectors
 *
 * Revision 1.7  2003/10/18 20:28:38  southa
 * Subdivision speed tests
 *
 * Revision 1.6  2003/10/18 12:58:38  southa
 * Subdivision implementation
 *
 * Revision 1.5  2003/10/17 19:33:10  southa
 * Mesh patches
 *
 * Revision 1.4  2003/10/17 12:27:18  southa
 * Line end fixes and more mesh work
 *
 * Revision 1.3  2003/10/15 12:26:58  southa
 * MushMeshArray neighbour testing and subdivision work
 *
 * Revision 1.2  2003/10/15 11:54:54  southa
 * MushMeshArray neighbour testing and subdivision
 *
 * Revision 1.1  2003/10/15 07:08:29  southa
 * MushMeshArray creation
 *
 */

#include "MushMeshStandard.h"
#include "MushMeshVector.h"
#include "MushMeshMath.h"

#define MUSHMESHARRAY_VERBOSE_DEBUG
#ifdef MUSHMESHARRAY_VERBOSE_DEBUG
#include "MushMeshSTL.h"
#endif

template <class T>
class MushMeshArray
{
public:
    MushMeshArray();
    MushMeshArray(Mushware::U32 inXSize, Mushware::U32 inYSize);
    const T& Get(Mushware::U32 inX, Mushware::U32 inY) const;
    const T& RefGet(Mushware::U32 inX, Mushware::U32 inY) const;
    const T& Get(const Mushware::t2U32& inPos) const;
    void Set(const T& inValue, Mushware::U32 inX, Mushware::U32 inY);
    void Set(const T& inValue, const Mushware::t2U32& inPos);
    const Mushware::t2U32 SizeGet(void) const;
    void SizeSet(const Mushware::t2U32& inSize);
    Mushware::U32 XSizeGet(void) const { return m_xSize; }
    Mushware::U32 YSizeGet(void) const { return m_ySize; }

    bool EqualIs(const MushMeshArray<T>& inObj) const;

    void Print(std::ostream& ioOut) const;

#ifndef HAVE_RESIZING_VALARRAY_ASSIGNMENT
    MushMeshArray<T>& operator=(const MushMeshArray<T>& inObj)
    {
        // With most compilers we must resize the valarray before assignment
        m_xSize = inObj.m_xSize;
        m_ySize = inObj.m_ySize;
        if (m_values.size() != inObj.m_values.size(), 1)
        {
            m_values.resize(0); // Prevent copies in the next resize
            m_values.resize(inObj.m_values.size()+300);
        }
        m_values = inObj.m_values;
        return *this;
    }
#endif

private:
    Mushware::U32 m_xSize;
    Mushware::U32 m_ySize;
    MushwareValarray<T> m_values;
};

template <class T>
MushMeshArray<T>::MushMeshArray() :
    m_xSize(0),
    m_ySize(0)
{
}

template <class T>
MushMeshArray<T>::MushMeshArray(Mushware::U32 inXSize, Mushware::U32 inYSize) :
    m_xSize(inXSize),
    m_ySize(inYSize),
    m_values(inXSize*inYSize)
{
}

template <class T>
inline const T&
MushMeshArray<T>::Get(Mushware::U32 inX, Mushware::U32 inY) const
{
#ifdef MUSHMESHARRAY_VERBOSE_DEBUG
    if (inX >= m_xSize || inY >= m_ySize)
    {
        std::ostringstream message;
        message << "MushMeshArray::Get failed: " << inX << ">=" << m_xSize << " || " << inY << ">=" << m_ySize;
        throw MushcoreLogicFail(message.str());
    }
#else
    MUSHCOREASSERT(inX < m_xSize && inY < m_ySize);
#endif
    return m_values[inX + m_xSize * inY];
}

template <class T>
inline const T&
MushMeshArray<T>::RefGet(Mushware::U32 inX, Mushware::U32 inY) const
{
#ifdef MUSHMESHARRAY_VERBOSE_DEBUG
    if (inX >= m_xSize || inY >= m_ySize)
    {
        std::ostringstream message;
        message << "MushMeshArray::RefGet failed: " << inX << ">=" << m_xSize << " || " << inY << ">=" << m_ySize;
        throw MushcoreLogicFail(message.str());
    }
#else
    MUSHCOREASSERT(inX < m_xSize && inY < m_ySize);
#endif
    return m_values[inX + m_xSize * inY];
}

template <class T>
inline const T&
MushMeshArray<T>::Get(const Mushware::t2U32& inPos) const
{
    return Get(inPos.X(), inPos.Y());
}

template <class T>
inline void
MushMeshArray<T>::Set(const T& inValue, Mushware::U32 inX, Mushware::U32 inY)
{
#ifdef MUSHMESHARRAY_VERBOSE_DEBUG
    if (inX >= m_xSize || inY >= m_ySize)
    {
        std::ostringstream message;
        message << "MushMeshArray::Set failed: " << inX << ">=" << m_xSize << " || " << inY << ">=" << m_ySize;
        throw MushcoreLogicFail(message.str());
    }
#else
    MUSHCOREASSERT(inX < m_xSize && inY < m_ySize);
#endif
    m_values[inX + m_xSize * inY] = inValue;
}

template <class T>
inline void
MushMeshArray<T>::Set(const T& inValue, const Mushware::t2U32& inPos)
{
    Set(inValue, inPos.X(), inPos.Y());
}

template <class T>
inline const Mushware::t2U32
MushMeshArray<T>::SizeGet(void) const
{
    return Mushware::t2U32(m_xSize, m_ySize);
}

template <class T>
inline void
MushMeshArray<T>::SizeSet(const Mushware::t2U32& inSize)
{
    if (Mushware::t2U32(m_xSize, m_ySize) != inSize)
    {
        //  This is a destructive resize.  No previous elements are copied
        m_values.resize(0); 
        m_xSize = inSize.X();
        m_ySize = inSize.Y();
        m_values.resize(m_xSize * m_ySize);
    }
}

template <class T>
inline bool
MushMeshArray<T>::EqualIs(const MushMeshArray<T>& inObj) const
{
    return (m_xSize == inObj.m_xSize) &&
           (m_ySize == inObj.m_ySize) &&
           MushMeshUtils::EqualIs(m_values, inObj.m_values); // Workaround for STL problem
}

template <class T>
inline void
MushMeshArray<T>::Print(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "xSize=" << m_xSize << ", ";
    ioOut << "ySize=" << m_ySize << ", ";
    ioOut << "values=" << m_values;
    ioOut << "]";
}

template <class T>
inline bool
operator==(const MushMeshArray<T>& a, const MushMeshArray<T>& b)
{
    return a.EqualIs(b);
}

template <class T>
inline bool
operator!=(const MushMeshArray<T>& a, const MushMeshArray<T>& b)
{
    return !a.EqualIs(b);
}

template <class T>
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshArray<T>& inObj)
{
    inObj.Print(ioOut);
    return ioOut;
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
