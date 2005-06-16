//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLPixelSource.cpp
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
//%Header } LccQwBTHLT37eo+dpTNBig
/*
 * $Id: MushGLPixelSource.cpp,v 1.2 2005/05/19 13:02:09 southa Exp $
 * $Log: MushGLPixelSource.cpp,v $
 * Revision 1.2  2005/05/19 13:02:09  southa
 * Mac release work
 *
 * Revision 1.1  2005/02/13 22:44:07  southa
 * Tesseract stuff
 *
 */

#include "MushGLPixelSource.h"

MUSHCORE_DATA_INSTANCE(MushGLPixelSource);

//%outOfLineFunctions {
void
MushGLPixelSource::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushGLPixelSource::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else
    {
        return false;
    }
    return true;
}
void
MushGLPixelSource::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } 3w4QPIqAN1anXzJkRs9lZg
