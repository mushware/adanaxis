//%includeGuardStart {
#ifndef MUSHMESHWORKSPACEBASED_H
#define MUSHMESHWORKSPACEBASED_H
//%includeGuardStart } NzpIlG/ct56BpblnnzESlQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshWorkspaceBased.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } uaYx8y694rSAj4OsdDwc+Q
/*
 * $Id$
 * $Log$
 */

#include "MushMeshStandard.h"
#include "MushMeshWorkspace.h"

template<class T>
class MushMeshWorkspaceBased : public MushMeshWorkspace<T>
{
public:
    T& BaseWRefGet(void);

    void BaseToCurrentCopy(void);

private:
    T m_base;
public:
    void Print(std::ostream& ioOut) const;
};

template<class T>
inline T&
MushMeshWorkspaceBased<T>::BaseWRefGet(void)
{
    return m_base;
}

template<class T>
inline void
MushMeshWorkspaceBased<T>::BaseToCurrentCopy(void)
{
    CurrentWRefGet() = m_base;
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
