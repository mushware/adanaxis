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
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } bU5rjQoYufJcBBZI9OgFaA
/*
 * $Id$
 * $Log$
 */

#include "MushMeshStandard.h"

template <class T>
class MushMeshWorkspace
{
public:
    MushMeshWorkspace();
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
