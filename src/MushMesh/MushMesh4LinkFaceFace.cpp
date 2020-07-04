//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4LinkFaceFace.cpp
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
//%Header } NaWqzK5GB6fJWPOiVO1oFA
/*
 * $Id: MushMesh4LinkFaceFace.cpp,v 1.2 2006/06/01 15:39:28 southa Exp $
 * $Log: MushMesh4LinkFaceFace.cpp,v $
 * Revision 1.2  2006/06/01 15:39:28  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/13 16:45:05  southa
 * Extrusion work
 *
 */

#include "MushMesh4LinkFaceFace.h"

//%outOfLineFunctions {

const char *MushMesh4LinkFaceFace::AutoName(void) const
{
    return "MushMesh4LinkFaceFace";
}

MushcoreVirtualObject *MushMesh4LinkFaceFace::AutoClone(void) const
{
    return new MushMesh4LinkFaceFace(*this);
}

MushcoreVirtualObject *MushMesh4LinkFaceFace::AutoCreate(void) const
{
    return new MushMesh4LinkFaceFace;
}

MushcoreVirtualObject *MushMesh4LinkFaceFace::AutoVirtualFactory(void)
{
    return new MushMesh4LinkFaceFace;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMesh4LinkFaceFace", MushMesh4LinkFaceFace::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMesh4LinkFaceFace::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "faceNum=" << m_faceNum << ", ";
    ioOut << "localFacetNum=" << m_localFacetNum << ", ";
    ioOut << "remoteFacetNum=" << m_remoteFacetNum;
    ioOut << "]";
}
bool
MushMesh4LinkFaceFace::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "faceNum")
    {
        ioIn >> m_faceNum;
    }
    else if (inTagStr == "localFacetNum")
    {
        ioIn >> m_localFacetNum;
    }
    else if (inTagStr == "remoteFacetNum")
    {
        ioIn >> m_remoteFacetNum;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushMesh4LinkFaceFace::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("faceNum");
    ioOut << m_faceNum;
    ioOut.TagSet("localFacetNum");
    ioOut << m_localFacetNum;
    ioOut.TagSet("remoteFacetNum");
    ioOut << m_remoteFacetNum;
}
//%outOfLineFunctions } isdI6Z0tdgU7swE/2Nkojw
