//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePosition.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 5KWVct6ABM0OH1EfsL9HSQ
/*
 * $Id$
 * $Log$
 */

#include "MushPiePosition.h"
using namespace Mushware;

void
operator>>(MushcoreXMLIStream& ioIn, MushPiePosition& outObj)
{
    ioIn >> outObj.angPos;
    ioIn >> outObj.pos;
}

MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const MushPiePosition& inObj)
{
    ioOut << inObj.angPos;
    ioOut << inObj.pos;
    return ioOut;
}

//%outOfLineFunctions {
void
MushPiePosition::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "angPos=" << angPos << ", ";
    ioOut << "pos=" << pos;
    ioOut << "]";
}
//%outOfLineFunctions } WFq1ktxUHFScHKfNgCOLig
