//%includeGuardStart {
#ifndef MUSHPIEPOSITION_H
#define MUSHPIEPOSITION_H
//%includeGuardStart } iDrnhb3v9WwAjgrJfJ3ImQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePosition.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } Fy/IUGeeVM06aENrKG7H5w
/*
 * $Id: MushPiePosition.h,v 1.3 2005/02/10 12:34:15 southa Exp $
 * $Log: MushPiePosition.h,v $
 * Revision 1.3  2005/02/10 12:34:15  southa
 * Template fixes
 *
 * Revision 1.2  2004/01/06 00:34:56  southa
 * MushPie testing
 *
 * Revision 1.1  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 */

#include "MushPieStandard.h"

//:generate ostream
class MushPiePosition
{
public:
    MushPiePosition() {}
    
    Mushware::tQVal angPos;
    Mushware::t3Val pos;

//%classPrototypes {
public:
    void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } igNZsqh+Ffme42HZCDZW6Q
};

void
operator>>(MushcoreXMLIStream& ioIn, MushPiePosition& outObj);

MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const MushPiePosition& inObj);

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushPiePosition& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } d8HdhqjTeBKhSuh3Oc/qcQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
