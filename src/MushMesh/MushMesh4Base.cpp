//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Base.cpp
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
//%Header } 0PKFEbUctRjQNMuvMH0V0A
/*
 * $Id: MushMesh4Base.cpp,v 1.1 2006/06/16 01:02:31 southa Exp $
 * $Log: MushMesh4Base.cpp,v $
 * Revision 1.1  2006/06/16 01:02:31  southa
 * Ruby mesh generation
 *
 */

#include "MushMesh4Base.h"

using namespace Mushware;
using namespace std;

void
MushMesh4Base::Make(MushMesh4Mesh& ioMesh) const
{
	throw MushcoreRequestFail("MushMesh4Base::Make not overriden - cannot build base object");
}
//%outOfLineFunctions {

const char *MushMesh4Base::AutoName(void) const
{
    return "MushMesh4Base";
}

MushcoreVirtualObject *MushMesh4Base::AutoClone(void) const
{
    return new MushMesh4Base(*this);
}

MushcoreVirtualObject *MushMesh4Base::AutoCreate(void) const
{
    return new MushMesh4Base;
}

MushcoreVirtualObject *MushMesh4Base::AutoVirtualFactory(void)
{
    return new MushMesh4Base;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMesh4Base", MushMesh4Base::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMesh4Base::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushMesh4Base::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushMesh4Base::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } i40vBYeuo0UBHkAjdU0lGQ
