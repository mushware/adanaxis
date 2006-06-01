//%includeGuardStart {
#ifndef MUSHMESHWORKSPACEBASED_H
#define MUSHMESHWORKSPACEBASED_H
//%includeGuardStart } NzpIlG/ct56BpblnnzESlQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshWorkspaceBased.h
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
//%Header } r0Cud/Kdg4Tl3wxyTrivDw
/*
 * $Id: MushMeshWorkspaceBased.h,v 1.5 2005/05/19 13:02:11 southa Exp $
 * $Log: MushMeshWorkspaceBased.h,v $
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
