//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameHostVolatileData.cpp
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
//%Header } 9sJQuPcTPwOAERot0KKS1w
/*
 * $Id: MushGameHostVolatileData.cpp,v 1.2 2005/07/02 00:42:37 southa Exp $
 * $Log: MushGameHostVolatileData.cpp,v $
 * Revision 1.2  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.1  2005/06/21 15:57:47  southa
 * MushGame work
 *
 */

#include "MushGameHostVolatileData.h"

MUSHCORE_DATA_INSTANCE(MushGameHostVolatileData);

MushGameHostVolatileData::MushGameHostVolatileData()
{
}

//%outOfLineFunctions {

const char *MushGameHostVolatileData::AutoName(void) const
{
    return "MushGameHostVolatileData";
}

MushcoreVirtualObject *MushGameHostVolatileData::AutoClone(void) const
{
    return new MushGameHostVolatileData(*this);
}

MushcoreVirtualObject *MushGameHostVolatileData::AutoCreate(void) const
{
    return new MushGameHostVolatileData;
}

MushcoreVirtualObject *MushGameHostVolatileData::AutoVirtualFactory(void)
{
    return new MushGameHostVolatileData;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameHostVolatileData", MushGameHostVolatileData::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameHostVolatileData::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushGameHostVolatileData::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushGameHostVolatileData::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } ZcMiWHoes92oYotzMo710g
