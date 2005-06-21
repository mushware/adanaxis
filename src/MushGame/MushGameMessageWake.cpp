//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageWake.cpp
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
//%Header } yZ79LpEYalG3wBFJ4waz3g
/*
 * $Id$
 * $Log$
 */

#include "MushGameMessageWake.h"
//%outOfLineFunctions {

const char *MushGameMessageWake::AutoName(void) const
{
    return "MushGameMessageWake";
}

MushcoreVirtualObject *MushGameMessageWake::AutoClone(void) const
{
    return new MushGameMessageWake(*this);
}

MushcoreVirtualObject *MushGameMessageWake::AutoCreate(void) const
{
    return new MushGameMessageWake;
}

MushcoreVirtualObject *MushGameMessageWake::AutoVirtualFactory(void)
{
    return new MushGameMessageWake;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameMessageWake", MushGameMessageWake::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameMessageWake::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameMessage::AutoPrint(ioOut);
    ioOut << "]";
}
bool
MushGameMessageWake::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushGameMessageWake::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameMessage::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } YlsKL0WxTJN7o4Lhfz/UZw
