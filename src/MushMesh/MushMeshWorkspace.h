//%includeGuardStart {
#ifndef MUSHMESHWORKSPACE_H
#define MUSHMESHWORKSPACE_H
//%includeGuardStart } rBavhf3LVMWNiqScmWOdhA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshWorkspace.h
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
//%Header } 7ktSynjK/y89aq/T1Oxcbw
/*
 * $Id: MushMeshWorkspace.h,v 1.4 2005/05/19 13:02:11 southa Exp $
 * $Log: MushMeshWorkspace.h,v $
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
