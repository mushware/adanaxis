//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieSignal.cpp
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
//%Header } 1C8j1hqSjBkuainavpw0IQ
/*
 * $Id: MushPieSignal.cpp,v 1.5 2005/06/20 14:30:37 southa Exp $
 * $Log: MushPieSignal.cpp,v $
 * Revision 1.5  2005/06/20 14:30:37  southa
 * Adanaxis work
 *
 * Revision 1.4  2005/06/16 17:25:40  southa
 * Client/server work
 *
 * Revision 1.3  2005/05/19 13:02:13  southa
 * Mac release work
 *
 * Revision 1.2  2005/02/10 12:34:16  southa
 * Template fixes
 *
 * Revision 1.1  2004/01/10 20:29:35  southa
 * Form and rendering work
 *
 */

#include "MushPieSignal.h"

//%outOfLineFunctions {

const char *MushPieSignal::AutoName(void) const
{
    return "MushPieSignal";
}

MushcoreVirtualObject *MushPieSignal::AutoClone(void) const
{
    return new MushPieSignal(*this);
}

MushcoreVirtualObject *MushPieSignal::AutoCreate(void) const
{
    return new MushPieSignal;
}

MushcoreVirtualObject *MushPieSignal::AutoVirtualFactory(void)
{
    return new MushPieSignal;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushPieSignal", MushPieSignal::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushPieSignal::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushPieSignal::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushPieSignal::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } zwYn5V3KeP742YjF16/ekg
