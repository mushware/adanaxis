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
 * $Id$
 * $Log$
 */

#include "MushMeshStandard.h"
#include "MushMeshVector.h"

template <class T>
class MushMeshArray
{
public:
    MushMeshArray(Mushware::U32 inXSize, Mushware::U32 inYSize);
    const T& Get(Mushware::U32 inX, Mushware::U32 inY) const;
    void Set(const T& inValue, Mushware::U32 inX, Mushware::U32 inY);
    void VertexNeighboursGet(MushwareValarray<const T *>& outVerts, Mushware::U32& outSize, Mushware::U32 inX, Mushware::U32 inY);

private:
    Mushware::U32 m_xSize;
    Mushware::U32 m_ySize;
    Mushware::U32 m_xSizeSub1;
    Mushware::U32 m_ySizeSub1;
    MushwareValarray<T> m_values;
    bool m_xCyclic;
    bool m_yCyclic;
};


template <class T>
MushMeshArray<T>::MushMeshArray(Mushware::U32 inXSize, Mushware::U32 inYSize) :
    m_xSize(inXSize),
    m_ySize(inYSize),
    m_xSizeSub1(inXSize-1),
    m_ySizeSub1(inYSize-1),
    m_xCyclic(false),
    m_yCyclic(false)
{
    MUSHCOREASSERT(inXSize > 0 && inYSize > 0);
    m_values.resize(inXSize*inYSize);
}

template <class T>
inline const T&
MushMeshArray<T>::Get(Mushware::U32 inX, Mushware::U32 inY) const
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
inline void
MushMeshArray<T>::VertexNeighboursGet(MushwareValarray<const T *>& outVerts, Mushware::U32& outSize, Mushware::U32 inX, Mushware::U32 inY)
{
    MUSHCOREASSERT(outVerts.size() >= 6);
    const T **pVertex = &outVerts[0];

    if (inX != 0 && inY != 0 && inX < m_xSizeSub1 && inY < m_ySizeSub1)
    {
        // Optimised case
        *pVertex = &m_values[inX-1, inY-1];
        *(++pVertex) = &m_values[inX, inY-1];
        *(++pVertex) = &m_values[inX-1, inY];
        *(++pVertex) = &m_values[inX+1, inY];
        *(++pVertex) = &m_values[inX, inY+1];
        *(++pVertex) = &m_values[inX+1, inY+1];
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
                *pVertex++ = &m_values[xSub1, ySub1];
            }
            *pVertex++ = &m_values[inX, ySub1];
        }

        if (generateXSub1)
        {
            *pVertex++ = &m_values[xSub1, inY];
        }

        if (generateXPlus1)
        {
            *pVertex++ = &m_values[xPlus1, inY];
        }

        if (generateYPlus1)
        {
            *pVertex++ = &m_values[inX, yPlus1];
            if (generateXPlus1)
            {
                *pVertex++ = &m_values[xPlus1, yPlus1];
            }
        }
        outSize = pVertex - &outVerts[0];
    }
}



//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
