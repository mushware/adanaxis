//%includeGuardStart {
#ifndef MUSHMESHBOX_H
#define MUSHMESHBOX_H
//%includeGuardStart } ypsitLQ7bckO5My8vBP2yQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshBox.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } zg4dYJ2vck3XL9zB+0VZHQ
/*
 * $Id$
 * $Log$
 */

#include "MushMeshStandard.h"

#include "MushMeshVector.h"

template <class T>
class MushMeshBox
{
public:
    typedef MushMeshVector<T, 2> tPoint;
    MushMeshBox(const tPoint& inStart, const tPoint& inEnd);
    MushMeshBox(const T& inStartX, const T& inStartY, const T& inEndX, const T& inEndY);

    const tPoint& StartGet(void) const { return m_start; }
    void StartSet(const tPoint& inPoint) { m_start = inPoint; }
    const tPoint& EndGet(void) const { return m_end; }
    void EndSet(const tPoint& inPoint) { m_end = inPoint; }
    const tPoint SizeGet(void) const { return m_end - m_start; }

    void RegularMake(void);

private:
    tPoint m_start;
    tPoint m_end;    

public:
    bool EqualIs(const MushMeshBox& inObj) const;
    void Print(std::ostream& ioOut) const;
};

template <class T>
inline
MushMeshBox<T>::MushMeshBox(const tPoint& inStart, const tPoint& inEnd) :
    m_start(inStart),
    m_end(inEnd)
{
}

template <class T>
inline
MushMeshBox<T>::MushMeshBox(const T& inStartX, const T& inStartY, const T& inEndX, const T& inEndY) :
    m_start(tPoint(inStartX, inStartY)),
    m_end(tPoint(inEndX, inEndY))
{
}

template <class T>
inline void
MushMeshBox<T>::RegularMake(void)
{
    if (m_start.X() > m_end.X())
    {
        T tempValue;
        tempValue = m_start.X();
        m_start.XSet(m_end.X());
        m_end.XSet(tempValue);
    }
    if (m_start.Y() > m_end.Y())
    {
        T tempValue;
        tempValue = m_start.Y();
        m_start.YSet(m_end.Y());
        m_end.YSet(tempValue);
    }
}

template <class T>
inline bool
MushMeshBox<T>::EqualIs(const MushMeshBox& inObj) const
{
    return 1
        && (m_start == inObj.m_start)
        && (m_end == inObj.m_end)
    ;
}

template <class T>
inline void
MushMeshBox<T>::Print(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "start=" << m_start << ", ";
    ioOut << "end=" << m_end;
    ioOut << "]";
}


template <class T>
inline bool
operator==(const MushMeshBox<T>& inA, const MushMeshBox<T>& inB)
{
    return inA.EqualIs(inB);
}

template <class T>
inline bool
operator!=(const MushMeshBox<T>& inA, const MushMeshBox<T>& inB)
{
    return !inA.EqualIs(inB);
}

template <class T>
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshBox<T>& inObj)
{
    inObj.Print(ioOut);
    return ioOut;
}


//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
