//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGamePlayer.cpp
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
//%Header } nBtAQHbpc8XKKxgcOfRPVA
/*
 * $Id$
 * $Log$
 */

#include "MushGamePlayer.h"

using namespace Mushware;
using namespace std;

MushGamePlayer::MushGamePlayer(Mushware::U32 inPlayerID) :
    m_playerID(inPlayerID)
{
}

void
MushGamePlayer::MessageConsume(MushGameMailbox& outReplyBox, const MushGameMessage& inMessage)
{
}
//%outOfLineFunctions {

const char *MushGamePlayer::AutoNameGet(void) const
{
    return "MushGamePlayer";
}

MushcoreVirtualObject *MushGamePlayer::AutoClone(void) const
{
    return new MushGamePlayer(*this);
}

MushcoreVirtualObject *MushGamePlayer::AutoCreate(void) const
{
    return new MushGamePlayer;
}

MushcoreVirtualObject *MushGamePlayer::AutoVirtualFactory(void)
{
    return new MushGamePlayer;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGamePlayer", MushGamePlayer::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGamePlayer::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "playerID=" << m_playerID;
    ioOut << "]";
}
bool
MushGamePlayer::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "playerID")
    {
        ioIn >> m_playerID;
    }
    else
    {
        return false;
    }
    return true;
}
void
MushGamePlayer::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("playerID");
    ioOut << m_playerID;
}
//%outOfLineFunctions } aftg6XwYIt+WUkcxbS4CHQ
