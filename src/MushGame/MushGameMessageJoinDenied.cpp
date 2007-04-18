//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageJoinDenied.cpp
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
//%Header } leTvJTAFTUd3hfefDhTyRA
/*
 * $Id: MushGameMessageJoinDenied.cpp,v 1.3 2006/06/01 15:39:24 southa Exp $
 * $Log: MushGameMessageJoinDenied.cpp,v $
 * Revision 1.3  2006/06/01 15:39:24  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.1  2005/06/20 14:30:36  southa
 * Adanaxis work
 *
 */

#include "MushGameMessageJoinDenied.h"

//%outOfLineFunctions {

const char *MushGameMessageJoinDenied::AutoName(void) const
{
    return "MushGameMessageJoinDenied";
}

MushcoreVirtualObject *MushGameMessageJoinDenied::AutoClone(void) const
{
    return new MushGameMessageJoinDenied(*this);
}

MushcoreVirtualObject *MushGameMessageJoinDenied::AutoCreate(void) const
{
    return new MushGameMessageJoinDenied;
}

MushcoreVirtualObject *MushGameMessageJoinDenied::AutoVirtualFactory(void)
{
    return new MushGameMessageJoinDenied;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameMessageJoinDenied", MushGameMessageJoinDenied::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameMessageJoinDenied::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameMessage::AutoPrint(ioOut);
    ioOut << "]";
}
bool
MushGameMessageJoinDenied::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (MushGameMessage::AutoXMLDataProcess(ioIn, inTagStr))
    {
        // Tag consumed by base class
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameMessageJoinDenied::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameMessage::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } bPOzu0v61cZnsis9PgYiMw
