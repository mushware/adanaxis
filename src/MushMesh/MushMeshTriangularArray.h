//%includeGuardStart {
#ifndef MUSHMESHTRIANGULARARRAY_H
#define MUSHMESHTRIANGULARARRAY_H
//%includeGuardStart } CFgyxFklArAzLRPExooCpg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshTriangularArray.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } yeuO0kZZevx142QRdFnXSQ
/*
 * $Id: MushMeshTriangularArray.h,v 1.1 2003/10/23 20:03:58 southa Exp $
 * $Log: MushMeshTriangularArray.h,v $
 * Revision 1.1  2003/10/23 20:03:58  southa
 * End mesh work
 *
 * Revision 1.9  2003/10/20 13:02:53  southa
 * Patch fixes and testing
 *
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

template <class T>
class MushMeshTriangularArray
{
public:
    MushMeshTriangularArray();
    MushMeshTriangularArray(Mushware::U32 inXSize, Mushware::U32 inOrder);
    const T& Get(Mushware::U32 inX, Mushware::U32 inY) const;
    const T& RefGet(Mushware::U32 inX, Mushware::U32 inY) const;
    const T& Get(const Mushware::t2U32& inPos) const;
    void Set(const T& inValue, Mushware::U32 inX, Mushware::U32 inY);
    void Set(const T& inValue, const Mushware::t2U32& inPos);
    const Mushware::t2U32 SizeGet(void) const;
    void SizeSet(const Mushware::t2U32& inSize);
    Mushware::U32 XSizeGet(void) const { return m_xSize; }
    Mushware::U32 OrderGet(void) const { return m_order; }

    bool EqualIs(const MushMeshTriangularArray<T>& inObj) const;

    void Print(std::ostream& ioOut) const;

#ifndef HAVE_RESIZING_VALARRAY_ASSIGNMENT
    MushMeshTriangularArray<T>& operator=(const MushMeshTriangularArray<T>& inObj)
    {
        // With most compilers we must resize the valarray before assignment
        m_xSize = inObj.m_xSize;
        m_order = inObj.m_order;
        if (m_values.size() != inObj.m_values.size())
        {
            m_values.resize(0); // Prevent copies in the next resize
            m_values.resize(inObj.m_values.size());
        }
        m_values = inObj.m_values;
        return *this;
    }
#endif

private:
    Mushware::U32 IndexGet(Mushware::U32 inX, Mushware::U32 inY) const;
    bool BoundsCheck(Mushware::U32 inX, Mushware::U32 inY) const;

    Mushware::U32 m_xSize;
    Mushware::U32 m_order;

    MushwareValarray<T> m_values;
};

template <class T>
MushMeshTriangularArray<T>::MushMeshTriangularArray() :
    m_xSize(0),
    m_order(0)
{
}

template <class T>
MushMeshTriangularArray<T>::MushMeshTriangularArray(Mushware::U32 inXSize, Mushware::U32 inOrder) :
    m_xSize(0),
    m_order(0)
{
        SizeSet(Mushware::t2U32(inXSize, inOrder));
}

template <class T>
inline Mushware::U32
MushMeshTriangularArray<T>::IndexGet(Mushware::U32 inX, Mushware::U32 inY) const
{
    return (m_order*(inX*(inX-1))) / 2 + inY;
}

template <class T>
inline bool
MushMeshTriangularArray<T>::BoundsCheck(Mushware::U32 inX, Mushware::U32 inY) const
{
    if (inX >= m_xSize || inY >= inX * m_order)
    {
        MushMeshUtils::BoundaryThrow(inX, m_xSize, inY, inX * m_order);
    }
    return true;
}

template <class T>
inline const T&
MushMeshTriangularArray<T>::Get(Mushware::U32 inX, Mushware::U32 inY) const
{
    MUSHCOREASSERT(BoundsCheck(inX, inY));
    MUSHCOREASSERT(IndexGet(inX, inY) < m_values.size());
    return m_values[IndexGet(inX, inY)];
}

template <class T>
inline const T&
MushMeshTriangularArray<T>::RefGet(Mushware::U32 inX, Mushware::U32 inY) const
{
    MUSHCOREASSERT(BoundsCheck(inX, inY));
    MUSHCOREASSERT(IndexGet(inX, inY) < m_values.size());
    return m_values[IndexGet(inX, inY)];
}

template <class T>
inline const T&
MushMeshTriangularArray<T>::Get(const Mushware::t2U32& inPos) const
{
    return Get(inPos.X(), inPos.Y());
}

template <class T>
inline void
MushMeshTriangularArray<T>::Set(const T& inValue, Mushware::U32 inX, Mushware::U32 inY)
{
    MUSHCOREASSERT(BoundsCheck(inX, inY));
    MUSHCOREASSERT(IndexGet(inX, inY) < m_values.size());
    m_values[IndexGet(inX, inY)] = inValue;
}

template <class T>
inline void
MushMeshTriangularArray<T>::Set(const T& inValue, const Mushware::t2U32& inPos)
{
    Set(inValue, inPos.X(), inPos.Y());
}

template <class T>
inline const Mushware::t2U32
MushMeshTriangularArray<T>::SizeGet(void) const
{
    return Mushware::t2U32(m_xSize, m_order);
}

template <class T>
inline void
MushMeshTriangularArray<T>::SizeSet(const Mushware::t2U32& inSize)
{
    if (Mushware::t2U32(m_xSize, m_order) != inSize)
    {
        //  This is a destructive resize.  No previous elements are copied
        m_values.resize(0); 
        m_xSize = inSize.X();
        m_order = inSize.Y();
        // Size happens to be the index value of the first element that we don't have
        m_values.resize(IndexGet(m_xSize, 0));
    }
}

template <class T>
inline bool
MushMeshTriangularArray<T>::EqualIs(const MushMeshTriangularArray<T>& inObj) const
{
    return (m_xSize == inObj.m_xSize) &&
           (m_order == inObj.m_order) &&
           MushMeshUtils::EqualIs(m_values, inObj.m_values); // Workaround for STL problem
}

template <class T>
inline void
MushMeshTriangularArray<T>::Print(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "xSize=" << m_xSize << ", ";
    ioOut << "order=" << m_order << ", ";
// FIXME!    ioOut << "values=" << m_values;
    ioOut << "]";
}

template <class T>
inline bool
operator==(const MushMeshTriangularArray<T>& a, const MushMeshTriangularArray<T>& b)
{
    return a.EqualIs(b);
}

template <class T>
inline bool
operator!=(const MushMeshTriangularArray<T>& a, const MushMeshTriangularArray<T>& b)
{
    return !a.EqualIs(b);
}

template <class T>
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshTriangularArray<T>& inObj)
{
    inObj.Print(ioOut);
    return ioOut;
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
