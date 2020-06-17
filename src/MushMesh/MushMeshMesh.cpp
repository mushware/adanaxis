//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshMesh.cpp
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
//%Header } AhBeevPmVHxuXzHtsRi77g
/*
 * $Id: MushMeshMesh.cpp,v 1.4 2006/06/19 15:57:18 southa Exp $
 * $Log: MushMeshMesh.cpp,v $
 * Revision 1.4  2006/06/19 15:57:18  southa
 * Materials
 *
 * Revision 1.3  2006/06/01 15:39:30  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.1  2005/06/30 12:04:56  southa
 * Mesh work
 *
 */

#include "MushMeshMesh.h"

MushMeshMesh::MushMeshMesh()
{
}

MushMeshMesh::~MushMeshMesh()
{
}

//%outOfLineFunctions {

const char *MushMeshMesh::AutoName(void) const
{
    return "MushMeshMesh";
}

MushcoreVirtualObject *MushMeshMesh::AutoClone(void) const
{
    return new MushMeshMesh(*this);
}

MushcoreVirtualObject *MushMeshMesh::AutoCreate(void) const
{
    return new MushMeshMesh;
}

MushcoreVirtualObject *MushMeshMesh::AutoVirtualFactory(void)
{
    return new MushMeshMesh;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMeshMesh", MushMeshMesh::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMeshMesh::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushMeshMesh::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushMeshMesh::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } wTkzluhiBp14xt5f8qFrHg
