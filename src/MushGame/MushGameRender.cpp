//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameRender.cpp
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
//%Header } w2//WvMUbsPuYAvxQojk5g
/*
 * $Id$
 * $Log$
 */

#include "MushGameRender.h"

MUSHCORE_DATA_INSTANCE(MushGameRender);

void
MushGameRender::FrameRender(MushGameLogic& ioLogic, const MushGameCamera& inCamera)
{
    // No operation
}
//%outOfLineFunctions {

const char *MushGameRender::AutoName(void) const
{
    return "MushGameRender";
}

MushcoreVirtualObject *MushGameRender::AutoClone(void) const
{
    return new MushGameRender(*this);
}

MushcoreVirtualObject *MushGameRender::AutoCreate(void) const
{
    return new MushGameRender;
}

MushcoreVirtualObject *MushGameRender::AutoVirtualFactory(void)
{
    return new MushGameRender;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameRender", MushGameRender::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameRender::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "groupingName=" << m_groupingName;
    ioOut << "]";
}
bool
MushGameRender::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "groupingName")
    {
        ioIn >> m_groupingName;
    }
    else
    {
        return false;
    }
    return true;
}
void
MushGameRender::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("groupingName");
    ioOut << m_groupingName;
}
//%outOfLineFunctions } 2hKtYVMcKekOTnMSdwRwAw
