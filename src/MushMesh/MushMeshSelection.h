//%includeGuardStart {
#ifndef MUSHMESHSELECTION_H
#define MUSHMESHSELECTION_H
//%includeGuardStart } ZwTd1vkAqduCcDFhFqDyGw
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshSelection.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } CmkuxGelnF+aOAES+7mivg
/*
 * $Id: MushMeshSelection.h,v 1.2 2004/01/02 21:13:11 southa Exp $
 * $Log: MushMeshSelection.h,v $
 * Revision 1.2  2004/01/02 21:13:11  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/20 13:05:57  southa
 * Created
 *
 */

#include "MushMeshStandard.h"
#include "MushMeshVector.h"

//:generate ostream
class MushMeshSelection
{
public:
    Mushware::t2U32 start;
    Mushware::t2U32 stride;
    Mushware::U32 size;
//%classPrototypes {
public:
    virtual void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } b86DSDsq8lQQbiM0rrNtkg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshSelection& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } hY/T98Ru1YtnD32lhEtIpA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
