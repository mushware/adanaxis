//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameJobAdmission.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } J1pFANeJRBraUOLYFDreLQ
/*
 * $Id: MushGameJobAdmission.cpp,v 1.6 2006/10/17 15:28:02 southa Exp $
 * $Log: MushGameJobAdmission.cpp,v $
 * Revision 1.6  2006/10/17 15:28:02  southa
 * Player collisions
 *
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
