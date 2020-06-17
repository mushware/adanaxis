//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Material.cpp
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
//%Header } C77x8bqZvyoPdzPcdpOwBA
/*
 * $Id: MushMesh4Material.cpp,v 1.2 2006/10/19 15:41:36 southa Exp $
 * $Log: MushMesh4Material.cpp,v $
 * Revision 1.2  2006/10/19 15:41:36  southa
 * Item handling
 *
 * Revision 1.1  2006/06/19 15:57:18  southa
 * Materials
 *
 */

#include "MushMesh4Material.h"

MUSHCORE_DATA_INSTANCE(MushMesh4Material);

//%outOfLineFunctions {

const char *MushMesh4Material::AutoName(void) const
{
    return "MushMesh4Material";
}

MushcoreVirtualObject *MushMesh4Material::AutoClone(void) const
{
    return new MushMesh4Material(*this);
}

MushcoreVirtualObject *MushMesh4Material::AutoCreate(void) const
{
    return new MushMesh4Material;
}

MushcoreVirtualObject *MushMesh4Material::AutoVirtualFactory(void)
{
    return new MushMesh4Material;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMesh4Material", MushMesh4Material::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMesh4Material::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "name=" << m_name << ", ";
    ioOut << "mappingType=" << m_mappingType;
    ioOut << "]";
}
bool
MushMesh4Material::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "name")
    {
        ioIn >> m_name;
    }
    else if (inTagStr == "mappingType")
    {
        ioIn >> m_mappingType;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushMesh4Material::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("name");
    ioOut << m_name;
    ioOut.TagSet("mappingType");
    ioOut << m_mappingType;
}
//%outOfLineFunctions } VEXtpiEsx4AChHs8CN3Y/A
