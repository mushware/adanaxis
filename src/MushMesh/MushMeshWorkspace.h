//%includeGuardStart {
#ifndef MUSHMESHWORKSPACE_H
#define MUSHMESHWORKSPACE_H
//%includeGuardStart } rBavhf3LVMWNiqScmWOdhA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshWorkspace.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } +8CvtJqtL3kz6uKLVW1QDQ
/*
 * $Id: MushMeshWorkspace.h,v 1.2 2003/10/18 20:28:38 southa Exp $
 * $Log: MushMeshWorkspace.h,v $
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
