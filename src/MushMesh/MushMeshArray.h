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
 * $Id: MushMeshArray.h,v 1.3 2003/10/15 12:26:58 southa Exp $
 * $Log: MushMeshArray.h,v $
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
class MushMeshArray
{
public:
    enum
    {
        kMaxVerts = 6
    };
    
    MushMeshArray(Mushware::U32 inXSize, Mushware::U32 inYSize);
    const T& Get(Mushware::U32 inX, Mushware::U32 inY) const;
    const T& RefGet(Mushware::U32 inX, Mushware::U32 inY) const;
    void Set(const T& inValue, Mushware::U32 inX, Mushware::U32 inY);
    const Mushware::t2U32 SizeGet(void) const;
    void SizeSet(const Mushware::t2U32& inSize);
    Mushware::U32 XSizeGet(void) const { return m_xSize; }
    Mushware::U32 YSizeGet(void) const { return m_ySize; }

    void VertexNeighboursGet(MushwareValarray<const T *>& outVerts, Mushware::U32& outSize, Mushware::U32 inX, Mushware::U32 inY) const;

    bool EqualIs(const MushMeshArray<T>& inObj) const;

    void Print(std::ostream& ioOut) const;

private:
    Mushware::U32 m_xSize;
    Mushware::U32 m_ySize;
    Mushware::U32 m_xSizeSub1;
    Mushware::U32 m_ySizeSub1;
    bool m_xCyclic;
    bool m_yCyclic;
    MushwareValarray<T> m_values;
};


template <class T>
MushMeshArray<T>::MushMeshArray(Mushware::U32 inXSize, Mushware::U32 inYSize) :
    m_xSize(inXSize),
    m_ySize(inYSize),
    m_xSizeSub1(inXSize-1),
    m_ySizeSub1(inYSize-1),
    m_xCyclic(false),
    m_yCyclic(false),
    m_values(inXSize*inYSize)
{
    MUSHCOREASSERT(inXSize > 0 && inYSize > 0);
}

template <class T>
inline const T&
MushMeshArray<T>::Get(Mushware::U32 inX, Mushware::U32 inY) const
{
    return m_values[inX + m_xSize * inY];
}

template <class T>
inline const T&
MushMeshArray<T>::RefGet(Mushware::U32 inX, Mushware::U32 inY) const
{
    return m_values[inX + m_xSize * inY];
}

template <class T>
inline void
MushMeshArray<T>::Set(const T& inValue, Mushware::U32 inX, Mushware::U32 inY)
{
    m_values[inX + m_xSize * inY] = inValue;
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
        m_values.resize(m_xSize * m_ySize);
        m_xSize = inSize.X();
        m_ySize = inSize.Y();
        m_xSizeSub1 = inSize.X()-1;
        m_ySizeSub1 = inSize.Y()-1;
        MUSHCOREASSERT(m_xSize > 0 && m_ySize > 0);
    }
}

template <class T>
inline void
MushMeshArray<T>::VertexNeighboursGet(MushwareValarray<const T *>& outVerts, Mushware::U32& outSize, Mushware::U32 inX, Mushware::U32 inY) const
{
    MUSHCOREASSERT(outVerts.size() >= kMaxVerts);
    const T **pVertex = &outVerts[0];

    if (inX != 0 && inY != 0 && inX < m_xSizeSub1 && inY < m_ySizeSub1)
    {
        // Optimised case
        *pVertex = &RefGet(inX-1, inY-1);
        *(++pVertex) = &RefGet(inX, inY-1);
        *(++pVertex) = &RefGet(inX-1, inY);
        *(++pVertex) = &RefGet(inX+1, inY);
        *(++pVertex) = &RefGet(inX, inY+1);
        *(++pVertex) = &RefGet(inX+1, inY+1);
        outSize = 6;
    }
    else
    {
        // General case
        Mushware::U32 xSub1;
        Mushware::U32 xPlus1;
        Mushware::U32 ySub1;
        Mushware::U32 yPlus1;
        bool generateXSub1;
        bool generateXPlus1;
        bool generateYSub1;
        bool generateYPlus1;

        // Test cycle and clip X values
        if (inX == 0)
        {
            if (m_xCyclic)
            {
                xSub1 = m_xSize - 1;
                generateXSub1 = true;
            }
            else
            {
                generateXSub1 = false;
            }
            xPlus1 = inX + 1;
            generateXPlus1 = true;
        }
        else
        {
            xSub1 = inX - 1;
            generateXSub1 = true;
 
            if (inX < m_xSizeSub1)
            {
                xPlus1 = inX + 1;
                generateXPlus1 = true;
            }
            else
            {
                if (m_xCyclic)
                {
                    xPlus1 = 0;
                    generateXPlus1 = true;
                }
                else    
                {
                    generateXPlus1 = false;
                }
            }
        }

        // Y values
        if (inY == 0)
        {
            if (m_yCyclic)
            {
                ySub1 = m_ySize - 1;
                generateYSub1 = true;
            }
            else
            {
                generateYSub1 = false;
            }
            yPlus1 = inY + 1;
            generateYPlus1 = true;
        }
        else
        {
            ySub1 = inY - 1;
            generateYSub1 = true;

            if (inY < m_ySizeSub1)
            {
                yPlus1 = inY + 1;
                generateYPlus1 = true;
            }
            else
            {
                if (m_yCyclic)
                {
                    yPlus1 = 0;
                    generateYPlus1 = true;
                }
                else
                {
                    generateYPlus1 = false;
                }
            }
        }

        if (generateYSub1)
        {
            if (generateXSub1)
            {
                *pVertex++ = &RefGet(xSub1, ySub1);
            }
            *pVertex++ = &RefGet(inX, ySub1);
        }

        if (generateXSub1)
        {
            *pVertex++ = &RefGet(xSub1, inY);
        }

        if (generateXPlus1)
        {
            *pVertex++ = &RefGet(xPlus1, inY);
        }

        if (generateYPlus1)
        {
            *pVertex++ = &RefGet(inX, yPlus1);
            if (generateXPlus1)
            {
                *pVertex++ = &RefGet(xPlus1, yPlus1);
            }
        }
        outSize = pVertex - &outVerts[0];
    }
}

template <class T>
inline bool
MushMeshArray<T>::EqualIs(const MushMeshArray<T>& inObj) const
{
    return (m_xSize == inObj.m_xSize) &&
           (m_ySize == inObj.m_ySize) &&
           MushMeshUtils::EqualIs(m_values, inObj.m_values) && // Workaround for STL problem
           (m_xCyclic == inObj.m_xCyclic) &&
           (m_yCyclic == inObj.m_yCyclic);
}

template <class T>
inline void
MushMeshArray<T>::Print(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "xSize=" << m_xSize << ", ";
    ioOut << "ySize=" << m_ySize << ", ";
    ioOut << "xSizeSub1=" << m_xSizeSub1 << ", ";
    ioOut << "ySizeSub1=" << m_ySizeSub1 << ", ";
    ioOut << "xCyclic=" << m_xCyclic << ", ";
    ioOut << "yCyclic=" << m_yCyclic << ", ";
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
