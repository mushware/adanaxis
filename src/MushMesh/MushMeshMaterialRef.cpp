//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshMaterialRef.cpp
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
//%Header } n/UkWx9jYA8DIO4Ho+6crA
/*
 * $Id$
 * $Log$
 */

#include "MushMeshMaterialRef.h"

//%outOfLineFunctions {

const char *MushMeshMaterialRef::AutoName(void) const
{
    return "MushMeshMaterialRef";
}

MushcoreVirtualObject *MushMeshMaterialRef::AutoClone(void) const
{
    return new MushMeshMaterialRef(*this);
}

MushcoreVirtualObject *MushMeshMaterialRef::AutoCreate(void) const
{
    return new MushMeshMaterialRef;
}

MushcoreVirtualObject *MushMeshMaterialRef::AutoVirtualFactory(void)
{
    return new MushMeshMaterialRef;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMeshMaterialRef", MushMeshMaterialRef::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMeshMaterialRef::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushMeshMaterialRef::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushMeshMaterialRef::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } 8wyMLgxX+AeAnQlC4dawDQ
