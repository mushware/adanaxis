//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameVolatileData.cpp
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
//%Header } ZLCiVmbUjo5qfJ+17ayqmA
/*
 * $Id$
 * $Log$
 */

#include "MushGameVolatileData.h"

MUSHCORE_DATA_INSTANCE(MushGameVolatileData);

MushGameVolatileData::MushGameVolatileData()
{
}
//%outOfLineFunctions {

const char *MushGameVolatileData::AutoName(void) const
{
    return "MushGameVolatileData";
}

MushcoreVirtualObject *MushGameVolatileData::AutoClone(void) const
{
    return new MushGameVolatileData(*this);
}

MushcoreVirtualObject *MushGameVolatileData::AutoCreate(void) const
{
    return new MushGameVolatileData;
}

MushcoreVirtualObject *MushGameVolatileData::AutoVirtualFactory(void)
{
    return new MushGameVolatileData;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameVolatileData", MushGameVolatileData::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameVolatileData::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushGameVolatileData::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushGameVolatileData::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } oj9JinIowURCdEE5HkvPnw
