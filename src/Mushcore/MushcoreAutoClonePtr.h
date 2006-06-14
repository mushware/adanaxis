//%includeGuardStart {
#ifndef MUSHCOREAUTOCLONEPTR_H
#define MUSHCOREAUTOCLONEPTR_H
//%includeGuardStart } MFR3Pz6m13lzcjHKZ/VmgA
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreAutoClonePtr.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } AtI7Zm+isB7x0vb4EGBGvg
/*
 * $Id: MushcoreAutoClonePtr.h,v 1.2 2006/06/01 15:39:41 southa Exp $
 * $Log: MushcoreAutoClonePtr.h,v $
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
