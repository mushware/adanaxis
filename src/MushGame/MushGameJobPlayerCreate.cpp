//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameJobPlayerCreate.cpp
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
//%Header } qU32+9pyxI1ZoLvEe4C86A
/*
 * $Id: MushGameJobPlayerCreate.cpp,v 1.14 2006/10/17 15:28:02 southa Exp $
 * $Log: MushGameJobPlayerCreate.cpp,v $
 * Revision 1.14  2006/10/17 15:28:02  southa
 * Player collisions
 *
 * Revision 1.13  2006/10/04 13:35:24  southa
 * Selective targetting
 *
 * Revision 1.12  2006/10/02 17:25:05  southa
 * Object lookup and target selection
 *
 * Revision 1.11  2006/06/01 15:39:22  southa
 * DrawArray verification and fixes
 *
 * Revision 1.10  2005/08/02 14:37:45  southa
 * Adanaxis control demo work
 *
 * Revision 1.9  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 * Revision 1.8  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.7  2005/06/24 10:30:12  southa
 * MushGame camera work
 *
 * Revision 1.6  2005/06/23 17:25:25  southa
 * MushGame link work
 *
 * Revision 1.5  2005/06/23 13:56:58  southa
 * MushGame link work
 *
 * Revision 1.4  2005/06/23 11:58:28  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/22 20:01:58  southa
 * MushGame link work
 *
 * Revision 1.2  2005/06/21 15:57:48  southa
 * MushGame work
 *
 * Revision 1.1  2005/06/21 13:10:51  southa
 * MushGame work
 *
 */

#include "MushGameJobPlayerCreate.h"

#include "MushGameLogic.h"

#include "MushGameMessageJoinConfirm.h"
#include "MushGameMessageJoinDenied.h"
#include "MushGameMessageJoinRequest.h"
#include "MushGameMessageWake.h"
#include "MushGameUtil.h"

using namespace Mushware;
using namespace std;

MushGameJobPlayerCreate::MushGameJobPlayerCreate(const std::string& inID) :
    MushGameJob(inID),
    m_state(kStateInit)
{
    ShouldWakeSet(true);
}

void
MushGameJobPlayerCreate::WakeConsume(MushGameLogic& ioLogic, const MushGameMessageWake& inMessage)
{
    switch (m_state)
    {
        case kStateInit:
        case kStateWait:
        {
            // MushcoreLog::Sgl().InfoLog() << "Send player request" << endl;
            
            MushGameMessageJoinRequest joinRequest("j:admission|"+Id());
            joinRequest.ClientNameSet(ioLogic.SaveData().ClientName());
            joinRequest.PlayerNameSet("0");
            joinRequest.PackageIDSet(MushcoreInfo::Sgl().PackageID());
            
            ioLogic.CopyAndSendToServer(joinRequest);
            
            WakeTimeSet(ioLogic.GameMsec() + kRetryMsec);
            ShouldWakeSet(true);
            m_state = kStateWait;
        }
        break;
            
        default:
            MUSHCOREASSERT(false);
            CompleteSet(true);
            break;
    }
}

void
MushGameJobPlayerCreate::JoinConfirmConsume(MushGameLogic& ioLogic, const MushGameMessageJoinConfirm& inMessage)
{
    std::string objType;
    Mushware::U32 objNum;
    MushGameUtil::ObjectNameDecode(objType, objNum, inMessage.NewPlayerID());
    if (ioLogic.SaveData().PlayersList().Exists(objNum))
    {
        throw MushcoreRequestFail("Attempt to create player that already exists");
    }
    
    MushGamePiecePlayer *pPlayer = ioLogic.SaveData().PlayersListWRef().Give(ioLogic.PlayerNew(&inMessage), objNum);
    
    pPlayer->IdSet(inMessage.NewPlayerID());
    pPlayer->PlayerNameSet(inMessage.PlayerName());
    pPlayer->ControlMailboxNameSet(ioLogic.SaveData().ControlMailboxName());
    // Create the mesh for this object
    pPlayer->MeshWRef() = *MushcoreData<MushMesh4Mesh>::Sgl().Get("player");
	pPlayer->SharedBuffersNameSet("player");
    
    ioLogic.ClientNewPlayerHandle(objNum);
    
    CompleteSet(true);
}

void
MushGameJobPlayerCreate::JoinDeniedConsume(MushGameLogic& ioLogic, const MushGameMessageJoinDenied& inMessage)
{
    MushcoreLog::Sgl().InfoLog() << "Join request denied" << endl;
    // Wait for timeout
}

void
MushGameJobPlayerCreate::MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    const MushGameMessageWake *pWakeMessage;
    const MushGameMessageJoinConfirm *pJoinConfirm;
    const MushGameMessageJoinDenied *pJoinDenied;
    
    if ((pWakeMessage = dynamic_cast<const MushGameMessageWake *>(&inMessage)) != NULL)
    {
        WakeConsume(ioLogic, *pWakeMessage);
    }
    else if ((pJoinConfirm = dynamic_cast<const MushGameMessageJoinConfirm *>(&inMessage)) != NULL)
    {
        JoinConfirmConsume(ioLogic, *pJoinConfirm);
    }
    else if ((pJoinDenied = dynamic_cast<const MushGameMessageJoinDenied *>(&inMessage)) != NULL)
    {
        JoinDeniedConsume(ioLogic, *pJoinDenied);
    }
    else
    {
        // Pass to base class
        MushGameJob::MessageConsume(ioLogic, inMessage);
    }
}

//%outOfLineFunctions {

const char *MushGameJobPlayerCreate::AutoName(void) const
{
    return "MushGameJobPlayerCreate";
}

MushcoreVirtualObject *MushGameJobPlayerCreate::AutoClone(void) const
{
    return new MushGameJobPlayerCreate(*this);
}

MushcoreVirtualObject *MushGameJobPlayerCreate::AutoCreate(void) const
{
    return new MushGameJobPlayerCreate;
}

MushcoreVirtualObject *MushGameJobPlayerCreate::AutoVirtualFactory(void)
{
    return new MushGameJobPlayerCreate;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameJobPlayerCreate", MushGameJobPlayerCreate::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameJobPlayerCreate::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameJob::AutoPrint(ioOut);
    ioOut << "state=" << m_state;
    ioOut << "]";
}
bool
MushGameJobPlayerCreate::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "state")
    {
        ioIn >> m_state;
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
MushGameJobPlayerCreate::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameJob::AutoXMLPrint(ioOut);
    ioOut.TagSet("state");
    ioOut << m_state;
}
//%outOfLineFunctions } d7q5twlznrcBv2/n0btoQA
