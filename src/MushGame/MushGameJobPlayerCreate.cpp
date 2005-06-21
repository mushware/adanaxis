//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameJobPlayerCreate.cpp
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
//%Header } 8FammiHLxEKuAIAzehni5g
/*
 * $Id: MushGameJobPlayerCreate.cpp,v 1.1 2005/06/21 13:10:51 southa Exp $
 * $Log: MushGameJobPlayerCreate.cpp,v $
 * Revision 1.1  2005/06/21 13:10:51  southa
 * MushGame work
 *
 */

#include "MushGameJobPlayerCreate.h"

#include "MushGameLogic.h"

#include "MushGameMessageWake.h"

using namespace Mushware;
using namespace std;

MushGameJobPlayerCreate::MushGameJobPlayerCreate() :
    m_state(kStateInit)
{
}

void
MushGameJobPlayerCreate::WakeConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    switch (m_state)
    {
        case kStateInit:
        case kStateWait:
            MushcoreLog::Sgl().InfoLog() << "Send player request" << endl;
            WakeTimeSet(ioLogic.GameMsec() + kRetryMsec);
            ShouldWakeSet(true);
            m_state = kStateWait;
            break;
            
        default:
            MUSHCOREASSERT(false);
            CompleteSet(true);
            break;
    }
}

void
MushGameJobPlayerCreate::MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    const MushGameMessageWake *wakeMessage = dynamic_cast<const MushGameMessageWake *>(&inMessage);
    if (wakeMessage != NULL)
    {
        WakeConsume(ioLogic, inMessage);
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
//%outOfLineFunctions } P2jjAP8v6YWFeewtzlkY7Q
