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
 * $Id: MushGamePlayer.cpp,v 1.2 2005/06/20 14:30:36 southa Exp $
 * $Log: MushGamePlayer.cpp,v $
 * Revision 1.2  2005/06/20 14:30:36  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/16 17:25:39  southa
 * Client/server work
 *
 */

#include "MushGamePlayer.h"

using namespace Mushware;
using namespace std;

MushGamePlayer::MushGamePlayer(std::string inID) :
    m_id(inID)
{
}

void
MushGamePlayer::MessageConsume(MushGameMailbox& outReplyBox, const MushGameMessage& inMessage)
{
}

//%outOfLineFunctions {

const char *MushGamePlayer::AutoName(void) const
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
    ioOut << "id=" << m_id << ", ";
    ioOut << "playerName=" << m_playerName;
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
    else if (inTagStr == "id")
    {
        ioIn >> m_id;
    }
    else if (inTagStr == "playerName")
    {
        ioIn >> m_playerName;
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
    ioOut.TagSet("id");
    ioOut << m_id;
    ioOut.TagSet("playerName");
    ioOut << m_playerName;
}
//%outOfLineFunctions } SJ4axSi1k3T3wNGhWt3w/Q
