//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisData.cpp
 *
 * Copyright: Andy Southgate 2005
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 3Y+7aZMBXZ16kNADvaOl9g
/*
 * $Id$
 * $Log$
 */

#include "AdanaxisData.h"

AdanaxisData::AdanaxisData(const std::string& inName) :
    MushGameData(inName)
{
}
//%outOfLineFunctions {

const char *AdanaxisData::AutoName(void) const
{
    return "AdanaxisData";
}

MushcoreVirtualObject *AdanaxisData::AutoClone(void) const
{
    return new AdanaxisData(*this);
}

MushcoreVirtualObject *AdanaxisData::AutoCreate(void) const
{
    return new AdanaxisData;
}

MushcoreVirtualObject *AdanaxisData::AutoVirtualFactory(void)
{
    return new AdanaxisData;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisData", AdanaxisData::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisData::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameData::AutoPrint(ioOut);
    ioOut << "]";
}
bool
AdanaxisData::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (MushGameData::AutoXMLDataProcess(ioIn, inTagStr))
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
AdanaxisData::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameData::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } 03vLNy6OhwIL6GKqF4s06w
