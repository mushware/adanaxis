//%includeGuardStart {
#ifndef MUSHPIEPOSICITY_H
#define MUSHPIEPOSICITY_H
//%includeGuardStart } F2dkpQPdB/Jt0A6al8mBNQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePosicity.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } u4KzedBl1+uLt37oBoF4HQ
/*
 * $Id: MushPiePosicity.h,v 1.1 2004/01/04 17:02:30 southa Exp $
 * $Log: MushPiePosicity.h,v $
 * Revision 1.1  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 */

#include "MushPieStandard.h"

//:generate ostream
class MushPiePosicity
{
public:
    Mushware::tQVal angPos;
    Mushware::tQVal angVel;
    Mushware::t3Val pos;
    Mushware::t3Val vel;
    
//%classPrototypes {
public:
    void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } igNZsqh+Ffme42HZCDZW6Q
};

void
operator>>(MushcoreXMLIStream& ioIn, MushPiePosicity& outObj);

MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const MushPiePosicity& inObj);

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushPiePosicity& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } tWJxSfzqfRjlGG2ziQD8OQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
