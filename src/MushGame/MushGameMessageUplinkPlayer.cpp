//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageUplinkPlayer.cpp
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
//%Header } UqnVgD6uDH55gOhU6efYng
/*
 * $Id: MushGameMessageUplinkPlayer.cpp,v 1.2 2006/06/01 15:39:25 southa Exp $
 * $Log: MushGameMessageUplinkPlayer.cpp,v $
 * Revision 1.2  2006/06/01 15:39:25  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/11 14:48:46  southa
 * Uplink work
 *
 */

#include "MushGameMessageUplinkPlayer.h"

//%outOfLineFunctions {

const char *MushGameMessageUplinkPlayer::AutoName(void) const
{
    return "MushGameMessageUplinkPlayer";
}

MushcoreVirtualObject *MushGameMessageUplinkPlayer::AutoClone(void) const
{
    return new MushGameMessageUplinkPlayer(*this);
}

MushcoreVirtualObject *MushGameMessageUplinkPlayer::AutoCreate(void) const
{
    return new MushGameMessageUplinkPlayer;
}

MushcoreVirtualObject *MushGameMessageUplinkPlayer::AutoVirtualFactory(void)
{
    return new MushGameMessageUplinkPlayer;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameMessageUplinkPlayer", MushGameMessageUplinkPlayer::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameMessageUplinkPlayer::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameMessageUplinkPiece::AutoPrint(ioOut);
    ioOut << "fireState=" << m_fireState;
    ioOut << "]";
}
bool
MushGameMessageUplinkPlayer::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "fireState")
    {
        ioIn >> m_fireState;
    }
    else if (MushGameMessageUplinkPiece::AutoXMLDataProcess(ioIn, inTagStr))
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
MushGameMessageUplinkPlayer::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameMessageUplinkPiece::AutoXMLPrint(ioOut);
    ioOut.TagSet("fireState");
    ioOut << m_fireState;
}
//%outOfLineFunctions } PL+NHARGaBgcMClIrHxIew
