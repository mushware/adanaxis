//%includeGuardStart {
#ifndef MUSHMESHARRAY_H
#define MUSHMESHARRAY_H
//%includeGuardStart } CYljICa3h+r4WSdWcHsDTw
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshArray.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } JKW5aY4a2V8htk/x1VVeQg
/*
 * $Id: MushMeshArray.h,v 1.18 2006/06/01 15:39:29 southa Exp $
 * $Log: MushMeshArray.h,v $
 * Revision 1.18  2006/06/01 15:39:29  southa
 * DrawArray verification and fixes
 *
 * Revision 1.17  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.16  2005/05/19 13:02:09  southa
 * Mac release work
 *
 * Revision 1.15  2005/02/03 15:46:51  southa
 * Quaternion work
 *
 * Revision 1.14  2004/03/07 12:05:56  southa
 * Rendering work
 *
 * Revision 1.13  2004/01/08 16:06:11  southa
 * XML fixes
 *
 * Revision 1.12  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.11  2004/01/01 21:15:46  southa
 * Created XCode project
 *
 * Revision 1.10  2003/10/23 20:03:57  southa
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
    T& WRefGet(Mushware::U32 inX, Mushware::U32 inY);
    const T& Get(const Mushware::t2U32& inPos) const;
    const T *DataPtrGet(Mushware::U32 inX, Mushware::U32 inY) const;
    const T *DataPtrGet(const Mushware::t2U32& inPos) const;
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
inline T&
MushMeshArray<T>::WRefGet(Mushware::U32 inX, Mushware::U32 inY)
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
inline const T *
MushMeshArray<T>::DataPtrGet(Mushware::U32 inX, Mushware::U32 inY) const
{
#ifdef MUSHMESHARRAY_VERBOSE_DEBUG
    if (inX >= m_xSize || inY >= m_ySize)
    {
        std::ostringstream message;
        message << "MushMeshArray::DataPtrGet failed: " << inX << ">=" << m_xSize << " || " << inY << ">=" << m_ySize;
        throw MushcoreLogicFail(message.str());
    }
#else
    MUSHCOREASSERT(inX < m_xSize && inY < m_ySize);
#endif
    return &m_values[inX + m_xSize * inY];
}

template <class T>
inline const T *
MushMeshArray<T>::DataPtrGet(const Mushware::t2U32& inPos) const
{
    return DataPtrGet(inPos.X(), inPos.Y());
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
    if (m_values.size() != inObj.m_values.size())
    {
        return false;
    }
    
    for (Mushware::U32 i=0; i < m_values.size(); ++i)
    {
        if (m_values[i] != inObj.m_values[i])
        {
            return false;
        }
    }
    
    return ((m_xSize == inObj.m_xSize) &&
        (m_ySize == inObj.m_ySize));
}

template <class T>
inline void
MushMeshArray<T>::Print(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "xSize=" << m_xSize << ", ";
    ioOut << "ySize=" << m_ySize << ", ";
    //FIXME ioOut << "values=" << m_values;
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
