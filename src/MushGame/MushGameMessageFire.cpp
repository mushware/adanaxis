//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageFire.cpp
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
//%Header } TUyHLJpfwBpQ6dlpQI4+nQ
/*
 * $Id$
 * $Log$
 */

#include "MushGameMessageFire.h"

//%outOfLineFunctions {

const char *MushGameMessageFire::AutoName(void) const
{
    return "MushGameMessageFire";
}

MushcoreVirtualObject *MushGameMessageFire::AutoClone(void) const
{
    return new MushGameMessageFire(*this);
}

MushcoreVirtualObject *MushGameMessageFire::AutoCreate(void) const
{
    return new MushGameMessageFire;
}

MushcoreVirtualObject *MushGameMessageFire::AutoVirtualFactory(void)
{
    return new MushGameMessageFire;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameMessageFire", MushGameMessageFire::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameMessageFire::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameMessage::AutoPrint(ioOut);
    ioOut << "post=" << m_post << ", ";
    ioOut << "type=" << m_type << ", ";
    ioOut << "owner=" << m_owner;
    ioOut << "]";
}
bool
MushGameMessageFire::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "post")
    {
        ioIn >> m_post;
    }
    else if (inTagStr == "type")
    {
        ioIn >> m_type;
    }
    else if (inTagStr == "owner")
    {
        ioIn >> m_owner;
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
MushGameMessageFire::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameMessage::AutoXMLPrint(ioOut);
    ioOut.TagSet("post");
    ioOut << m_post;
    ioOut.TagSet("type");
    ioOut << m_type;
    ioOut.TagSet("owner");
    ioOut << m_owner;
}
//%outOfLineFunctions } Fe/fXpUZOJom5d70lajqAw
