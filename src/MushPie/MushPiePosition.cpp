//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePosition.cpp
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } pnARIeNNWwZ3CSI0Mi8zrw
/*
 * $Id: MushPiePosition.cpp,v 1.3 2006/05/11 10:43:16 southa Exp $
 * $Log: MushPiePosition.cpp,v $
 * Revision 1.3  2006/05/11 10:43:16  southa
 * Project updates
 *
 * Revision 1.2  2005/05/19 13:02:13  southa
 * Mac release work
 *
 * Revision 1.1  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
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
