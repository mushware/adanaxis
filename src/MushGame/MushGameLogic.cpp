//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameLogic.cpp
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
//%Header } G0/dfauKPLZ8TwNbwBtU8A
/*
 * $Id: MushGameLogic.cpp,v 1.1 2005/06/21 13:10:51 southa Exp $
 * $Log: MushGameLogic.cpp,v $
 * Revision 1.1  2005/06/21 13:10:51  southa
 * MushGame work
 *
 */

#include "MushGameLogic.h"

#include "MushGameJob.h"
#include "MushGameMessageWake.h"

#include "API/mushGame.h"

MUSHCORE_DATA_INSTANCE(MushGameLogic);

using namespace Mushware;
using namespace std;

Mushware::U32
MushGameLogic::GameMsec(void) const
{
    GameAppHandler *pGameAppHandler=dynamic_cast<GameAppHandler *>(&MushcoreAppHandler::Sgl());
    if (pGameAppHandler == NULL)
    {
        return 0;
    }
    else
    {
        return pGameAppHandler->MillisecondsGet();
    }
}

void
MushGameLogic::JobListProcess(MushGameMailbox& outReplyBox, tJobList& ioList)
{
    U32 msecNow = GameMsec();
    
    for (tJobList::tIterator p = ioList.Begin(); p != ioList.End(); )
    {
        MushGameJob *pJob = p->second;
        MUSHCOREASSERT(pJob != NULL);
        if (pJob->ShouldWake())
        {
            if (pJob->WakeTime() <= msecNow)
            {
                MushGameMessageWake wakeMessage;
                try
                {
                    pJob->MessageConsume(*this, wakeMessage);
                }
                catch (MushcoreNonFatalFail& e)
                {
                    MushcoreLog::Sgl().ErrorLog() << "Job wake consumption failure: " << e.what() << endl
                        << "Job was '" << p->first << "': " << *pJob << endl;
                    pJob->CompleteSet(true);
                }
            }
        }
        
        tJobList::tIterator oldP = p;
        ++p;

        if (pJob->Complete())
        {
            ioList.Delete(oldP);
        }
    }
}

void
MushGameLogic::PerFrameProcessing(void)
{
    JobListProcess(SaveData().ToServerMailboxWRef(), SaveData().JobListWRef());
}

//%outOfLineFunctions {

const char *MushGameLogic::AutoName(void) const
{
    return "MushGameLogic";
}

MushcoreVirtualObject *MushGameLogic::AutoClone(void) const
{
    return new MushGameLogic(*this);
}

MushcoreVirtualObject *MushGameLogic::AutoCreate(void) const
{
    return new MushGameLogic;
}

MushcoreVirtualObject *MushGameLogic::AutoVirtualFactory(void)
{
    return new MushGameLogic;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameLogic", MushGameLogic::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameLogic::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "dataRef=" << m_dataRef << ", ";
    ioOut << "hostDataRef=" << m_hostDataRef;
    ioOut << "]";
}
bool
MushGameLogic::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "dataRef")
    {
        ioIn >> m_dataRef;
    }
    else if (inTagStr == "hostDataRef")
    {
        ioIn >> m_hostDataRef;
    }
    else
    {
        return false;
    }
    return true;
}
void
MushGameLogic::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("dataRef");
    ioOut << m_dataRef;
    ioOut.TagSet("hostDataRef");
    ioOut << m_hostDataRef;
}
//%outOfLineFunctions } DVO9yyMiWy5cK9z0gQKXvQ
