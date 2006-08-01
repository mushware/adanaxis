//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisClient.cpp
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.1, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 8QC77xLORrqOmOzn6o6lgA
/*
 * $Id: AdanaxisClient.cpp,v 1.4 2006/06/01 15:38:46 southa Exp $
 * $Log: AdanaxisClient.cpp,v $
 * Revision 1.4  2006/06/01 15:38:46  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/07/02 00:42:36  southa
 * Conditioning tweaks
 *
 * Revision 1.2  2005/06/20 14:30:33  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/16 10:49:57  southa
 * Client/server work
 *
 */

#include "AdanaxisClient.h"

//%outOfLineFunctions {

const char *AdanaxisClient::AutoName(void) const
{
    return "AdanaxisClient";
}

MushcoreVirtualObject *AdanaxisClient::AutoClone(void) const
{
    return new AdanaxisClient(*this);
}

MushcoreVirtualObject *AdanaxisClient::AutoCreate(void) const
{
    return new AdanaxisClient;
}

MushcoreVirtualObject *AdanaxisClient::AutoVirtualFactory(void)
{
    return new AdanaxisClient;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisClient", AdanaxisClient::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisClient::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameClient::AutoPrint(ioOut);
    ioOut << "]";
}
bool
AdanaxisClient::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (MushGameClient::AutoXMLDataProcess(ioIn, inTagStr))
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
AdanaxisClient::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameClient::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } MKiksVc34iPApeuBpWYHVQ
