//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameLogicLocal.cpp
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
//%Header } 73iRqDd6zP6hGImTnrZMfg
/*
 * $Id: MushGameLogicLocal.cpp,v 1.7 2005/07/02 00:42:37 southa Exp $
 * $Log: MushGameLogicLocal.cpp,v $
 * Revision 1.7  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.6  2005/06/30 16:29:25  southa
 * Adanaxis work
 *
 * Revision 1.5  2005/06/23 17:25:25  southa
 * MushGame link work
 *
 * Revision 1.4  2005/06/23 13:56:58  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/22 20:01:59  southa
 * MushGame link work
 *
 * Revision 1.2  2005/06/21 15:57:48  southa
 * MushGame work
 *
 * Revision 1.1  2005/06/21 13:10:51  southa
 * MushGame work
 *
 */

#include "MushGameLogicLocal.h"

#include "MushGameJobPlayerCreate.h"
#include "MushGameUtil.h"

MushGameLogicLocal::MushGameLogicLocal()
{
}

void
MushGameLogicLocal::SinglePlayerCheck(void)
{
    if (SaveData().Players().Size() < 1)
    {
        std::string jobName = "localplayercreate";
        if (!SaveData().JobList().Exists(jobName))
        {
            MushGameJobPlayerCreate *pCreate = new MushGameJobPlayerCreate("j:"+jobName);
            SaveData().JobListWRef().Give(jobName, pCreate);
        }
    }
}

void
MushGameLogicLocal::PerFrameProcessing(void)
{
    SinglePlayerCheck();
    MushGameLogic::PerFrameProcessing();
}

void
MushGameLogicLocal::JobMessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    throw MushcoreDataFail(std::string("Discarding message of type '")+inMessage.AutoName()+"' with Job ID");
}

//%outOfLineFunctions {

const char *MushGameLogicLocal::AutoName(void) const
{
    return "MushGameLogicLocal";
}

MushcoreVirtualObject *MushGameLogicLocal::AutoClone(void) const
{
    return new MushGameLogicLocal(*this);
}

MushcoreVirtualObject *MushGameLogicLocal::AutoCreate(void) const
{
    return new MushGameLogicLocal;
}

MushcoreVirtualObject *MushGameLogicLocal::AutoVirtualFactory(void)
{
    return new MushGameLogicLocal;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameLogicLocal", MushGameLogicLocal::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameLogicLocal::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameLogic::AutoPrint(ioOut);
    ioOut << "]";
}
bool
MushGameLogicLocal::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (MushGameLogic::AutoXMLDataProcess(ioIn, inTagStr))
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
MushGameLogicLocal::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameLogic::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } 96dDf3dow9nkQEE6n/tInA
