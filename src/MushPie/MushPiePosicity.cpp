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
 * $Id: MushPiePosicity.cpp,v 1.2 2004/01/06 00:34:56 southa Exp $
 * $Log: MushPiePosicity.cpp,v $
 * Revision 1.2  2004/01/06 00:34:56  southa
 * MushPie testing
 *
 * Revision 1.1  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 */

#include "MushPiePosicity.h"

using namespace Mushware;

void
operator>>(MushcoreXMLIStream& ioIn, MushPiePosicity& outObj)
{
    if (ioIn.ByteTake() != '(') ioIn.Throw("Expecting '('");
    ioIn >> outObj.angPos;
    if (ioIn.ByteTake() != ',') ioIn.Throw("Expecting ','");
    ioIn >> outObj.angVel;
    if (ioIn.ByteTake() != ',') ioIn.Throw("Expecting ','");
    ioIn >> outObj.pos;
    if (ioIn.ByteTake() != ',') ioIn.Throw("Expecting ','");
    ioIn >> outObj.vel;
    if (ioIn.ByteTake() != ')') ioIn.Throw("Expecting ')'");
}

MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const MushPiePosicity& inObj)
{
    std::string localTag = ioOut.OpeningTagWrite();
    
    ioOut.OStreamGet() << '(';
    ioOut << inObj.angPos;
    ioOut.OStreamGet() << ',';
    ioOut << inObj.angVel;
    ioOut.OStreamGet() << ',';
    ioOut << inObj.pos;
    ioOut.OStreamGet() << ',';
    ioOut << inObj.vel;
    ioOut.OStreamGet() << ')';

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
