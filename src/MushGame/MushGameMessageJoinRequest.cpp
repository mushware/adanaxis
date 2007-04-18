//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageJoinRequest.cpp
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
//%Header } 6PXSM8orluYVKu7Q2PGyfQ
/*
 *  MushGameMessageJoinRequest.cpp
 *  project
 *
 *  Created by Andy Southgate on 20/06/2005.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include "MushGameMessageJoinRequest.h"

//%outOfLineFunctions {

const char *MushGameMessageJoinRequest::AutoName(void) const
{
    return "MushGameMessageJoinRequest";
}

MushcoreVirtualObject *MushGameMessageJoinRequest::AutoClone(void) const
{
    return new MushGameMessageJoinRequest(*this);
}

MushcoreVirtualObject *MushGameMessageJoinRequest::AutoCreate(void) const
{
    return new MushGameMessageJoinRequest;
}

MushcoreVirtualObject *MushGameMessageJoinRequest::AutoVirtualFactory(void)
{
    return new MushGameMessageJoinRequest;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameMessageJoinRequest", MushGameMessageJoinRequest::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameMessageJoinRequest::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameMessage::AutoPrint(ioOut);
    ioOut << "clientName=" << m_clientName << ", ";
    ioOut << "playerName=" << m_playerName << ", ";
    ioOut << "packageID=" << m_packageID;
    ioOut << "]";
}
bool
MushGameMessageJoinRequest::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "clientName")
    {
        ioIn >> m_clientName;
    }
    else if (inTagStr == "playerName")
    {
        ioIn >> m_playerName;
    }
    else if (inTagStr == "packageID")
    {
        ioIn >> m_packageID;
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
MushGameMessageJoinRequest::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameMessage::AutoXMLPrint(ioOut);
    ioOut.TagSet("clientName");
    ioOut << m_clientName;
    ioOut.TagSet("playerName");
    ioOut << m_playerName;
    ioOut.TagSet("packageID");
    ioOut << m_packageID;
}
//%outOfLineFunctions } zur/wek2UdmVisJBbJLGtQ
