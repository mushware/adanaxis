//%includeGuardStart {
#ifndef MUSHPIEPOSITION_H
#define MUSHPIEPOSITION_H
//%includeGuardStart } iDrnhb3v9WwAjgrJfJ3ImQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePosition.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } PxSYbLIM7YOX7YNd1OUhMw
/*
 * $Id: MushPiePosition.h,v 1.2 2004/01/06 00:34:56 southa Exp $
 * $Log: MushPiePosition.h,v $
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
