//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameSaveData.cpp
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
//%Header } OWJ0lyKjoxUWAtsxD5Oexg
/*
 * $Id: MushGameSaveData.cpp,v 1.1 2005/06/16 17:25:39 southa Exp $
 * $Log: MushGameSaveData.cpp,v $
 * Revision 1.1  2005/06/16 17:25:39  southa
 * Client/server work
 *
 */

#include "MushGameSaveData.h"

MUSHCORE_DATA_INSTANCE(MushGameSaveData);

MushGameSaveData::MushGameSaveData() :
    m_nextPlayerID(2)
{
}

//%outOfLineFunctions {

const char *MushGameSaveData::AutoName(void) const
{
    return "MushGameSaveData";
}

MushcoreVirtualObject *MushGameSaveData::AutoClone(void) const
{
    return new MushGameSaveData(*this);
}

MushcoreVirtualObject *MushGameSaveData::AutoCreate(void) const
{
    return new MushGameSaveData;
}

MushcoreVirtualObject *MushGameSaveData::AutoVirtualFactory(void)
{
    return new MushGameSaveData;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameSaveData", MushGameSaveData::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameSaveData::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "players=" << m_players << ", ";
    ioOut << "nextPlayerID=" << m_nextPlayerID << ", ";
    ioOut << "maxPlayersAllowed=" << m_maxPlayersAllowed;
    ioOut << "]";
}
bool
MushGameSaveData::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "players")
    {
        ioIn >> m_players;
    }
    else if (inTagStr == "nextPlayerID")
    {
        ioIn >> m_nextPlayerID;
    }
    else if (inTagStr == "maxPlayersAllowed")
    {
        ioIn >> m_maxPlayersAllowed;
    }
    else
    {
        return false;
    }
    return true;
}
void
MushGameSaveData::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("players");
    ioOut << m_players;
    ioOut.TagSet("nextPlayerID");
    ioOut << m_nextPlayerID;
    ioOut.TagSet("maxPlayersAllowed");
    ioOut << m_maxPlayersAllowed;
}
//%outOfLineFunctions } qB2bqso9RrltGnq98gqqIQ
