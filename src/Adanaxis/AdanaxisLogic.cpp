//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisLogic.cpp
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
//%Header } ui3Az6sPZVE4olMwWeOmrw
/*
 * $Id$
 * $Log$
 */

#include "AdanaxisLogic.h"

//%outOfLineFunctions {

const char *AdanaxisLogic::AutoName(void) const
{
    return "AdanaxisLogic";
}

MushcoreVirtualObject *AdanaxisLogic::AutoClone(void) const
{
    return new AdanaxisLogic(*this);
}

MushcoreVirtualObject *AdanaxisLogic::AutoCreate(void) const
{
    return new AdanaxisLogic;
}

MushcoreVirtualObject *AdanaxisLogic::AutoVirtualFactory(void)
{
    return new AdanaxisLogic;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisLogic", AdanaxisLogic::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisLogic::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameLogic::AutoPrint(ioOut);
    ioOut << "]";
}
bool
AdanaxisLogic::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
AdanaxisLogic::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameLogic::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } i810fq7uLu8LgqN5Dfw4QQ
