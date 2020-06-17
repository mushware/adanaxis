//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Maker.cpp
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
//%Header } pk7ueWO7XuAM7v2CHDHo3Q
/*
 * $Id: MushMesh4Maker.cpp,v 1.1 2006/06/14 18:45:47 southa Exp $
 * $Log: MushMesh4Maker.cpp,v $
 * Revision 1.1  2006/06/14 18:45:47  southa
 * Ruby mesh generation
 *
 */

#include "MushMesh4Maker.h"

MUSHCORE_SINGLETON_INSTANCE(MushMesh4Maker);

using namespace Mushware;
using namespace std;

void
MushMesh4Maker::Make(MushMesh4Mesh& ioMesh)
{
	throw MushcoreRequestFail("MushMesh4Maker not overriden - cannot build mesh");
}

//%outOfLineFunctions {

const char *MushMesh4Maker::AutoName(void) const
{
    return "MushMesh4Maker";
}

MushcoreVirtualObject *MushMesh4Maker::AutoClone(void) const
{
    return new MushMesh4Maker(*this);
}

MushcoreVirtualObject *MushMesh4Maker::AutoCreate(void) const
{
    return new MushMesh4Maker;
}

MushcoreVirtualObject *MushMesh4Maker::AutoVirtualFactory(void)
{
    return new MushMesh4Maker;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMesh4Maker", MushMesh4Maker::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMesh4Maker::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushMesh4Maker::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushMesh4Maker::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } C+6Nad+JPItHLhguOl+Slg
