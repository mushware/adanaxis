//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameServer.cpp
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
//%Header } Ib2b3u1bPJ3KuhedcK69TA
/*
 * $Id$
 * $Log$
 */

#include "MushGameServer.h"

MushGameServer::MushGameServer()
{
}

void
MushGameServer::MessageConsume(MushGameMailbox& outReplyBox, const MushGameMessage& inMessage)
{
}

//%outOfLineFunctions {

const char *MushGameServer::AutoNameGet(void) const
{
    return "MushGameServer";
}

MushcoreVirtualObject *MushGameServer::AutoClone(void) const
{
    return new MushGameServer(*this);
}

MushcoreVirtualObject *MushGameServer::AutoCreate(void) const
{
    return new MushGameServer;
}

MushcoreVirtualObject *MushGameServer::AutoVirtualFactory(void)
{
    return new MushGameServer;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameServer", MushGameServer::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameServer::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushGameServer::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushGameServer::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } PgDobFCWPKI2pDDjSoYNCA
