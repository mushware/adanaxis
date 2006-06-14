//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryExtruder.cpp
 *
 * Copyright: Andy Southgate 2005-2006
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
//%Header } +CjJTslTpESdG8DA9+lCGw
/*
 * $Id$
 * $Log$
 */

#include "MushMeshLibraryExtruder.h"

//%outOfLineFunctions {

const char *MushMeshLibraryExtruder::AutoName(void) const
{
    return "MushMeshLibraryExtruder";
}

MushcoreVirtualObject *MushMeshLibraryExtruder::AutoClone(void) const
{
    return new MushMeshLibraryExtruder(*this);
}

MushcoreVirtualObject *MushMeshLibraryExtruder::AutoCreate(void) const
{
    return new MushMeshLibraryExtruder;
}

MushcoreVirtualObject *MushMeshLibraryExtruder::AutoVirtualFactory(void)
{
    return new MushMeshLibraryExtruder;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMeshLibraryExtruder", MushMeshLibraryExtruder::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMeshLibraryExtruder::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushMesh4Extruder::AutoPrint(ioOut);
    ioOut << "]";
}
bool
MushMeshLibraryExtruder::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (MushMesh4Extruder::AutoXMLDataProcess(ioIn, inTagStr))
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
MushMeshLibraryExtruder::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushMesh4Extruder::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } zGI/YPt0OmIao0cmqdOEcw
