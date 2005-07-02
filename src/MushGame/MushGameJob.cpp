//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameJob.cpp
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
//%Header } x1hhF/NH4dT4y5U7K5AdDw
/*
 * $Id: MushGameJob.cpp,v 1.5 2005/06/23 17:25:25 southa Exp $
 * $Log: MushGameJob.cpp,v $
 * Revision 1.5  2005/06/23 17:25:25  southa
 * MushGame link work
 *
 * Revision 1.4  2005/06/23 13:56:58  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/22 20:01:58  southa
 * MushGame link work
 *
 * Revision 1.2  2005/06/21 15:57:47  southa
 * MushGame work
 *
 * Revision 1.1  2005/06/21 13:10:51  southa
 * MushGame work
 *
 */

#include "MushGameJob.h"

#include "MushGameSaveData.h"

MushGameJob::MushGameJob(const std::string& inID) :
    m_shouldWake(false),
    m_complete(false),
    m_wakeTime(0),
    m_id(inID)
{
}

void
MushGameJob::MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    throw MushcoreDataFail(std::string("Unhandled message type ")+inMessage.AutoName()+" in "+AutoName());
}

//%outOfLineFunctions {

const char *MushGameJob::AutoName(void) const
{
    return "MushGameJob";
}

MushcoreVirtualObject *MushGameJob::AutoClone(void) const
{
    return new MushGameJob(*this);
}

MushcoreVirtualObject *MushGameJob::AutoCreate(void) const
{
    return new MushGameJob;
}

MushcoreVirtualObject *MushGameJob::AutoVirtualFactory(void)
{
    return new MushGameJob;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameJob", MushGameJob::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameJob::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "shouldWake=" << m_shouldWake << ", ";
    ioOut << "complete=" << m_complete << ", ";
    ioOut << "wakeTime=" << m_wakeTime << ", ";
    ioOut << "id=" << m_id;
    ioOut << "]";
}
bool
MushGameJob::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "shouldWake")
    {
        ioIn >> m_shouldWake;
    }
    else if (inTagStr == "complete")
    {
        ioIn >> m_complete;
    }
    else if (inTagStr == "wakeTime")
    {
        ioIn >> m_wakeTime;
    }
    else if (inTagStr == "id")
    {
        ioIn >> m_id;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameJob::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("shouldWake");
    ioOut << m_shouldWake;
    ioOut.TagSet("complete");
    ioOut << m_complete;
    ioOut.TagSet("wakeTime");
    ioOut << m_wakeTime;
    ioOut.TagSet("id");
    ioOut << m_id;
}
//%outOfLineFunctions } d8SCAKb4/EEakq925tuONQ
