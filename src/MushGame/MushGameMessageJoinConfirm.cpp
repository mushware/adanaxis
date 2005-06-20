//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageJoinConfirm.cpp
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
//%Header } COko3K/CUso17qARGyiR7Q
/*
 *  MushGameMessageJoinConfirm.cpp
 *  project
 *
 *  Created by Andy Southgate on 20/06/2005.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include "MushGameMessageJoinConfirm.h"

//%outOfLineFunctions {

const char *MushGameMessageJoinConfirm::AutoName(void) const
{
    return "MushGameMessageJoinConfirm";
}

MushcoreVirtualObject *MushGameMessageJoinConfirm::AutoClone(void) const
{
    return new MushGameMessageJoinConfirm(*this);
}

MushcoreVirtualObject *MushGameMessageJoinConfirm::AutoCreate(void) const
{
    return new MushGameMessageJoinConfirm;
}

MushcoreVirtualObject *MushGameMessageJoinConfirm::AutoVirtualFactory(void)
{
    return new MushGameMessageJoinConfirm;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameMessageJoinConfirm", MushGameMessageJoinConfirm::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameMessageJoinConfirm::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameMessage::AutoPrint(ioOut);
    ioOut << "]";
}
bool
MushGameMessageJoinConfirm::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushGameMessageJoinConfirm::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameMessage::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } 3uxh3huyfrR6VkkKurWiSg
