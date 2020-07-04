//%includeGuardStart {
#ifndef MUSHMESHWORKSPACE_H
#define MUSHMESHWORKSPACE_H
//%includeGuardStart } rBavhf3LVMWNiqScmWOdhA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshWorkspace.h
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
//%Header } pavLJMuBmCWPtktRJGAt3A
/*
 * $Id: MushMeshWorkspace.h,v 1.5 2006/06/01 15:39:33 southa Exp $
 * $Log: MushMeshWorkspace.h,v $
 * Revision 1.5  2006/06/01 15:39:33  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/05/19 13:02:11  southa
 * Mac release work
 *
 * Revision 1.3  2004/01/02 21:13:11  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/18 20:28:38  southa
 * Subdivision speed tests
 *
 * Revision 1.1  2003/10/17 19:38:25  southa
 * Created
 *
 */

#include "MushMeshStandard.h"

template <class T>
class MushMeshWorkspace
{
public:
    MushMeshWorkspace();
    const T& CurrentGet(void) const;
    const T& PreviousGet(void) const;
    T& CurrentWRefGet(void);
    T& PreviousWRefGet(void);
    void Swap(void);

private:
    std::vector<T> m_workspace;
    Mushware::U32 m_current;

public:
    void Print(std::ostream& ioOut) const;
};

template<class T>
MushMeshWorkspace<T>::MushMeshWorkspace() :
    m_workspace(2),
    m_current(0)
{
}

template<class T>
inline const T&
MushMeshWorkspace<T>::CurrentGet(void) const
{
    return m_workspace[m_current];
}

template<class T>
inline const T&
MushMeshWorkspace<T>::PreviousGet(void) const
{
    return m_workspace[1 - m_current];
}

template<class T>
inline T&
MushMeshWorkspace<T>::CurrentWRefGet(void)
{
    return m_workspace[m_current];
}

template<class T>
inline T&
MushMeshWorkspace<T>::PreviousWRefGet(void)
{
    return m_workspace[1 - m_current];
}

template<class T>
inline void
MushMeshWorkspace<T>::Swap(void)
{
    m_current = 1 - m_current;
}

template<class T>
inline void
MushMeshWorkspace<T>::Print(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "workspace=" << m_workspace << ", ";
    ioOut << "current=" << m_current;
    ioOut << "]";
}

template<class T>
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshWorkspace<T>& inObj)
{
    inObj.Print(ioOut);
    return ioOut;
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
