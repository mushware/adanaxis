//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionWorkspace.cpp
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
//%Header } 6KASaPiwmr9A4q1aVRtl6g
/*
 * $Id$
 * $Log$
 */

#include "MushCollisionWorkspace.h"

//%outOfLineFunctions {

const char *MushCollisionWorkspace::AutoName(void) const
{
    return "MushCollisionWorkspace";
}

MushcoreVirtualObject *MushCollisionWorkspace::AutoClone(void) const
{
    return new MushCollisionWorkspace(*this);
}

MushcoreVirtualObject *MushCollisionWorkspace::AutoCreate(void) const
{
    return new MushCollisionWorkspace;
}

MushcoreVirtualObject *MushCollisionWorkspace::AutoVirtualFactory(void)
{
    return new MushCollisionWorkspace;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushCollisionWorkspace", MushCollisionWorkspace::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushCollisionWorkspace::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushCollisionWorkspace::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushCollisionWorkspace::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } 7U0lCVx4tlIQkeWRConURw
