//%includeGuardStart {
#ifndef MUSHMESHBOX_H
#define MUSHMESHBOX_H
//%includeGuardStart } ypsitLQ7bckO5My8vBP2yQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshBox.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } ZDuCclDiF5IQ7mVH6peZ2A
/*
 * $Id: MushMeshBox.h,v 1.7 2006/06/09 11:43:03 southa Exp $
 * $Log: MushMeshBox.h,v $
 * Revision 1.7  2006/06/09 11:43:03  southa
 * Facet to texture transformation
 *
 * Revision 1.6  2006/05/01 17:39:00  southa
 * Texture generation
 *
 * Revision 1.5  2005/05/19 13:02:10  southa
 * Mac release work
 *
 * Revision 1.4  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.3  2003/10/20 13:02:53  southa
 * Patch fixes and testing
 *
 * Revision 1.2  2003/10/17 19:33:10  southa
 * Mesh patches
 *
 * Revision 1.1  2003/10/17 12:27:19  southa
 * Line end fixes and more mesh work
 *
 */

#include "MushMeshStandard.h"

#include "MushMeshVector.h"

//:generate inline
template <class T>
class MushMeshBox
{
public:
    typedef MushMeshVector<T, 2> tPoint;

    MushMeshBox();
    MushMeshBox(const tPoint& inStart, const tPoint& inEnd);
    MushMeshBox(const T& inStartX, const T& inStartY, const T& inEndX, const T& inEndY);

    const tPoint SizeGet(void) const { return m_end - m_start; }
    const tPoint Size(void) const { return m_end - m_start; }

    bool RegularIs(void);
    void RegularMake(void);

private:
    tPoint m_start; //:readwrite
    tPoint m_end; //:readwrite

public:
    bool EqualIs(const MushMeshBox& inObj) const;
    void Print(std::ostream& ioOut) const;
//%classPrototypes {
public:
    const tPoint& Start(void) const { return m_start; }
    void StartSet(const tPoint& inValue) { m_start=inValue; }
    const tPoint& End(void) const { return m_end; }
    void EndSet(const tPoint& inValue) { m_end=inValue; }
//%classPrototypes } qnV570tW6c1wp7S+E9oAGA
};

template <class T>
inline
MushMeshBox<T>::MushMeshBox()
{
}

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
inline bool
MushMeshBox<T>::RegularIs(void)
{
    return m_start.X() <= m_end.X() &&
           m_start.Y() <= m_end.Y();
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

template <class T>
inline void
operator>>(MushcoreXMLIStream& ioIn, MushMeshBox<T>& outObj)
{
    std::vector<T> valueVec;
    ioIn >> valueVec;
    if (valueVec.size() != 4)
    {
        ioIn.Throw("Bad vector size for MushMeshBox");
    }
    outObj = MushMeshBox<T>(valueVec[0], valueVec[1], valueVec[2], valueVec[3]);
}

template <class T>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const MushMeshBox<T>& inObj)
{
    std::vector<T> valueVec(4);
    valueVec[0] = inObj.Start().X();
    valueVec[1] = inObj.Start().Y();
    valueVec[2] = inObj.End().X();
    valueVec[3] = inObj.End().Y();
    ioOut << valueVec;
    
    return ioOut;
}

// Convenient types
namespace Mushware
{
    typedef MushMeshBox<Mushware::U32> t2BoxU32;
    typedef MushMeshBox<Mushware::tVal> t2BoxVal;
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
