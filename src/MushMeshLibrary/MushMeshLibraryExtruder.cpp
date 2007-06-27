//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryExtruder.cpp
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.4, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 3qqa4Z0hlix4iuZ+HvQdhQ
/*
 * $Id: MushMeshLibraryExtruder.cpp,v 1.3 2007/04/18 09:22:53 southa Exp $
 * $Log: MushMeshLibraryExtruder.cpp,v $
 * Revision 1.3  2007/04/18 09:22:53  southa
 * Header and level fixes
 *
 * Revision 1.2  2006/08/01 17:21:33  southa
 * River demo
 *
 * Revision 1.1  2006/06/14 11:20:08  southa
 * Ruby mesh generation
 *
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
