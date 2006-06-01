//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshMaterialRef.cpp
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
//%Header } 8GMBckdEbWXBFMxF4lkmEA
/*
 * $Id: MushMeshMaterialRef.cpp,v 1.2 2005/07/02 00:42:38 southa Exp $
 * $Log: MushMeshMaterialRef.cpp,v $
 * Revision 1.2  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.1  2005/06/30 12:04:55  southa
 * Mesh work
 *
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
//%outOfLineFunctions } DyIwh0bXkCOC9IcLYzJGzw
