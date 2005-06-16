//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameClient.cpp
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
//%Header } ZzA13XBaYAADYudEapYUYw
/*
 * $Id$
 * $Log$
 */

#include "MushGameClient.h"

MushGameClient::MushGameClient()
{
    
}

void
MushGameClient::MessageConsume(MushGameMailbox& outReplyBox, const MushGameMessage& inMessage)
{
}

//%outOfLineFunctions {

const char *MushGameClient::AutoNameGet(void) const
{
    return "MushGameClient";
}

MushcoreVirtualObject *MushGameClient::AutoClone(void) const
{
    return new MushGameClient(*this);
}

MushcoreVirtualObject *MushGameClient::AutoCreate(void) const
{
    return new MushGameClient;
}

MushcoreVirtualObject *MushGameClient::AutoVirtualFactory(void)
{
    return new MushGameClient;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameClient", MushGameClient::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameClient::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushGameClient::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushGameClient::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } AQ27IcEsY8b5NMgNzQetvA
