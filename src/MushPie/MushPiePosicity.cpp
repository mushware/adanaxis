//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePosicity.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 0niOQpG0nEHxTZPccDWOjQ
/*
 * $Id$
 * $Log$
 */

#include "MushPiePosicity.h"

using namespace Mushware;

void
operator>>(MushcoreXMLIStream& ioIn, MushPiePosicity& outObj)
{
    ioIn >> outObj.angPos;
    ioIn >> outObj.angVel;
    ioIn >> outObj.pos;
    ioIn >> outObj.vel;
}

MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const MushPiePosicity& inObj)
{
    ioOut << inObj.angPos;
    ioOut << inObj.angVel;
    ioOut << inObj.pos;
    ioOut << inObj.vel;
    return ioOut;
}

//%outOfLineFunctions {
void
MushPiePosicity::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "angPos=" << angPos << ", ";
    ioOut << "angVel=" << angVel << ", ";
    ioOut << "pos=" << pos << ", ";
    ioOut << "vel=" << vel;
    ioOut << "]";
}
//%outOfLineFunctions } YP4Vpc9NGmc8hguBTeGcWA
