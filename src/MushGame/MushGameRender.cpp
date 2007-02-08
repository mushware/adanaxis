//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameRender.cpp
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
//%Header } Up/Zo/AbGEsGQw3FmjqFGg
/*
 * $Id: MushGameRender.cpp,v 1.4 2006/07/20 12:22:22 southa Exp $
 * $Log: MushGameRender.cpp,v $
 * Revision 1.4  2006/07/20 12:22:22  southa
 * Precache display
 *
 * Revision 1.3  2006/06/01 15:39:26  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.1  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 */

#include "MushGameRender.h"

MUSHCORE_DATA_INSTANCE(MushGameRender);

void
MushGameRender::PrecacheRender(MushGameLogic& ioLogic, const MushGameCamera& inCamera)
{
    // No operation
}

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
//%outOfLineFunctions } S4xWtMTmFOzf3j9ZFnCXDw
