//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshDisplacement.cpp
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
//%Header } bOh+7o6+HfdRR06kOGS7hQ
/*
 * $Id: MushMeshDisplacement.cpp,v 1.2 2006/06/01 15:39:29 southa Exp $
 * $Log: MushMeshDisplacement.cpp,v $
 * Revision 1.2  2006/06/01 15:39:29  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/12 20:39:05  southa
 * Mesh library work
 *
 */

#include "MushMeshDisplacement.h"

//%outOfLineFunctions {

const char *MushMeshDisplacement::AutoName(void) const
{
    return "MushMeshDisplacement";
}

MushcoreVirtualObject *MushMeshDisplacement::AutoClone(void) const
{
    return new MushMeshDisplacement(*this);
}

MushcoreVirtualObject *MushMeshDisplacement::AutoCreate(void) const
{
    return new MushMeshDisplacement;
}

MushcoreVirtualObject *MushMeshDisplacement::AutoVirtualFactory(void)
{
    return new MushMeshDisplacement;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMeshDisplacement", MushMeshDisplacement::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMeshDisplacement::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "offset=" << m_offset << ", ";
    ioOut << "rotation=" << m_rotation << ", ";
    ioOut << "scale=" << m_scale;
    ioOut << "]";
}
bool
MushMeshDisplacement::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "offset")
    {
        ioIn >> m_offset;
    }
    else if (inTagStr == "rotation")
    {
        ioIn >> m_rotation;
    }
    else if (inTagStr == "scale")
    {
        ioIn >> m_scale;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushMeshDisplacement::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("offset");
    ioOut << m_offset;
    ioOut.TagSet("rotation");
    ioOut << m_rotation;
    ioOut.TagSet("scale");
    ioOut << m_scale;
}
//%outOfLineFunctions } QpLfeJFjfVzGw6gNjbRU+Q
