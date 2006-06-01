//%includeGuardStart {
#ifndef MUSHMESHSELECTION_H
#define MUSHMESHSELECTION_H
//%includeGuardStart } ZwTd1vkAqduCcDFhFqDyGw
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshSelection.h
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
//%Header } w+Qp05tgmZ9unprzaSENLQ
/*
 * $Id: MushMeshSelection.h,v 1.7 2005/08/01 17:58:25 southa Exp $
 * $Log: MushMeshSelection.h,v $
 * Revision 1.7  2005/08/01 17:58:25  southa
 * Object explosion
 *
 * Revision 1.6  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.5  2005/05/19 13:02:11  southa
 * Mac release work
 *
 * Revision 1.4  2005/02/10 12:34:07  southa
 * Template fixes
 *
 * Revision 1.3  2004/09/27 22:42:09  southa
 * MSVC compilation fixes
 *
 * Revision 1.2  2004/01/02 21:13:11  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/20 13:05:57  southa
 * Created
 *
 */

#include "MushMeshStandard.h"
#include "MushMeshVector.h"

//:generate nonvirtual ostream
class MushMeshSelection
{
public:

    Mushware::t2U32 start;
    Mushware::t2U32 stride;
    Mushware::U32 size;
//%classPrototypes {
public:
    void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } igNZsqh+Ffme42HZCDZW6Q
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
