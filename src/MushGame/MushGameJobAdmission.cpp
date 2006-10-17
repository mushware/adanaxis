//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameJobAdmission.cpp
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } KiIXpTnHXcN2vGSkbhO8LQ
/*
 * $Id: MushGameJobAdmission.cpp,v 1.5 2006/10/02 17:25:05 southa Exp $
 * $Log: MushGameJobAdmission.cpp,v $
 * Revision 1.5  2006/10/02 17:25:05  southa
 * Object lookup and target selection
 *
 * Revision 1.4  2006/06/01 15:39:22  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.2  2005/06/23 17:25:25  southa
 * MushGame link work
 *
 * Revision 1.1  2005/06/23 13:56:58  southa
 * MushGame link work
 *
 */

#include "MushGameJobAdmission.h"

#include "MushGameLogic.h"
#include "MushGameMessageJoinConfirm.h"
#include "MushGameMessageJoinDenied.h"
#include "MushGameMessageJoinRequest.h"

using namespace Mushware;
using namespace std;

MushGameJobAdmission::MushGameJobAdmission(const std::string& inID) :
    MushGameJob(inID)
{
}

void
MushGameJobAdmission::JoinRequestConsume(MushGameLogic& ioLogic, const MushGameMessageJoinRequest& inMessage)
{    
    if (ioLogic.HostSaveData().HostPlayersList().size() >= ioLogic.HostSaveData().MaxPlayersAllowed())
    {
        MushGameMessageJoinDenied deniedMessage;
        ioLogic.AsReplyCopyAndSend(deniedMessage, inMessage);
    }
    else
    {
        U32 newPlayerNum = ioLogic.HostSaveData().NextPlayerNum();
        ++ioLogic.HostSaveData().NextPlayerNumWRef();
        
        std::string newPlayerName;
        {
            ostringstream newPlayerStream;
            newPlayerStream << newPlayerNum;
            newPlayerName = newPlayerStream.str();
        }
        
        if (ioLogic.HostSaveData().HostPlayersList().Exists(newPlayerNum))
        {
            throw MushcoreRequestFail("Attempt to create player that already exists");
        }
        
        MushGamePiecePlayer *pPlayer =
            ioLogic.HostSaveData().HostPlayersListWRef().Give(ioLogic.PlayerNew(&inMessage), newPlayerNum);

        pPlayer->IdSet("p:"+newPlayerName);
        pPlayer->PlayerNameSet(inMessage.PlayerName());
        
        MushGameMessageJoinConfirm confirmMessage;
        
        ostringstream playerID;
        playerID << newPlayerNum;

        confirmMessage.NewPlayerIDSet("p:"+playerID.str());
        confirmMessage.HostNameSet(ioLogic.HostSaveData().ServerName());
        confirmMessage.PlayerNameSet(inMessage.PlayerName());
        confirmMessage.HostPackageIDSet(MushcoreInfo::Sgl().PackageID());
        
        ioLogic.AsReplyCopyAndSend(confirmMessage, inMessage);
    }
}

void
MushGameJobAdmission::MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    const MushGameMessageJoinRequest *joinRequest = dynamic_cast<const MushGameMessageJoinRequest *>(&inMessage);
    if (joinRequest != NULL)
    {
        JoinRequestConsume(ioLogic, *joinRequest);
    }
    else
    {
        // Pass to base class
        MushGameJob::MessageConsume(ioLogic, inMessage);
    }
}

//%outOfLineFunctions {

const char *MushGameJobAdmission::AutoName(void) const
{
    return "MushGameJobAdmission";
}

MushcoreVirtualObject *MushGameJobAdmission::AutoClone(void) const
{
    return new MushGameJobAdmission(*this);
}

MushcoreVirtualObject *MushGameJobAdmission::AutoCreate(void) const
{
    return new MushGameJobAdmission;
}

MushcoreVirtualObject *MushGameJobAdmission::AutoVirtualFactory(void)
{
    return new MushGameJobAdmission;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameJobAdmission", MushGameJobAdmission::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameJobAdmission::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameJob::AutoPrint(ioOut);
    ioOut << "]";
}
bool
MushGameJobAdmission::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (MushGameJob::AutoXMLDataProcess(ioIn, inTagStr))
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
MushGameJobAdmission::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameJob::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } By0UVwDmfZff7HrW//FMzw
