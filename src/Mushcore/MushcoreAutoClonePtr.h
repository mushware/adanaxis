//%includeGuardStart {
#ifndef MUSHCOREAUTOCLONEPTR_H
#define MUSHCOREAUTOCLONEPTR_H
//%includeGuardStart } MFR3Pz6m13lzcjHKZ/VmgA
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreAutoClonePtr.h
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
//%Header } hB4It+tKKPNnbjhzm24FFg
/*
 * $Id: MushcoreAutoClonePtr.h,v 1.3 2006/06/14 11:20:10 southa Exp $
 * $Log: MushcoreAutoClonePtr.h,v $
 * Revision 1.3  2006/06/14 11:20:10  southa
 * Ruby mesh generation
 *
 * Revision 1.2  2006/06/01 15:39:41  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/12 20:39:05  southa
 * Mesh library work
 *
 */

#include "MushcoreStandard.h"

#include "MushcoreFail.h"
#include "MushcoreVirtualObject.h"
#include "MushcoreXMLIStream.h"
#include "MushcoreXMLOStream.h"

template<class T>
class MushcoreAutoClonePtr
{
public:
    explicit MushcoreAutoClonePtr(T *inpObj = NULL) : m_ptr(inpObj) {}
    MushcoreAutoClonePtr(const MushcoreAutoClonePtr& inClonePtr);
    virtual ~MushcoreAutoClonePtr() { delete m_ptr; }
    
    MushcoreAutoClonePtr& operator=(const MushcoreAutoClonePtr& inClonePtr);
    
    T *Get(void) const { return m_ptr; }
    void Reset(T *inpObj) { delete m_ptr; m_ptr = inpObj; }
    T& operator*() { MUSHCOREASSERT(m_ptr != NULL); return m_ptr; }
    T *operator->() { MUSHCOREASSERT(m_ptr != NULL); return m_ptr; }
    void FromXMLRead(MushcoreXMLIStream& ioIn);
    
private:
    T *m_ptr;
};

template<class T>
inline
MushcoreAutoClonePtr<T>::MushcoreAutoClonePtr(const MushcoreAutoClonePtr& inClonePtr)
{
    if (inClonePtr.m_ptr == NULL)
    {
        m_ptr = NULL;   
    }
    else
    {
        m_ptr = dynamic_cast<T *>(inClonePtr.m_ptr->AutoClone());
        if (m_ptr == NULL)
        {
            throw MushcoreLogicFail("Cast to type failed");
        }
    }
}

template<class T>
inline MushcoreAutoClonePtr<T>&
MushcoreAutoClonePtr<T>::operator=(const MushcoreAutoClonePtr& inClonePtr)
{
    if (&inClonePtr != this)
    {
        MushcoreAutoClonePtr tempObj(inClonePtr);
        // Swap the contents
        T *tempPtr = m_ptr;
        m_ptr = tempObj.m_ptr;
        tempObj.m_ptr = tempPtr;
    }
    return *this;
}

template<class T>
inline void
MushcoreAutoClonePtr<T>::FromXMLRead(MushcoreXMLIStream& ioIn)
{
    ioIn >> m_ptr;
}

template<class T>
inline std::ostream&
operator<<(std::ostream& ioOut, const MushcoreAutoClonePtr<T>& inObj)
{
    ioOut << inObj.Get();
    return ioOut;
}

template<class T>
inline MushcoreXMLIStream&
operator>>(MushcoreXMLIStream& ioIn, MushcoreAutoClonePtr<T>& outObj)
{
    outObj.FromXMLRead(ioIn);
    return ioIn;
}

template<class T>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const MushcoreAutoClonePtr<T>& inObj)
{
    ioOut << inObj.Get();
    return ioOut;
}


//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
