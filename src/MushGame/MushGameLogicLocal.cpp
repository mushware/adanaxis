//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameLogicLocal.cpp
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
//%Header } qP/D11f61WKLayRHqTfr/g
/*
 * $Id: MushGameLogicLocal.cpp,v 1.1 2005/06/21 13:10:51 southa Exp $
 * $Log: MushGameLogicLocal.cpp,v $
 * Revision 1.1  2005/06/21 13:10:51  southa
 * MushGame work
 *
 */

#include "MushGameLogicLocal.h"

#include "MushGameJobPlayerCreate.h"

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
            MushGameJobPlayerCreate *pCreate = new MushGameJobPlayerCreate;
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
    else
    {
        return false;
    }
    return true;
}
void
MushGameLogicLocal::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } alEi4IbB6ooex+HwUNBGeg