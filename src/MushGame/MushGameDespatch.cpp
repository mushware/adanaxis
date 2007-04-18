//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameDespatch.cpp
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } MPCdAgS4aAxtW+a997Z9tQ
/*
 * $Id: MushGameDespatch.cpp,v 1.3 2006/06/01 15:39:21 southa Exp $
 * $Log: MushGameDespatch.cpp,v $
 * Revision 1.3  2006/06/01 15:39:21  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.1  2005/06/20 16:14:30  southa
 * Adanaxis work
 *
 */

#include "MushGameDespatch.h"

//%outOfLineFunctions {

const char *MushGameDespatch::AutoName(void) const
{
    return "MushGameDespatch";
}

MushcoreVirtualObject *MushGameDespatch::AutoClone(void) const
{
    return new MushGameDespatch(*this);
}

MushcoreVirtualObject *MushGameDespatch::AutoCreate(void) const
{
    return new MushGameDespatch;
}

MushcoreVirtualObject *MushGameDespatch::AutoVirtualFactory(void)
{
    return new MushGameDespatch;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameDespatch", MushGameDespatch::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameDespatch::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushGameDespatch::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushGameDespatch::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } kfbxuxA1GBQa6vMsU9Ds6w
