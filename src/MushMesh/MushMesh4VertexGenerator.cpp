//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4VertexGenerator.cpp
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
//%Header } 5KrHWQ/eoM4NYvjNROiGUA
/*
 * $Id: MushMesh4VertexGenerator.cpp,v 1.2 2006/06/01 15:39:28 southa Exp $
 * $Log: MushMesh4VertexGenerator.cpp,v $
 * Revision 1.2  2006/06/01 15:39:28  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/12 20:39:05  southa
 * Mesh library work
 *
 */

#include "MushMesh4VertexGenerator.h"

//%outOfLineFunctions {

const char *MushMesh4VertexGenerator::AutoName(void) const
{
    return "MushMesh4VertexGenerator";
}

MushcoreVirtualObject *MushMesh4VertexGenerator::AutoClone(void) const
{
    return new MushMesh4VertexGenerator(*this);
}

MushcoreVirtualObject *MushMesh4VertexGenerator::AutoCreate(void) const
{
    return new MushMesh4VertexGenerator;
}

MushcoreVirtualObject *MushMesh4VertexGenerator::AutoVirtualFactory(void)
{
    return new MushMesh4VertexGenerator;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMesh4VertexGenerator", MushMesh4VertexGenerator::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMesh4VertexGenerator::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushMesh4VertexGenerator::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushMesh4VertexGenerator::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } lyeVTCecrUbXkcWUQLvJPw
