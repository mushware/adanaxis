//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisServer.cpp
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.3, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } OyX77UXDrSwa0Uzo/J9CfA
/*
 * $Id: AdanaxisServer.cpp,v 1.8 2006/08/01 17:21:29 southa Exp $
 * $Log: AdanaxisServer.cpp,v $
 * Revision 1.8  2006/08/01 17:21:29  southa
 * River demo
 *
 * Revision 1.7  2006/06/01 15:38:49  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/07/02 00:42:36  southa
 * Conditioning tweaks
 *
 * Revision 1.5  2005/06/23 13:56:57  southa
 * MushGame link work
 *
 * Revision 1.4  2005/06/22 20:01:57  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/21 15:57:46  southa
 * MushGame work
 *
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
//%outOfLineFunctions } 6ZhKK88QgMUPxqzwtFIPJQ
