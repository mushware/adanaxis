//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameRefPlayer.cpp
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
//%Header } OuvMbRXRiwpwat99Zdh98w
/*
 * $Id$
 * $Log$
 */

#include "MushGameRefPlayer.h"

MushGameRefPlayer::MushGameRefPlayer(const std::string& inName, MushcoreData<MushGamePlayer> *inInstance) :
    m_playerRef(inName, *inInstance)
{
}

//%outOfLineFunctions {

const char *MushGameRefPlayer::AutoName(void) const
{
    return "MushGameRefPlayer";
}

MushcoreVirtualObject *MushGameRefPlayer::AutoClone(void) const
{
    return new MushGameRefPlayer(*this);
}

MushcoreVirtualObject *MushGameRefPlayer::AutoCreate(void) const
{
    return new MushGameRefPlayer;
}

MushcoreVirtualObject *MushGameRefPlayer::AutoVirtualFactory(void)
{
    return new MushGameRefPlayer;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameRefPlayer", MushGameRefPlayer::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameRefPlayer::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameRef::AutoPrint(ioOut);
    ioOut << "playerRef=" << m_playerRef;
    ioOut << "]";
}
bool
MushGameRefPlayer::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "playerRef")
    {
        ioIn >> m_playerRef;
    }
    else if (MushGameRef::AutoXMLDataProcess(ioIn, inTagStr))
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
MushGameRefPlayer::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameRef::AutoXMLPrint(ioOut);
    ioOut.TagSet("playerRef");
    ioOut << m_playerRef;
}
//%outOfLineFunctions } 4jvcCAs3XsCRthVFeggHZg
