//%includeGuardStart {
#ifndef MUSHMESHWORKSPACEBASED_H
#define MUSHMESHWORKSPACEBASED_H
//%includeGuardStart } NzpIlG/ct56BpblnnzESlQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshWorkspaceBased.h
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
//%Header } E7KS4C1N++0aguu6E/ghrg
/*
 * $Id: MushMeshWorkspaceBased.h,v 1.6 2006/06/01 15:39:33 southa Exp $
 * $Log: MushMeshWorkspaceBased.h,v $
 * Revision 1.6  2006/06/01 15:39:33  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/05/19 13:02:11  southa
 * Mac release work
 *
 * Revision 1.4  2005/05/18 15:53:27  southa
 * Made buildable using gcc 4.0/Mac OS X 10.4
 *
 * Revision 1.3  2004/01/02 21:13:11  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/19 15:59:34  southa
 * Edge manipulation
 *
 * Revision 1.1  2003/10/17 19:38:25  southa
 * Created
 *
 */

#include "MushMeshStandard.h"
#include "MushMeshWorkspace.h"

template<class T>
class MushMeshWorkspaceBased : public MushMeshWorkspace<T>
{
public:
    const T& BaseGet(void) { return m_base; }
    T& BaseWRefGet(void) { return m_base; }

    void BaseToCurrentCopy(void);

private:
    T m_base;
public:
    void Print(std::ostream& ioOut) const;
};

template<class T>
inline void
MushMeshWorkspaceBased<T>::BaseToCurrentCopy(void)
{
    this->CurrentWRefGet() = m_base;
}

template<class T>
inline void
MushMeshWorkspaceBased<T>::Print(std::ostream& ioOut) const
{

    ioOut << "[";
    MushMeshWorkspace<T>::Print(ioOut);
    ioOut << "base=" << m_base;
    ioOut << "]";
}

template<class T>
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshWorkspaceBased<T>& inObj)
{
    inObj.Print(ioOut);
    return ioOut;
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
