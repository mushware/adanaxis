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
 * $Id: MushGameClient.cpp,v 1.3 2005/06/21 15:57:47 southa Exp $
 * $Log: MushGameClient.cpp,v $
 * Revision 1.3  2005/06/21 15:57:47  southa
 * MushGame work
 *
 * Revision 1.2  2005/06/20 14:30:35  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/16 10:48:59  southa
 * Client/server work
 *
 */

#include "MushGameClient.h"

MUSHCORE_DATA_INSTANCE(MushGameClient);

MushGameClient::MushGameClient()
{    
}

void
MushGameClient::MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
}

//%outOfLineFunctions {

const char *MushGameClient::AutoName(void) const
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
//%outOfLineFunctions } cbnKsomm2pgbV/XUnmfWXw
