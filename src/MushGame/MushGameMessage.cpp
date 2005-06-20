//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessage.cpp
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
//%Header } O8joXp2wbkSfRipztzWPwA
/*
 * $Id: MushGameMessage.cpp,v 1.1 2005/06/16 10:48:59 southa Exp $
 * $Log
 */

#include "MushGameMessage.h"

MushGameMessage::MushGameMessage()
{
}

//%outOfLineFunctions {

const char *MushGameMessage::AutoName(void) const
{
    return "MushGameMessage";
}

MushcoreVirtualObject *MushGameMessage::AutoClone(void) const
{
    return new MushGameMessage(*this);
}

MushcoreVirtualObject *MushGameMessage::AutoCreate(void) const
{
    return new MushGameMessage;
}

MushcoreVirtualObject *MushGameMessage::AutoVirtualFactory(void)
{
    return new MushGameMessage;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameMessage", MushGameMessage::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameMessage::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushGameMessage::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushGameMessage::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } 9OgiSD/E61EWlpidgjrVBA
