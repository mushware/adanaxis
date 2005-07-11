//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageUplinkPiece.cpp
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
//%Header } HMrl6MUkU0BSx7cWfwSZbw
/*
 * $Id$
 * $Log$
 */

#include "MushGameMessageUplinkPiece.h"

//%outOfLineFunctions {

const char *MushGameMessageUplinkPiece::AutoName(void) const
{
    return "MushGameMessageUplinkPiece";
}

MushcoreVirtualObject *MushGameMessageUplinkPiece::AutoClone(void) const
{
    return new MushGameMessageUplinkPiece(*this);
}

MushcoreVirtualObject *MushGameMessageUplinkPiece::AutoCreate(void) const
{
    return new MushGameMessageUplinkPiece;
}

MushcoreVirtualObject *MushGameMessageUplinkPiece::AutoVirtualFactory(void)
{
    return new MushGameMessageUplinkPiece;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameMessageUplinkPiece", MushGameMessageUplinkPiece::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameMessageUplinkPiece::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameMessage::AutoPrint(ioOut);
    ioOut << "post=" << m_post;
    ioOut << "]";
}
bool
MushGameMessageUplinkPiece::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushGameMessageUplinkPiece::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameMessage::AutoXMLPrint(ioOut);
    ioOut.TagSet("post");
    ioOut << m_post;
}
//%outOfLineFunctions } HtOAg/6FUltTRUu64NMpaQ
