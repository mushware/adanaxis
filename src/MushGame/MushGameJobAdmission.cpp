//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameJobAdmission.cpp
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
//%Header } YalEpz8yBppohkHxqtvbBA
/*
 * $Id$
 * $Log$
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
MushGameJobAdmission::JoinRequestConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    U32 playerID = ioLogic.HostSaveData().NextPlayerID();
    
    if (ioLogic.HostSaveData().HostPlayers().Size() >= ioLogic.HostSaveData().MaxPlayersAllowed(), 1)
    {
        MushcoreLog::Sgl().InfoLog() << "Sending player denied" << endl;
        MushGameMessageJoinDenied deniedMessage;
        ioLogic.AsReplyCopyAndSend(deniedMessage, inMessage);
    }
    else
    {
    }
}

void
MushGameJobAdmission::MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    const MushGameMessageJoinRequest *joinRequest = dynamic_cast<const MushGameMessageJoinRequest *>(&inMessage);
    if (joinRequest != NULL)
    {
        JoinRequestConsume(ioLogic, inMessage);
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
//%outOfLineFunctions } as8KPsz/7Q1HdJbLmtsGtg
