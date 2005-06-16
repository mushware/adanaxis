//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisClient.cpp
 *
 * Copyright: Andy Southgate 2005
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } mGYcBWqP13PsBBDcwTbikQ
/*
 * $Id$
 * $Log$
 */

#include "AdanaxisClient.h"

//%outOfLineFunctions {

const char *AdanaxisClient::AutoNameGet(void) const
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
//%outOfLineFunctions } NoxPSUtSRW4tH1vUL+Tgxw
