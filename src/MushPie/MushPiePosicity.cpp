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
 * $Id: MushPiePosicity.cpp,v 1.1 2004/01/04 17:02:30 southa Exp $
 * $Log: MushPiePosicity.cpp,v $
 * Revision 1.1  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
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
    std::string localTag = ioOut.OpeningTagWrite();
    
    ioOut << inObj.angPos;
    ioOut << inObj.angVel;
    ioOut << inObj.pos;
    ioOut << inObj.vel;

    ioOut.ClosingTagWrite(localTag);
    
    return ioOut;
}

//%outOfLineFunctions {
bool
MushPiePosicity::AutoEquals(const MushPiePosicity& inObj) const
{
    return 1
        && (angPos == inObj.angPos)
        && (angVel == inObj.angVel)
        && (pos == inObj.pos)
        && (vel == inObj.vel)
    ;
}
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
//%outOfLineFunctions } bsc7mssIv/uNlMoJoGZ50g
