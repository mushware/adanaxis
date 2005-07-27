//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionListEntry.cpp
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
//%Header } aqwYlxB27su3kAczIZ6a6Q
/*
 * $Id$
 * $Log$
 */

#include "MushCollisionListEntry.h"

using namespace Mushware;
using namespace std;




//%outOfLineFunctions {

const char *MushCollisionListEntry::AutoName(void) const
{
    return "MushCollisionListEntry";
}

MushcoreVirtualObject *MushCollisionListEntry::AutoClone(void) const
{
    return new MushCollisionListEntry(*this);
}

MushcoreVirtualObject *MushCollisionListEntry::AutoCreate(void) const
{
    return new MushCollisionListEntry;
}

MushcoreVirtualObject *MushCollisionListEntry::AutoVirtualFactory(void)
{
    return new MushCollisionListEntry;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushCollisionListEntry", MushCollisionListEntry::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushCollisionListEntry::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushCollisionListEntry::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushCollisionListEntry::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } 32mjahm/s5hwm1EUGHDWRA
