//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameRef.cpp
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
//%Header } dpL0b7TsIdCYecycwXE65g
/*
 *  MushGameRef.cpp
 *  project
 *
 *  Created by Andy Southgate on 24/06/2005.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include "MushGameRef.h"

//%outOfLineFunctions {

const char *MushGameRef::AutoName(void) const
{
    return "MushGameRef";
}

MushcoreVirtualObject *MushGameRef::AutoClone(void) const
{
    return new MushGameRef(*this);
}

MushcoreVirtualObject *MushGameRef::AutoCreate(void) const
{
    return new MushGameRef;
}

MushcoreVirtualObject *MushGameRef::AutoVirtualFactory(void)
{
    return new MushGameRef;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameRef", MushGameRef::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameRef::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushGameRef::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushGameRef::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } AdaIrpCYoLvBJAPCubbu5g
