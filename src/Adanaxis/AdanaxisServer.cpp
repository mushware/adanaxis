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
 * $Id: AdanaxisServer.cpp,v 1.2 2005/06/20 14:30:33 southa Exp $
 * $Log: AdanaxisServer.cpp,v $
 * Revision 1.2  2005/06/20 14:30:33  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/16 10:49:57  southa
 * Client/server work
 *
 */

#include "AdanaxisServer.h"

void
AdanaxisServer::MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    MushGameServer::MessageConsume(ioLogic, inMessage);
}

void
AdanaxisServer::JoinRequestConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    if (SaveData().Players().Size() >= SaveData().MaxPlayersAllowed())
    {
        MushGameMessageJoinDenied *pJoinDenied = new MushGameMessageJoinDenied;
        //outReplyBox.Give(pJoinDenied);
    }
    else
    {
    }
}

//%outOfLineFunctions {

const char *AdanaxisServer::AutoName(void) const
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
//%outOfLineFunctions } trMMGZRBwu0OySY7A/qsgg
