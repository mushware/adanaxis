//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryExtruder.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } YKWhGplcYmJQ1fSz2dkGOg
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
