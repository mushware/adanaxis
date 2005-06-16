//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisServer.cpp
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
//%Header } 5jSH/Xb6MEG+qzzvWN1AjA
/*
 * $Id$
 * $Log$
 */

#include "AdanaxisServer.h"

//%outOfLineFunctions {

const char *AdanaxisServer::AutoNameGet(void) const
{
    return "AdanaxisServer";
}

MushcoreVirtualObject *AdanaxisServer::AutoClone(void) const
{
    return new AdanaxisServer(*this);
}

MushcoreVirtualObject *AdanaxisServer::AutoCreate(void) const
{
    return new AdanaxisServer;
}

MushcoreVirtualObject *AdanaxisServer::AutoVirtualFactory(void)
{
    return new AdanaxisServer;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisServer", AdanaxisServer::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisServer::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameServer::AutoPrint(ioOut);
    ioOut << "]";
}
bool
AdanaxisServer::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (MushGameServer::AutoXMLDataProcess(ioIn, inTagStr))
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
AdanaxisServer::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameServer::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } D6yCp7ICZz+LNVCi4+Fx1g
