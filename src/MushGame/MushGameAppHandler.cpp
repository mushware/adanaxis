//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameAppHandler.cpp
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
//%Header } vTDmm7/9yQPLbrRCYbzIaw
/*
 * $Id$
 * $Log$
 */

#include "MushGameAppHandler.h"

#include "MushGameMessageControlInfo.h"

using namespace Mushware;
using namespace std;

MushGameAppHandler::MushGameAppHandler(const std::string& inName) :
    GameAppHandler(),
    m_lastTickerMsec(0)
{
    GroupingNameSet(inName);
}

void
MushGameAppHandler::GroupingNameSet(const std::string& inName)
{
    m_groupingName = inName;
    std::string controlMailboxName = inName+"-controlmailbox";
    MushcoreData<MushGameMailbox>::Sgl().GetOrCreate(controlMailboxName);
    m_controlMailboxRef.NameSet(controlMailboxName);
}

void
MushGameAppHandler::AxisDefSet(const MushGameAxisDef& inAxisDef, Mushware::U32 inAxisNum)
{
    if (inAxisNum > 64)
    {
        throw MushcoreDataFail("Axis number too high");
    }
    if (inAxisNum >= m_axisDefs.size())
    {
        m_axisDefs.resize(inAxisNum+1);
    }
    m_axisDefs[inAxisNum] = inAxisDef;
}

void
MushGameAppHandler::FillAxisPipe(void)
{
    typedef MushGameMessageControlInfo tMessage;
    std::auto_ptr<MushGameMessageControlInfo> aControlInfo;
    
    for (U32 i=0; i<m_axisDefs.size(); ++i)
    {
        MushGameAxisDef& axisDefRef = m_axisDefs[i];
        if (axisDefRef.PosHasMoved())
        {
            if (aControlInfo.get() == NULL)
            {
                aControlInfo.reset(new MushGameMessageControlInfo);
                aControlInfo->TimestampSet(MillisecondsGet());
            }
            aControlInfo->AxisEventsWRef().push_back(tMessage::tAxisEvent(i, axisDefRef.Pos()));
            axisDefRef.PosHasMovedSet(false);
        }
    }        
    if (aControlInfo.get() != NULL)
    {
        m_controlMailboxRef.WRef().Give(aControlInfo.release());
    }
}

void
MushGameAppHandler::AxisTicker(Mushware::tMsec inTimeslice)
{
    tVal amount = inTimeslice / 1000.0;
    
    // Loop through axes and apply the effect of keys
    for (U32 i=0; i<m_axisDefs.size(); ++i)
    {
        MushGameAxisDef& axisDefRef = m_axisDefs[i];
        
        if (axisDefRef.UseKeys())
        {
            if (KeyStateGet(axisDefRef.UpKey()))
            {
                axisDefRef.Accelerate(amount);
            }
            else if (KeyStateGet(axisDefRef.DownKey()))
            {
                axisDefRef.Accelerate(-amount);
            }
            else
            {
                axisDefRef.Decelerate(amount);
            }
        }
        if (axisDefRef.Integrate())
        {
            axisDefRef.ApplyIntegration(amount);
        }
    }
}

void
MushGameAppHandler::Idle(void)
{
    tMsec msecNow = MillisecondsGet();
    
    tMsec timesliceMsec = msecNow - m_lastTickerMsec;
    
    MushcoreUtil::Constrain<tMsec>(timesliceMsec, 0, 1000);
        
    // Input is read on a 10ms (or greater) tick
    if (timesliceMsec >= 10)
    {
        if (m_lastTickerMsec != 0)
        {
            AxisTicker(timesliceMsec);
            FillAxisPipe();
        }
        m_lastTickerMsec = msecNow;
    }
    
    GameAppHandler::Idle();
}

